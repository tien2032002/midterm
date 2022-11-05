/*
 * button.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Administrator
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define N0_OF_BUTTONS 3
#define DURATION_FOR_AUTO_INCREASING 300
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

#define RESET_IDX		0
#define INC_IDX			1
#define DEC_IDX			2

void button_reading ( void );
void reset_button_buffer();

extern int flagForButtonPress[N0_OF_BUTTONS];
extern int flagForButtonPress1s[N0_OF_BUTTONS];
extern int flagForButtonDoublePress [N0_OF_BUTTONS];

extern int flagForPressed;

#endif /* INC_BUTTON_H_ */
