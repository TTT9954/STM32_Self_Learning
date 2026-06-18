#ifndef BUTTON_H
#define BUTTON_H

#include "std_type.h"
#include "gpio.h"


void button_init();

void button_execution();

extern u8 option;
extern u8 option1;
extern u16 but_timing;
extern u8 but_count;
#endif