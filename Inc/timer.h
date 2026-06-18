#ifndef TIM_H
#define TIM_H

#include "std_type.h"

#define TIM2_BASE_ADDR 0x40000000
#define TIM2_SR_ADDR (TIM2_BASE_ADDR + 0x10)

extern volatile u32 *const TIM2_CR1;
extern volatile u32 *const TIM2_SR;
extern volatile u32 *const TIM2_CNT;
extern volatile u32 *const TIM2_ARR;
extern volatile u32 *const TIM2_DIER;
extern volatile u32 count_TIM;
extern volatile u32 count1_TIM;

void timer2_init();

#endif