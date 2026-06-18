#include "gpio.h"
#include "led.h"
#include "std_type.h"
#include "timer.h"
#include "clock.h"
#include "nvic.h"
#include "button.h"

void TIM2_IRQHandler(void);


pFunc FuncList[6] = {
					meteor_shower_effect, led_breathing_ramp, 
	                led_toggle, led_chaser, led_chaser1,
					    led_snake
				     };

int main(void)
{
	clock_enable();
	led_init();
	nvic_init(28, 1);
	timer2_init();
	button_init();
	
	while(1)
	{
		// Overflow inhibition
		if(led_timing_current == MAX_U32) led_timing_current = 0;
		if(led_timing_last == MAX_U32)    led_timing_last = 0;
		if(shift_time == MAX_U32) 		  shift_time = 0;

        if (is_initialized == b_FALSE)
        {
            led_deInit();
			led_chaser_reset();
			led_breathing_ramp_reset();
            is_initialized = b_TRUE;
			shift_time = 0;
			led_timing_current = 0;
			led_timing_last = 0;
			ramp_time = 0;
        }

		switch (option)
		{
		case 0:
			FuncList[option](2000);
			break;
		case 1:
			FuncList[option](20);
			break;
		case 2:
			FuncList[option](1500);
			break;
		case 3:
			FuncList[option](1500);
		case 4:
			FuncList[option](2000);
		case 5:
			FuncList[option](5000);
		default:
			break;
		}
	}
    return 0;
}


void TIM2_IRQHandler(void)
{
    if (*TIM2_SR & 1)
    {
        *TIM2_SR &= ~1;     // Clear UIF

		button_execution();

		if(option >= u_ZERO && option <= u_FIVE)
		{
			++led_timing_current;	
		}
		else led_timing_current = 0;

		++ramp_time;
		count_TIM = (count_TIM >= 100) ? 0 : (count_TIM+1);
    }
}
