#ifndef _MODE_RESET_HPP_
#define _MODE_RESET_HPP_

#include "ModeBase.hpp"

class ModeReset : public ModeBase {
    public:
        ModeReset() {}
        ModeReset(CONFIG_DATA*);
        ~ModeReset() {}
        void init();
        void onRotate(int8_t);
        uint8_t onCancel();
        uint8_t onOK();
        void print(Adafruit_SSD1306 *);

    private:
        int8_t  chosen;
};

#endif