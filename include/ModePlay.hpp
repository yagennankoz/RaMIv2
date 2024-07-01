#ifndef _MODE_PLAY_HPP_
#define _MODE_PLAY_HPP_

#include "ModeBase.hpp"

#define DISPLAY_DURATION    (15000000u)

class ModePlay : public ModeBase {
    public:
        ModePlay() {}
        ~ModePlay() {}
        void init();
        uint8_t onCancel();
        uint8_t onOK();
        void print(Adafruit_SSD1306 *);
        void set_display_msg_at(uint32_t);
    private:
        uint32_t display_msg_at;
};

#endif