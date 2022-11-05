/*
 * button.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Administrator
 */

#include "main.h"
#include "button.h"
#include <math.h>
#include "software_timer.h"


static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1 [N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2 [N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3 [N0_OF_BUTTONS];

int flagForButtonPress [N0_OF_BUTTONS];
int flagForButtonPress3s [N0_OF_BUTTONS];
int flagForButtonDoublePress [N0_OF_BUTTONS];
int counterForButtonPress3s [N0_OF_BUTTONS];

void reset_button_buffer() {
	for (int i=0;i<N0_OF_BUTTONS;i++) {
		buttonBuffer[i]=BUTTON_IS_RELEASED;
		debounceButtonBuffer1[i]=BUTTON_IS_RELEASED;
		debounceButtonBuffer2[i]=BUTTON_IS_RELEASED;
		debounceButtonBuffer3[i]=BUTTON_IS_RELEASED;
		flagForButtonPress[i]=0;
		flagForButtonPress3s[i]=0;
		counterForButtonPress3s[i]=DURATION_FOR_AUTO_INCREASING;
	}
}
int flagForPressed=0;
void button_reading ( void ){
	for ( int i = 0; i < N0_OF_BUTTONS ; i ++){
		if(timer1_flag==1) {
			flagForPressed=0;
			setTimer1(0);
		}
		debounceButtonBuffer3 [i] = debounceButtonBuffer2 [i];
		debounceButtonBuffer2 [i] = debounceButtonBuffer1 [i];
		debounceButtonBuffer1 [i] = HAL_GPIO_ReadPin(GPIOA, RESET_Pin*pow(2,i));
		if (buttonBuffer[i]==BUTTON_IS_RELEASED) {
			flagForButtonPress3s[i]=0;
			counterForButtonPress3s[i]=0;
		}
		if( debounceButtonBuffer1 [i] == debounceButtonBuffer2 [i] && debounceButtonBuffer2[i]==debounceButtonBuffer3[i]) {
			if (buttonBuffer[i] != debounceButtonBuffer3 [i]) {
				buttonBuffer [i] = debounceButtonBuffer3 [i];
				if( buttonBuffer [i] == BUTTON_IS_PRESSED ){
					flagForButtonPress [i]=1;
					counterForButtonPress3s [i]=DURATION_FOR_AUTO_INCREASING;
					if (flagForPressed==0) {
						setTimer1(50);
						flagForPressed=0;
					}
					else {
						flagForButtonDoublePress[i]=1;
						flagForPressed=0;
						setTimer1(0);
					}
				}
			}
			else {
				if (buttonBuffer[i]==BUTTON_IS_PRESSED) {
					counterForButtonPress3s [i]--;
					if (counterForButtonPress3s[i]<=0) {
						flagForButtonPress3s[i]=1;
					}
				}
			}
		}
	}
}


