#include "util.hpp"
#include "ModeDelaySw.hpp"


static CONFIG_DATA* config;

ModeDelaySw::ModeDelaySw(CONFIG_DATA *in_config) {
    config = in_config;
}

void ModeDelaySw::init() {
    chosen = config->delay_enabled;
    reprint = 1;
}


void ModeDelaySw::onRotate(int8_t rot) {
    if (!rot) {
        return;
    }
    
    if (rot > 0) {
        chosen = config->delay_enabled = 1;
    } else if (rot < 0) {
        chosen = config->delay_enabled = 0;
    }
    reprint = 1;
}


uint8_t ModeDelaySw::onCancel() {
    load_setting(config);
    return MODE_CONFIG;
}


uint8_t ModeDelaySw::onOK() {
    save_setting(config);
    return MODE_CONFIG;
}


void ModeDelaySw::print(Adafruit_SSD1306 *oled) {
    if (!reprint) {
        return;
    }

    const char menu_item[] = "OFF\0ON";
    print_menu( oled, (const char*)"SETUP DELAY SW", 2, menu_item, chosen );
    reprint = 0;
}