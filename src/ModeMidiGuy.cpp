#include "util.hpp"
#include "ModeMidiGuy.hpp"


static CONFIG_DATA* config;

ModeMidiGuy::ModeMidiGuy(CONFIG_DATA *in_config) {
    config = in_config;
}

void ModeMidiGuy::init() {
    chosen = config->midi_guy_mt_enabled;
    reprint = 1;
}


void ModeMidiGuy::onRotate(int8_t rot) {
    if (!rot) {
        return;
    }
    
    if (rot > 0) {
        chosen = config->midi_guy_mt_enabled = 1;
    } else if (rot < 0) {
        chosen = config->midi_guy_mt_enabled = 0;
    }
    reprint = 1;
}


uint8_t ModeMidiGuy::onCancel() {
    load_setting(config);
    return MODE_CONFIG;
}


uint8_t ModeMidiGuy::onOK() {
    save_setting(config);
    return MODE_CONFIG;
}


void ModeMidiGuy::print(Adafruit_SSD1306 *oled) {
    if (!reprint) {
        return;
    }

    const char menu_item[] = "OFF\0ON";
    print_menu( oled, (const char*)"SETUP MIDIGUY MT", 2, menu_item, chosen );
    reprint = 0;
}