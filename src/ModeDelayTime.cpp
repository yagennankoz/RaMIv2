#include "util.hpp"
#include "ModeDelayTime.hpp"


static CONFIG_DATA* config;

ModeDelayTime::ModeDelayTime(CONFIG_DATA *in_config) {
    config = in_config;
}

void ModeDelayTime::init() {
    reprint = 1;
}


void ModeDelayTime::onRotate(int8_t rot) {
    if (!rot) {
        return;
    }
    
    if (rot > 0) {
        config->delay_time += 100;
    } else if (rot < 0) {
        config->delay_time -= 100;
        if (config->delay_time < 0) {
            config->delay_time = 0;
        }
    }
    reprint = 1;
}


uint8_t ModeDelayTime::onCancel() {
    load_setting(config);
    return MODE_CONFIG;
}


uint8_t ModeDelayTime::onOK() {
    save_setting(config);
    return MODE_CONFIG;
}


void ModeDelayTime::print(Adafruit_SSD1306 *oled) {
    if (!reprint) {
        return;
    }
    oled->clearDisplay();
    oled->setTextColor(SSD1306_WHITE);
    oled->setTextSize(1);
    oled->setCursor(124-6*16, 0);
    oled->print("SETUP DELAY TIME");
    oled->drawLine(0,10, 127,10, SSD1306_WHITE);
    oled->drawLine(0,12, 127,12, SSD1306_WHITE);
    oled->setTextSize(2);
    oled->setCursor(20,28);
    oled->printf("%.1f ms", ((float_t)(config->delay_time)) / 1000);
    oled->display();   
    reprint = 0;
}