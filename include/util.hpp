#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <stdio.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <hardware/flash.h>

#include "const.hpp"

void print_menu(Adafruit_SSD1306*, const char*, uint8_t, const char*, int8_t);
uint8_t isEventAvailable();
void save_setting(CONFIG_DATA *);
void load_setting(CONFIG_DATA *);

#endif