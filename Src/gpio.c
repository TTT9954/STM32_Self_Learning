#include "gpio.h"


void gpio_handle(GPIOx *In_GPIOx)
{
    u64 temp_reg = 0;

    In_GPIOx->reg->MODER &= ~(u_THREE << In_GPIOx->pin * u_TWO);
    temp_reg = (u64)In_GPIOx->moder_type << (In_GPIOx->pin * u_TWO);
    In_GPIOx->reg->MODER |= (u32)temp_reg;

    temp_reg = 0U; 
    
    if(In_GPIOx->moder_type == AF)
    {
        switch(In_GPIOx->pin)
        {
            case 0:  In_GPIOx->reg->AFR.numb.PIN0  = In_GPIOx->af_type; break;
            case 1:  In_GPIOx->reg->AFR.numb.PIN1  = In_GPIOx->af_type; break;
            case 2:  In_GPIOx->reg->AFR.numb.PIN2  = In_GPIOx->af_type; break;
            case 3:  In_GPIOx->reg->AFR.numb.PIN3  = In_GPIOx->af_type; break;
            case 4:  In_GPIOx->reg->AFR.numb.PIN4  = In_GPIOx->af_type; break;
            case 5:  In_GPIOx->reg->AFR.numb.PIN5  = In_GPIOx->af_type; break;
            case 6:  In_GPIOx->reg->AFR.numb.PIN6  = In_GPIOx->af_type; break;
            case 7:  In_GPIOx->reg->AFR.numb.PIN7  = In_GPIOx->af_type; break;
            case 8:  In_GPIOx->reg->AFR.numb.PIN8  = In_GPIOx->af_type; break;
            case 9:  In_GPIOx->reg->AFR.numb.PIN9  = In_GPIOx->af_type; break;
            case 10: In_GPIOx->reg->AFR.numb.PIN10 = In_GPIOx->af_type; break;
            case 11: In_GPIOx->reg->AFR.numb.PIN12 = In_GPIOx->af_type; break;
            case 12: In_GPIOx->reg->AFR.numb.PIN11 = In_GPIOx->af_type; break; 
            case 13: In_GPIOx->reg->AFR.numb.PIN13 = In_GPIOx->af_type; break;
            case 14: In_GPIOx->reg->AFR.numb.PIN14 = In_GPIOx->af_type; break;
            case 15: In_GPIOx->reg->AFR.numb.PIN15 = In_GPIOx->af_type; break;
            default: break;
        }
    }  
    
    temp_reg = 0U;
    In_GPIOx->reg->PUPDR &= ~(u_THREE << In_GPIOx->pin * u_TWO);
    temp_reg = (u64)In_GPIOx->pupd_type << (In_GPIOx->pin * u_TWO);
    In_GPIOx->reg->PUPDR |= (u32)temp_reg;   
    
    
}