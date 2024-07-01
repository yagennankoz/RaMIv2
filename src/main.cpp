#include <Arduino.h>

#include <stdio.h>
#include <string.h>
#include <hardware/uart.h>
#include <hardware/gpio.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ModeBase.hpp"
#include "ModePlay.hpp"
#include "ModeConfig.hpp"
#include "ModeDelaySw.hpp"
#include "ModeDelayTime.hpp"
#include "ModeReset.hpp"
#include "ModeMidiGuy.hpp"
#include "util.hpp"
#include "rami.hpp"

static CONFIG_DATA config;
static note data_buffer[BUFFER_SIZE];
static uint16_t in_idx;
static uint16_t out_idx;
static uint8_t mode;
static uint16_t rotStateLast = 0;

Adafruit_SSD1306    oled(128, 64, &Wire, -1);
ModePlay            modePlay = ModePlay();
ModeConfig          modeConfig = ModeConfig();
ModeDelaySw         modeDelaySw = ModeDelaySw(&config);
ModeDelayTime       modeDelayTime = ModeDelayTime(&config);
ModeReset           modeReset = ModeReset(&config);
ModeMidiGuy         modeMidiGuy = ModeMidiGuy(&config);
int16_t             clk_last;

const int8_t KNOBDIR[] = {
   0, 0, 0, 0,
   0, 0, 0,-1,
   0, 0, 0, 1,
   0, 0, 0, 0};

static ModeBase *mode_tbl[] = {
    &modePlay,
    &modeConfig,
    &modeDelaySw,
    &modeDelayTime,
    &modeReset,
    &modeMidiGuy
};

void setup()
{
    Serial.begin(9600);

    Wire.setSDA(OLED_SDA_PIN);
    Wire.setSCL(OLED_SCL_PIN);
    Wire.begin(); 

    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.setTextColor(SSD1306_WHITE);

    setup_gpio();

    load_setting(&config);
    in_idx = 0;
    out_idx = 0;

    mode = MODE_PLAY;

    modePlay.init();
    modePlay.setMsg("RaMI v2\r\n");

    oled.clearDisplay();
    oled.display();

    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    uint32_t counter;
    uint32_t note_counter;
    uint32_t elapsed;
    uint32_t led_counter = 0;
    uint32_t led_elapsed;

    while (uart_is_writable(MIDI_OUT)) {
        mode_tbl[mode]->print(&oled);

        if (in_idx == out_idx) {
            digitalWrite(LED_BUILTIN, LOW);
            continue;
        }
        counter = time_us_32();
        note_counter = data_buffer[out_idx].counter;
        if (counter >= note_counter) {
            elapsed = counter - note_counter;
            led_elapsed = counter - led_counter;
        } else {
            elapsed = UINT32_MAX - note_counter + counter;
            led_elapsed = UINT32_MAX - led_counter + counter;
        }
        if (led_elapsed > 20000) {
            digitalWrite(LED_BUILTIN, LOW);
        }
        if (config.delay_enabled && (elapsed < config.delay_time)) {
            continue;
        }

        uart_putc_raw(MIDI_OUT, data_buffer[out_idx++].data);
        digitalWrite(LED_BUILTIN, HIGH);
        led_counter = counter;
        if (out_idx >= BUFFER_SIZE) {
            out_idx = 0;
        }
    }
    digitalWrite(LED_BUILTIN, LOW);
}

void setup_gpio() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);

    uart_init(MIDI_IN, UART_BAUD_RATE);
    uart_set_hw_flow(MIDI_IN, false, false);
    uart_set_format(MIDI_IN, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(MIDI_IN, false);
    int UART_IRQ = MIDI_IN == uart0 ? UART0_IRQ : UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, midi_in_callback);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(MIDI_IN, true, false);

    uart_init(MIDI_OUT, UART_BAUD_RATE);
    uart_set_hw_flow(MIDI_OUT, false, false);
    uart_set_format(MIDI_OUT, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(MIDI_OUT, false);

    pinMode(CANCEL_PIN, INPUT);
    attachInterrupt(CANCEL_PIN, cancel_callback, RISING);

    pinMode(OK_PIN, INPUT);
    attachInterrupt(OK_PIN, ok_callback, RISING);

    pinMode(ROT_A_PIN, INPUT);
    attachInterrupt(ROT_A_PIN, rotary_callback, CHANGE);
    pinMode(ROT_B_PIN, INPUT);
    attachInterrupt(ROT_B_PIN, rotary_callback, CHANGE);
}

static void midi_in_callback() {
    uint8_t c;
    while (uart_is_readable(MIDI_IN)) {
        c = uart_getc(MIDI_IN);
        if (config.midi_guy_mt_enabled && (c >= 0xC0 && c <= 0xCF)) {
            data_buffer[in_idx].data = (c & 0x0F) | 0xB0;
            data_buffer[in_idx++].counter = time_us_32();
            data_buffer[in_idx].data = 0x00;
            data_buffer[in_idx++].counter = time_us_32();
            data_buffer[in_idx].data = 0x7F;
            data_buffer[in_idx++].counter = time_us_32();
        }
        data_buffer[in_idx].data = c;
        data_buffer[in_idx++].counter = time_us_32();
        if (in_idx >= BUFFER_SIZE) {
            in_idx = 0;
        }
    }
}

static void cancel_callback()
{
    if (!isEventAvailable()) {
        return;
    }
    uint8_t mode_next = mode_tbl[mode]->onCancel();
    if (mode != mode_next) {
        mode = mode_next;
        mode_tbl[mode]->init();
    }
}

static void ok_callback()
{
    if (!isEventAvailable()) {
        return;
    }
    uint8_t mode_next = mode_tbl[mode]->onOK();
    if (mode != mode_next) {
        mode = mode_next;
        mode_tbl[mode]->init();
    }
}

static void rotary_callback()
{
    int8_t rot = 0;
    uint16_t nowState = digitalRead(ROT_A_PIN) | (digitalRead(ROT_B_PIN) << 1);
    rot = KNOBDIR[nowState | (rotStateLast << 2)];
    rotStateLast = nowState;

    mode_tbl[mode]->onRotate(rot);
}

