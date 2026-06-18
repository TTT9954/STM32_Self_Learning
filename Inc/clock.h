#ifndef CLOCK_H
#define CLOCK_H

#include "std_type.h"

#define RCC_AHB1ENR_ADDR 0x40023830
#define RCC_APB1ENR_ADDR 0x40023840

extern volatile u32 *const RCC_AHB1ENR;
extern volatile u32 *const RCC_APB1ENR;

void clock_enable();

#endif