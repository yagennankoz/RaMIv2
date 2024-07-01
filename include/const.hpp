#ifndef _CONST_HPP_
#define _CONST_HPP_

#define UART0_TX_PIN        (0u)
#define UART0_RX_PIN        (1u)
#define UART1_TX_PIN        (4u)
#define UART1_RX_PIN        (5u)

// CANCEL BUTTON (GPIO22)
#define CANCEL_PIN          (22u)

// OK BUTTON (GPIO28)
#define OK_PIN              (28u)

// ROTARY ENCODER
// CLK (GPIO27)
#define ROT_A_PIN           (27u)
// DT (GPIO26)
#define ROT_B_PIN           (26u)

// SSD1306
// SDA
#define OLED_SDA_PIN        (16u)
// SCL
#define OLED_SCL_PIN        (17u)


#define MIDI_IN                     uart0
#define MIDI_OUT                    uart1

#define UART_BAUD_RATE              31250

#define BUFFER_SIZE                 2048 
#define FLASH_TARGET_OFFSET         0x1F0000
#define DELAY_TIME_DEFAULT          115000
#define DELAY_TIME_MAX              1000000
#define DELAY_DIFF                  500
#define EVENT_INTERVAL              (500000u)

#define COL_MAX                     (10u)
#define ROW_MAX                     (6u)

#define ENCODER_CLK_COUNT           (2u)

enum {
    MODE_PLAY,
    MODE_CONFIG,
    MODE_DELAY_SW,
    MODE_DELAY_TIME,
    MODE_RESET,
    MODE_MIDIGUY
};

typedef struct {
    uint32_t delay_time;
    uint8_t delay_enabled;
    uint8_t midi_guy_mt_enabled;
} CONFIG_DATA;

const uint8_t SIGNATURE[] = "RaMI";

#endif