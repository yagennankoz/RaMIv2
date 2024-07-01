#ifndef _MODE_MIDI_GUY_HPP_
#define _MODE_MIDI_GUY_HPP_

#include "ModeBase.hpp"

class ModeMidiGuy : public ModeBase {
    public:
        ModeMidiGuy() {}
        ModeMidiGuy(CONFIG_DATA*);
        ~ModeMidiGuy() {}
        void init();
        void onRotate(int8_t);
        uint8_t onCancel();
        uint8_t onOK();
        void print(Adafruit_SSD1306 *);

    private:
        int8_t  chosen;
};

#endif