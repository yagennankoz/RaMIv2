#include "ModeBase.hpp"

void ModeBase::init() {}

void ModeBase::setMsg(const char* in_msg) {
    msg = (char*)in_msg;
}

void ModeBase::clearMsg() {
    msg = NULL;
}

void ModeBase::onRotate(int8_t rot) {}

uint8_t ModeBase::onCancel() {
    return MODE_PLAY;
}

uint8_t ModeBase::onOK() {
    return MODE_PLAY;
}

void ModeBase::print(Adafruit_SSD1306 *oled) {}
