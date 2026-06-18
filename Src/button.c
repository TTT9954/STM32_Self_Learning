#include "button.h"
#include "led.h"

u8 option;
u8 option1;
u8 but_count;
u16 but_timing;

GPIOx pGPIO_button = {
    .reg = GPIOA
};

void button_init()
{
	pGPIO_button.pin  	   = PIN0;
	pGPIO_button.moder_type = INPUT;
	pGPIO_button.speed      = LOW;
	pGPIO_button.pupd_type  = NO_PUPD; //pull-up
	gpio_handle(&pGPIO_button);
}

void button_execution()
{
    u8 current_state = pGPIO_button.reg->IDR.PIN0; 
               
    if ((current_state & PIN_0) == 1) // Button is physically pressed down
    {     
        but_timing++;
        
        if (but_timing == 100)
        {
            is_initialized = b_FALSE;
            if(++option > 5) option = 0;   
        }   
    }
    else but_timing = 0;
}