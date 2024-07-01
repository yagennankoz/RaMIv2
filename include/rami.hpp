#ifndef _RAMI_HPP_
#define _RAMI_HPP_

#include <stdio.h>
#include "const.hpp"

typedef struct {
    uint8_t data;
    uint32_t counter;
} note;


void setup_gpio();
static void midi_out();
static void midi_in_callback();
static void cancel_callback();
static void ok_callback();
static void rotary_callback();
static void save_setting();
static void load_setting();
static void print_delay(uint32_t delay_new);


#endif