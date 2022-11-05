/*
 * led_blinky.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Administrator
 */

#include "main.h"
#include "led_blinky.h"
#include "software_timer.h"

int led_status=0;

void led_blinky() {
	switch (led_status){
	case ON:
		HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_SET);
		if (timer5_flag==1) {
			setTimer5(100);
			led_status=OFF;
		}
		break;
	case OFF:
		HAL_GPIO_WritePin(GPIOA, LED_Pin, GPIO_PIN_RESET);
		if (timer5_flag==1 ) {
			setTimer5(100);
			led_status=ON;
		}

		break;
	default:
		break;
	}

}
