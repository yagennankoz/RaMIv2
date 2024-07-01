#ifndef _MODE_DELAY_TIME_HPP_
#define _MODE_DELAY_TIME_HPP_

#include "ModeBase.hpp"

class ModeDelayTime : public ModeBase {
    public:
        ModeDelayTime() {}
        ModeDelayTime(CONFIG_DATA*);
        ~ModeDelayTime() {}
        void init();
        void onRotate(int8_t);
        uint8_t onCancel();
        uint8_t onOK();
        void print(Adafruit_SSD1306 *);

    private:
        int8_t  chosen;
};

#endif