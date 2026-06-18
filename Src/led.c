#include "led.h"
#include "gpio.h"
#include "timer.h"

LED_DATA led_data[4] = 
        { 
		  {LED_1, LED_OFF, b_FALSE},
	      {LED_2, LED_OFF, b_FALSE},
		  {LED_3, LED_OFF, b_FALSE},
		  {LED_4, LED_OFF, b_FALSE}    
	    };


u8 brightness[MAX_BRIGHT] = 
						{
							0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
    						10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    						20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    						30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
    						40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    						50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    						60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    						70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    						80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    						90, 91, 92, 93, 94, 95, 96, 97, 98, 99
						};


u8 brightness1[4] = 
						{
							1, 5, 20, 99
						};

GPIOx pGPIOD;


u32 led_timing_current;
u32 led_timing_last;
u16 led_shift;
u32 ramp_time;
u32 shift_time;

_Bool is_initialized;

static u16 save_led = 0;
static u8 duty;
static u8 i = 0;
static u8 count_shift = 0;
static u8 led_chase_count = 4;

static u8 chase_mode_time;
void led_init()
{   
	
	pGPIOD.reg = GPIOD;
	pGPIOD.pin = 12;
	pGPIOD.moder_type = OUTPUT;
	//pGPIOD->af_type = AF15;
	gpio_handle(&pGPIOD);
	pGPIOD.pin = 13;
	pGPIOD.moder_type = OUTPUT;
	gpio_handle(&pGPIOD);
	pGPIOD.pin = 14;
	pGPIOD.moder_type = OUTPUT;
	gpio_handle(&pGPIOD);
	pGPIOD.pin = 15;
	pGPIOD.moder_type = OUTPUT;
	gpio_handle(&pGPIOD);
}

void led_deInit()
{
    pGPIOD.reg->ODR.numb_pin &= ~(0xF000);
}

void led_toggle(u16 speed_toggle)
{
    if(!is_initialized)
    {
        led_deInit();
        is_initialized = b_TRUE;
    }

    if((led_timing_current - led_timing_last) >= speed_toggle)
	{
        led_timing_last = led_timing_current;
		led_data[0].flag = b_TRUE;
		led_data[1].flag = b_TRUE;
		led_data[2].flag = b_TRUE;
		led_data[3].flag = b_TRUE;
	}

	if(led_data[0].flag)
	{
		led_data[0].status = (led_data[0].status == LED_ON) ? LED_OFF : LED_ON;
        pGPIOD.reg->ODR.numb.PIN12 = led_data[0].status;
		led_data[0].flag = b_FALSE;
	}
	if(led_data[1].flag)
	{
		led_data[1].status = (led_data[1].status == LED_ON) ? LED_OFF : LED_ON;
        pGPIOD.reg->ODR.numb.PIN13 = led_data[1].status;
		led_data[1].flag = b_FALSE;
	}
	if(led_data[2].flag)
	{
		led_data[2].status = (led_data[2].status == LED_ON) ? LED_OFF : LED_ON;
        pGPIOD.reg->ODR.numb.PIN14 = led_data[2].status;
		led_data[2].flag = b_FALSE;
	}
	if(led_data[3].flag)
	{
		led_data[3].status = (led_data[3].status == LED_ON) ? LED_OFF : LED_ON;
        pGPIOD.reg->ODR.numb.PIN15 = led_data[3].status;
		led_data[3].flag = b_FALSE;
	}

}

void meteor_shower_effect(u16 speed_meteor)
{

    // 1. Initialize the meteor values ONCE, not on every function call
    if (is_initialized == b_FALSE)
    {
        brightness1[3] =  brightness[99];
        brightness1[2] =  brightness[20];
        brightness1[1] =  brightness[5];
        brightness1[0] =  brightness[1];
        is_initialized = b_TRUE;
    }

    if((led_timing_current - led_timing_last) >= speed_meteor)
    {
        u8 ds = brightness1[3]; 
        
        for(u8 CountLed = 3; CountLed > 0; CountLed--)
        {
            brightness1[CountLed] = brightness1[CountLed - 1];
        }   
        
        brightness1[0] = ds;
        led_timing_last = led_timing_current; 
    }

    // LED 1
	if(count_TIM < brightness1[0]) pGPIOD.reg->ODR.numb.PIN12 = LED_ON;
   	else pGPIOD.reg->ODR.numb.PIN12 = LED_OFF;
	// LED 2
	if(count_TIM < brightness1[1]) pGPIOD.reg->ODR.numb.PIN13 = LED_ON;
   	else pGPIOD.reg->ODR.numb.PIN13 = LED_OFF;
	
	//LED 3
	if(count_TIM < brightness1[2]) pGPIOD.reg->ODR.numb.PIN14 = LED_ON;
   	else pGPIOD.reg->ODR.numb.PIN14 = LED_OFF;
	
	// LED 4
	if(count_TIM < brightness1[3]) pGPIOD.reg->ODR.numb.PIN15 = LED_ON;
   	else  pGPIOD.reg->ODR.numb.PIN15 = LED_OFF;	
}

void led_breathing_ramp_reset()
{
    i = 0;
    for(u8 ch = 0; ch < 4; ch++)
    {
        led_data[ch].dir = UP;
        led_data[ch].led_bright = 0;
    }
}

