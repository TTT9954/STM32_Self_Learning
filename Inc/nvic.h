#ifndef NVIC_H
#define NVIC_H

#include "std_type.h"

#define NVIC_BASE_ADDR    0xE000E000
#define NVIC_ISER0_ADDR   (NVIC_BASE_ADDR + 0x100)

extern volatile u32 *p_NVIC_ISERx;
extern volatile u32 *const p_NVIC_ICER0; 
extern volatile u32 *p_NVIC_IPRx; 

void nvic_init(u8 IRQ_Numb, u8 Priority);
#endif 