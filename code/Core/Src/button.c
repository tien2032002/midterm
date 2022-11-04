/*
 * button.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Administrator
 */

#include "main.h"
#include "button.h"
#include <math.h>


static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1 [N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2 [N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3 [N0_OF_BUTTONS];

int flagForButtonPress [N0_OF_BUTTONS];
int flagForButtonPress1s [N0_OF_BUTTONS];
int counterForButtonPress1s [N0_OF_BUTTONS];

void reset_button_buffer() {
	for (int i=0;i<N0_OF_BUTTONS;i++) {
		buttonBuffer[i]=BUTTON_IS_RELEASED;
		debounceButtonBuffer1[i]=BUTTON_IS_RELEASED;
		debounceButtonBuffer2[i]=BUTTON_IS_RELEASED;
		debounceButtonBuffer3[i]=BUTTON_IS_RELEASED;
		flagForButtonPress[i]=0;
		flagForButtonPress1s[i]=0;
		counterForButtonPress1s[i]=DURATION_FOR_AUTO_INCREASING;
	}
}
void button_reading ( void ){
	for ( int i = 0; i < N0_OF_BUTTONS ; i ++){
		debounceButtonBuffer3 [i] = debounceButtonBuffer2 [i];
		debounceButtonBuffer2 [i] = debounceButtonBuffer1 [i];
		debounceButtonBuffer1 [i] = HAL_GPIO_ReadPin(GPIOA, BUTTON1_Pin*pow(2,i));
		if( debounceButtonBuffer1 [i] == debounceButtonBuffer2 [i] && debounceButtonBuffer2[i]==debounceButtonBuffer3[i]) {
			if (buttonBuffer[i] != debounceButtonBuffer3 [i]) {
				buttonBuffer [i] = debounceButtonBuffer3 [i];
				if( buttonBuffer [i] == BUTTON_IS_PRESSED ){
					flagForButtonPress [i]=1;
					counterForButtonPress1s [i]=DURATION_FOR_AUTO_INCREASING;
				}
			}
			else {
				if (buttonBuffer[i]==BUTTON_IS_PRESSED) {
					counterForButtonPress1s [i]--;
					if (counterForButtonPress1s[i]<=0) {
						flagForButtonPress1s[i]=1;
						buttonBuffer[i]=0;
					}
				}
			}
		}
	}
}