void led_breathing_ramp(u16 speed_ramp)
{
	if((led_timing_current - led_timing_last) > speed_ramp)
	{   
        led_timing_last = led_timing_current;
        if(led_data[i].dir == UP)
        {
            // FIXED: If it approaches or somehow exceeds MAX_BRIGHT, switch direction immediately
            if(led_data[i].led_bright >= (MAX_BRIGHT - 1)) 
            {
                led_data[i].led_bright = MAX_BRIGHT - 1; // Cap it at absolute peak
                led_data[i].dir = DOWN;                           // Force transition to ramp down
            }
            else 
            {
                led_data[i].led_bright++;
            }
        }
        else // dir[i] == DOWN
        {
            // FIXED: Safe boundary check for zero floor limits
            if(led_data[i].led_bright <= 0) 
            {
                led_data[i].led_bright = 0;  // Cap it at absolute zero
                led_data[i].dir = UP;                 // Reset current index direction flag back to UP
                i = (i >= 3) ? 0 : (i+1);
            }
            else 
            {
                led_data[i].led_bright--;
            }
        }
    }

    // LED 1
	if(count_TIM < led_data[0].led_bright) pGPIOD.reg->ODR.numb.PIN12 = LED_ON;
   	else pGPIOD.reg->ODR.numb.PIN12 = LED_OFF;
	// LED 2
	if(count_TIM < led_data[1].led_bright) pGPIOD.reg->ODR.numb.PIN13 = LED_ON;
   	else pGPIOD.reg->ODR.numb.PIN13 = LED_OFF;
	
	//LED 3
	if(count_TIM < led_data[2].led_bright) pGPIOD.reg->ODR.numb.PIN14 = LED_ON;
   	else pGPIOD.reg->ODR.numb.PIN14 = LED_OFF;
	
	// LED 4
	if(count_TIM < led_data[3].led_bright) pGPIOD.reg->ODR.numb.PIN15 = LED_ON;
   	else  pGPIOD.reg->ODR.numb.PIN15 = LED_OFF;	
}

void led_chaser_reset()
{
    save_led = 0;
    led_shift = 0;
    count_shift = 0;
    led_chase_count = 4;
    chase_mode_time = 0;
}

void led_chaser(u16 speed_chaser)
{
    if((led_timing_current - led_timing_last) >= speed_chaser)
    {   
        led_timing_last = led_timing_current;
        led_shift <<= 1;
        if(led_shift > LED4_PIN || led_shift <= LED1_PIN)
        {
            led_shift = (LED1_PIN);
        }       
        pGPIOD.reg->ODR.numb_pin = led_shift;
    }   
}

void led_chaser1(u16 speed_chaser)
{
    if(ramp_time > 20)
    {   
        if(++duty >= MAX_BRIGHT) duty = 0;
        ramp_time = 0;
    } 

    if(count_TIM < brightness[duty]) 
    {
        pGPIOD.reg->ODR.numb_pin |= save_led;   
    }
    else pGPIOD.reg->ODR.numb_pin &= ~save_led;

    if((led_timing_current - led_timing_last) > speed_chaser)
    {
        led_timing_last = led_timing_current;
        if(led_shift == u_ZERO)
        {
            led_shift = LED1_PIN;
        }
        else
        {         
            pGPIOD.reg->ODR.numb_pin = (save_led | led_shift); 
        
            if(led_chase_count == 0)
            {
                pGPIOD.reg->ODR.numb_pin &= ~(0xF000);
                led_chase_count = 4;    
                save_led = 0;            
                led_shift = LED1_PIN;    
                count_shift = 0;         
            }
            else 
            {
                if(count_shift < (led_chase_count-1))
                {
                    count_shift++;
                    led_shift <<= 1; 
                }
                else
                {
                    save_led |= led_shift;   
                    led_shift = LED1_PIN;    
                    count_shift = 0;        
                    led_chase_count--;      
                }                
            }
        }

    }  
}

void led_snake(u16 speed_craw)
{
        if(ramp_time > 20)
    {   
        if(++duty >= MAX_BRIGHT) duty = 0;
        ramp_time = 0;
    } 

    if(count_TIM < brightness[duty]) 
    {
        pGPIOD.reg->ODR.numb_pin = save_led;   
    }
    else pGPIOD.reg->ODR.numb_pin &= ~(0xF000);

    if((led_timing_current - led_timing_last) > speed_craw)
    {
        led_timing_last = led_timing_current;
        pGPIOD.reg->ODR.numb_pin = save_led;

        if(led_shift == 0) 
        {
            led_shift = LED1_PIN;
            save_led = led_shift;
        }
        else if(led_shift < (LED2_PIN | LED1_PIN))
        {
            save_led = (save_led  & 0xF000) | (led_shift);
            led_shift <<= 1;
        }
        else 
        {    
            if((save_led & 0xF000) == (LED3_PIN | LED4_PIN))
            {
                save_led <<= 1;
            }
            else if((save_led & LED4_PIN))
            {
                save_led = u_ZERO;
                led_shift = u_ZERO;
            }
            else save_led <<= 1;
        }
    }
}