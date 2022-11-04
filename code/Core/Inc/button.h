/*
 * button.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Administrator
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define N0_OF_BUTTONS 2
#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

void button_reading ( void );
void reset_button_buffer();

extern int flagForButtonPress[N0_OF_BUTTONS];
extern int flagForButtonPress1s[N0_OF_BUTTONS];

#endif /* INC_BUTTON_H_ */
