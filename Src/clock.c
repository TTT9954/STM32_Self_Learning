#include "clock.h"
#include "gpio.h"


volatile u32 *const RCC_AHB1ENR = (u32 *) RCC_AHB1ENR_ADDR;
volatile u32 *const RCC_APB1ENR = (u32 *) RCC_APB1ENR_ADDR;

void clock_enable()
{
    *RCC_AHB1ENR |= (1 << 3) | (1 << 0); //GPIODEN
    *RCC_APB1ENR |= (1 << 0); // TIM2EN
}

void clock_reset()
{
    *RCC_AHB1ENR &= ~(0xFF);
    *RCC_APB1ENR &= ~(0xFF);
}