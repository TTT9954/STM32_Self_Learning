#include "timer.h"


volatile u32 *const TIM2_CR1 = (u32*) TIM2_BASE_ADDR;
volatile u32 *const TIM2_SR =  (u32*) TIM2_SR_ADDR;
volatile u32 *const TIM2_CNT = (u32*) (TIM2_BASE_ADDR + 0x24);
volatile u32 *const TIM2_ARR = (u32*) (TIM2_BASE_ADDR + 0x2C);
volatile u32 *const TIM2_DIER = (u32*) (TIM2_BASE_ADDR + 0x0C);
volatile u32 *const TIM2_PSC = (u32*) (TIM2_BASE_ADDR + 0x28);
volatile u32 *const TIM2_EGR = (u32*) (TIM2_BASE_ADDR + 0x14);

volatile u32 count_TIM = 0;
volatile u32 count1_TIM = 0;
void timer2_init()
{
    *TIM2_CR1 |= (1 << 0); // counter enable;
    *TIM2_DIER |= (1 << 0); // enable Timer interupt 
    *TIM2_ARR = (u32)0x50; // auto-preload = 999
    *TIM2_CNT = 0x00; // counter from 0
    *TIM2_PSC = 0x0F; // 15999
    *TIM2_EGR |=  (1 << 0); //Re-initialize counter and psc
}