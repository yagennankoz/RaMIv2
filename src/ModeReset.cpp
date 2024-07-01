#include "util.hpp"
#include "ModeReset.hpp"


static CONFIG_DATA* config;

ModeReset::ModeReset(CONFIG_DATA *in_config) {
    config = in_config;
}

void ModeReset::init() {
    chosen = 1;
    reprint = 1;
}


void ModeReset::onRotate(int8_t rot) {
    if (!rot) {
        return;
    }
    
    if (rot > 0) {
        chosen = 1;
    } else if (rot < 0) {
        chosen = 0;
    }
    reprint = 1;
}


uint8_t ModeReset::onCancel() {
    return MODE_CONFIG;
}


uint8_t ModeReset::onOK() {
    if (chosen == 0) {
        config->delay_enabled = 1;
        config->delay_time = DELAY_TIME_DEFAULT;
        save_setting(config);
    }
    return MODE_CONFIG;
}


void ModeReset::print(Adafruit_SSD1306 *oled) {
    if (!reprint) {
        return;
    }

    const char menu_item[] = "YES\0NO";
    print_menu( oled, (const char*)"SETUP RESET", 2, menu_item, chosen );
    reprint = 0;
}