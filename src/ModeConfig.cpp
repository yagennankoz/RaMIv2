#include "util.hpp"
#include "ModeConfig.hpp"

void ModeConfig::init() {
    chosen = 0;
    reprint = 1;
}


void ModeConfig::onRotate(int8_t rot) {
    if (!rot) {
        return;
    }
    
    if (rot > 0) {
        chosen++;
        if (chosen > 3) {
            chosen = 3;
        }
    } else if (rot < 0) {
        chosen--;
        if (chosen < 0) {
            chosen = 0;
        }
    }
    reprint = 1;
}


uint8_t ModeConfig::onCancel() {
    return MODE_PLAY;
}


uint8_t ModeConfig::onOK() {
    uint8_t mode;
    switch (chosen) {
        case 0:
            mode = MODE_DELAY_SW;
            break;
        case 1:
            mode = MODE_DELAY_TIME;
            break;
        case 2:
            mode = MODE_MIDIGUY;
            break;
        case 3:
            mode = MODE_RESET;
            break;
        default:
            mode = MODE_PLAY;
    }
    return mode;
}


void ModeConfig::print(Adafruit_SSD1306 *oled) {
    if (!reprint) {
        return;
    }

    const char menu_item[] = "DELAY SW\0DELAY TIME\0MIDIGUY MT\0RESET\0";
    print_menu( oled, (const char*)"SETUP", 4, menu_item, chosen );
    reprint = 0;
}