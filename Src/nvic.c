#include "nvic.h"


volatile u32 *p_NVIC_ISERx = (u32*)(NULL); //Interrupt set-enable register
volatile u32 *const p_NVIC_ICER0 = (u32*)(NVIC_ISER0_ADDR+0x180); //Interrupt clear-enable register x
volatile u32 *p_NVIC_IPRx = (u32*)(NULL);


void nvic_init(u8 IRQ_Numb, u8 Priority)
{
    p_NVIC_IPRx = (u32*)(NVIC_BASE_ADDR+(0x400 + (0x04 * (IRQ_Numb >> 2))));
    p_NVIC_ISERx = (u32*)(NVIC_BASE_ADDR+(0x100 + (0x04 * (IRQ_Numb >> 5))));
    u8 offset = (IRQ_Numb%4)*8;
    *p_NVIC_IPRx |= Priority << (4 + offset);
    *p_NVIC_ISERx |= (1 << IRQ_Numb);
}

void nvic_reset(u8 IRQ_Numb)
{
    *p_NVIC_ICER0 |= (1 << IRQ_Numb); // TIM2 global interrupt disable;
}