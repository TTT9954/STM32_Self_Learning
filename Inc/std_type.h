#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdint.h>

#define b_FALSE             0
#define b_TRUE              !b_FALSE

#define u_ZERO              0U     
#define u_ONE             	1U        
#define u_TWO               2U
#define u_THREE             3U
#define u_FOUR              4U
#define u_FIVE              5U
#define u_FIFTHTEEN         15U

//shift constant
#define u_SHIFT_TWO         u_TWO
#define u_SHIFT_THREE       u_THREE
#define u_SHIFT_FIFTHTEEN   u_FIFTHTEEN 

#define MAX_U8				0xFF
#define MAX_U16				0xFFFF
#define MAX_U32				0xFFFFFFFF

#define PIN_0				(1 << 0)
#define PIN_1				(1 << 1)
#define PIN_2				(1 << 2)
#define PIN_3				(1 << 3)
#define PIN_4				(1 << 4)
#define PIN_5				(1 << 5)
#define PIN_6				(1 << 6)
#define PIN_7				(1 << 7)
#define PIN_8				(1 << 8)
#define PIN_9				(1 << 9)
#define PIN_10				(1 << 10)
#define PIN_11				(1 << 11)
#define PIN_12				(1 << 12)
#define PIN_13				(1 << 13)
#define PIN_14				(1 << 14)
#define PIN_15				(1 << 15)

#define DELAY(x)  do { \
    					for(u32 i = 0; i < (x); i++) { \
        				__asm volatile("NOP"); \
    					} \
					} while(0)
                    
#define SHIFT_BIT(out, value, bitpos)     (out = (value << bitpos))

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef void (*pFunc)(u16);
#endif