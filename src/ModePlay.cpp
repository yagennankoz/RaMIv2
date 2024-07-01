#include "ModePlay.hpp"

void ModePlay::init() {
    clearMsg();
    display_msg_at = 0;
}


uint8_t ModePlay::onCancel() {
    clearMsg();
    display_msg_at = 0;
    return MODE_CONFIG;
}


uint8_t ModePlay::onOK() {
    clearMsg();
    display_msg_at = 0;
    return MODE_CONFIG;
}


void ModePlay::print(Adafruit_SSD1306 *oled) {
    if (msg == NULL && display_msg_at > 0) {
        uint32_t now = time_us_32();
        uint32_t elapsed = 0;
        if (now >= display_msg_at) {
            elapsed = now - display_msg_at;
        } else {
            elapsed = UINT32_MAX - display_msg_at + now;
        }
        if (elapsed > DISPLAY_DURATION) {
            oled->clearDisplay();

            set_display_msg_at(0);
        }
    } else {
        oled->clearDisplay();
        oled->setTextSize(2);
        oled->setCursor(0,0);
        oled->print(msg);
        oled->display();

        set_display_msg_at(time_us_32());
        clearMsg();
    }
}

void ModePlay::set_display_msg_at(uint32_t time) {
    display_msg_at = time;
}
