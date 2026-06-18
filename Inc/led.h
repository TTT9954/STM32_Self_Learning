#ifndef LED_H
#define LED_H

#include "std_type.h"
#include "gpio.h"

#define MAX_BRIGHT 100
#define LED1_PIN (1 << LED_1)
#define LED2_PIN (1 << LED_2)
#define LED3_PIN (1 << LED_3)
#define LED4_PIN (1 << LED_4)

typedef enum LED_STATUS
{
	LED_OFF = 0,
	LED_ON = 1
}LED_STATUS;

typedef enum DIRECTION
{
	DOWN = 0,
	UP = 1
}DIRECTION;

typedef enum LED_PINS
{
	LED_1 = 12,
	LED_2 = 13,
	LED_3 = 14,
	LED_4 = 15
}LED_PINS;

typedef struct LED_DATA
{
	LED_PINS type;
	LED_STATUS status;
	_Bool flag;
	volatile u8 led_bright;
	u8 dir;
}LED_DATA;



extern u8 brightness[MAX_BRIGHT];
extern u8 brightness1[4];

extern LED_DATA led_data[4];
extern DIRECTION direction;
extern u32 led_timing_current;
extern u32 led_timing_last;
extern _Bool is_initialized;
extern u16 led_shift;
extern u32 ramp_time;
extern u32 shift_time;
extern u32 count_toggle;

void led_init();
void led_deInit();
void led_toggle(u16 speed_toggle);
void meteor_shower_effect(u16 speed_meteor);
void led_breathing_ramp_reset();
void led_breathing_ramp(u16 speed_ramp);
void led_chaser_reset();
void led_chaser(u16 speed_chaser);
void led_chaser1(u16 speed_chaser);
void led_snake(u16 speed_craw);

#endif