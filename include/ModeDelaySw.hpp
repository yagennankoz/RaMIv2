#ifndef _MODE_DELAY_SW_HPP_
#define _MODE_DELAY_SW_HPP_

#include "ModeBase.hpp"

class ModeDelaySw : public ModeBase {
    public:
        ModeDelaySw() {}
        ModeDelaySw(CONFIG_DATA*);
        ~ModeDelaySw() {}
        void init();
        void onRotate(int8_t);
        uint8_t onCancel();
        uint8_t onOK();
        void print(Adafruit_SSD1306 *);

    private:
        int8_t  chosen;
};

#endif