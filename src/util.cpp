#include "util.hpp"

extern uint32_t delay_time;
extern uint8_t delay_sw;

void print_menu(
    Adafruit_SSD1306* oled,
    const char* title,
    uint8_t item_num,
    const char* menu_list,
    int8_t chosen
) {
    char* items[6];
    char* ptr = (char*)menu_list;
    uint8_t cnt = 1;

    items[0] = (char*)menu_list;
    while (true) {
        if (*(ptr++) == '\0') {
            items[cnt++] = ptr;
        };
        if (cnt >= item_num) {
            break;
        }
    }
    oled->clearDisplay();
    oled->setTextSize(2);
    uint8_t page = chosen / 3;
    uint8_t idx = chosen % 3;
    for (uint8_t i = 0; i < 3; i++) {
        if (item_num <= (i + (page*3))) {
            continue;
        }
        if ((i + (page*3)) == chosen) {
            oled->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        } else {
            oled->setTextColor(SSD1306_WHITE);
        }
        oled->setCursor(0, (i + 1) * 16);
        oled->print(items[i + (page*3)]);
    }
    oled->setTextColor(SSD1306_WHITE);
    oled->setTextSize(1);
    oled->setCursor(124-strlen(title)*6,0);
    oled->print(title);
    oled->drawLine(0,10, 127,10, SSD1306_WHITE);
    oled->drawLine(0,12, 127,12, SSD1306_WHITE);
    oled->display();
}


unsigned long lastEvent = 0;

uint8_t isEventAvailable() {
    uint32_t now = micros();
    uint32_t elapsed;
    if (now > lastEvent) {
        elapsed = now - lastEvent;
    } else {
        elapsed = UINT32_MAX - lastEvent + now;
    }

    if (elapsed > EVENT_INTERVAL) {
        lastEvent = now;
        return true;
    }

    return false;
}

void save_setting(CONFIG_DATA *config)
{
    uint8_t write_data[FLASH_PAGE_SIZE];

    memcpy(write_data, SIGNATURE, 4);
    memcpy(&write_data[4], config, sizeof(CONFIG_DATA));

    noInterrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, write_data, FLASH_PAGE_SIZE);
    interrupts();
}

void load_setting(CONFIG_DATA *config)
{
    printf("load_setting\n");
    const uint8_t *saved_data = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);
    
    uint32_t delay_time_tmp;
    uint8_t sign[4];
    memcpy(sign, saved_data, 4);
    memcpy(config, &saved_data[4], sizeof(CONFIG_DATA));

    if (0 != memcmp(sign, SIGNATURE, 4) || config->delay_time > DELAY_TIME_MAX) {
        config->delay_time = DELAY_TIME_DEFAULT;
        config->delay_enabled = 1;
        config->midi_guy_mt_enabled = 0;
    }
}
