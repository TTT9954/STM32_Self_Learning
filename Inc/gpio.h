#ifndef GPIO_H
#define GPIO_H

#include "std_type.h"


#define GPIOD_BASE_ADDR    0x40020C00
#define GPIOA_BASE_ADDR    0x40020000                           
#define GPIOA              ((GPIOx_reg *)GPIOA_BASE_ADDR)
#define GPIOD              ((GPIOx_reg *)GPIOD_BASE_ADDR)

typedef enum GPIO_pin
{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15,
}GPIO_pin;

typedef union GPIOx_ODR
{
    struct pin_numb
    {
        u32 PIN0:  1;
        u32 PIN1:  1;
        u32 PIN2:  1;
        u32 PIN3:  1;
        u32 PIN4:  1;
        u32 PIN5:  1;
        u32 PIN6:  1;
        u32 PIN7:  1;
        u32 PIN8:  1;
        u32 PIN9:  1;
        u32 PIN10: 1;
        u32 PIN11: 1;
        u32 PIN12: 1;
        u32 PIN13: 1;
        u32 PIN14: 1;
        u32 PIN15: 1;
        u32 REVERSED: 16;
    }numb;
    u32 numb_pin;
}GPIOx_ODR;

typedef struct GPIOx_IDR
{

    u32 PIN0:  1;
    u32 PIN1:  1;
    u32 PIN2:  1;
    u32 PIN3:  1;
    u32 PIN4:  1;
    u32 PIN5:  1;
    u32 PIN6:  1;
    u32 PIN7:  1;
    u32 PIN8:  1;
    u32 PIN9:  1;
    u32 PIN10: 1;
    u32 PIN11: 1;
    u32 PIN12: 1;
    u32 PIN13: 1;
    u32 PIN14: 1;
    u32 PIN15: 1;
    u32 REVERSED: 16;
}GPIOx_IDR;

typedef union GPIOx_AFR
{
    struct pin_AFR
    {
        u64 PIN0:  4;
        u64 PIN1:  4;
        u64 PIN2:  4;
        u64 PIN3:  4;
        u64 PIN4:  4;
        u64 PIN5:  4;
        u64 PIN6:  4;
        u64 PIN7:  4;
        u64 PIN8:  4;
        u64 PIN9:  4;
        u64 PIN10: 4;
        u64 PIN11: 4;
        u64 PIN12: 4;
        u64 PIN13: 4;
        u64 PIN14: 4;
        u64 PIN15: 4;
    }numb;
    u64 numb_pin;
}GPIOx_AFR;

typedef enum GPIO_Moder_Type
{
    INPUT,
    OUTPUT,
    AF,
    ANALOG
}GPIO_Moder_Type;

typedef enum GPIO_AF_Type
{
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
}GPIO_AF_Type;

typedef enum GPIO_Speed
{
    LOW,
    MED,
    HIGH,
    VERY_HIGH
}GPIO_Speed;

typedef enum GPIO_PUPDR
{
    NO_PUPD,
    PU,
    PD,
}GPIO_PUPDR;

typedef struct GPIOx_reg
{
    u32 MODER;
    u32 OTYPER;
    u32 OSPEEDR;
    u32 PUPDR;
    GPIOx_IDR IDR;
    GPIOx_ODR ODR;
    u32 BSRR;
    u32 LCKR;
    GPIOx_AFR AFR;
}GPIOx_reg;


typedef struct GPIOx
{

    GPIOx_reg       *reg;
    GPIO_pin        pin;
    GPIO_Moder_Type moder_type;
    GPIO_Speed      speed;
    GPIO_AF_Type    af_type;
    GPIO_PUPDR      pupd_type;
}GPIOx;



extern GPIOx pGPIOD;
extern GPIOx pGPIO_button;
void gpio_handle(GPIOx *In_GPIOx);

#endif