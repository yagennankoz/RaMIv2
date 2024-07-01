#ifndef _MODE_BASE_HPP_
#define _MODE_BASE_HPP_

#include <stdio.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include "const.hpp"

class ModeBase {
    public:
        ModeBase() {}
        ~ModeBase() {}
        virtual void init();
        virtual void setMsg(const char*);
        virtual void clearMsg();
        virtual void onRotate(int8_t);
        virtual uint8_t onCancel();
        virtual uint8_t onOK();
        virtual void print(Adafruit_SSD1306 *);
    
    protected:
        char *msg;
        uint8_t reprint;
};

#endif