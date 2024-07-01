#ifndef _MODE_CONFIG_HPP_
#define _MODE_CONFIG_HPP_

#include "ModeBase.hpp"

class ModeConfig : public ModeBase {
    public:
        ModeConfig() {}
        ~ModeConfig() {}
        void init();
        void onRotate(int8_t);
        uint8_t onCancel();
        uint8_t onOK();
        void print(Adafruit_SSD1306 *);

    private:
        int8_t  chosen;
};

#endif