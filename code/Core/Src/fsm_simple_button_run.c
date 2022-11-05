/*
 * fsm_simple_button_run.c
 *
 *  Created on: Nov 5, 2022
 *      Author: Administrator
 */

#include "fsm_simple_button_run.h"
#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "7seg.h"

int status=0;
int counter=0;

void fsm_simple_button_run() {
	switch (status) {
	case INIT:
		status=NO_BUTTON_PRESS;
		break;

	case NO_BUTTON_PRESS:
		display7SEG(counter);

		if (timer3_flag==1) {
			setTimer4(100);
			setTimer3(0);
			status=AUTO_DECREASING;
			break;
		}

		if (flagForButtonPress[RESET_IDX]==1) {
			flagForButtonPress[RESET_IDX]=0;
			status=RESET_PRESS;
		}

		else if(flagForButtonPress[INC_IDX]==1) {
			flagForButtonPress[INC_IDX]=0;
			status=INC_PRESS;
		}

		else if (flagForButtonPress1s[INC_IDX]==1) {
			setTimer2(100);
			counter++;
			if (counter>=10) counter=0;
			status=INC_LONG_PRESS;
		}

		else if (flagForButtonPress1s[DEC_IDX]==1) {
			setTimer2(100);
			counter--;
			if (counter<0) counter=9;
			status=DEC_LONG_PRESS;
		}

		else if(flagForButtonPress[DEC_IDX]==1) {
			flagForButtonPress[DEC_IDX]=0;
			status=DEC_PRESS;
		}
		break;

	case RESET_PRESS:
		counter=0;
		setTimer3(1000);
		status=NO_BUTTON_PRESS;
		break;

	case INC_PRESS:
		counter++;
		if (counter>=10) counter=0;
		setTimer3(1000);
		status=NO_BUTTON_PRESS;
		break;

	case DEC_PRESS:
		counter--;
		if (counter<0) counter=9;
		setTimer3(1000);
		status=NO_BUTTON_PRESS;
		break;

	case INC_LONG_PRESS:
		display7SEG(counter);
		if (flagForButtonPress1s[INC_IDX]==0) {
			setTimer3(1000);
			status=NO_BUTTON_PRESS;
			setTimer2(0);
		}
		if (timer2_flag==1) {
			setTimer2(100);
			counter++;
			if (counter>=10) counter=0;
		}
		break;

	case DEC_LONG_PRESS:
		display7SEG(counter);
		if (flagForButtonPress1s[DEC_IDX]==0) {
			setTimer3(1000);
			status=NO_BUTTON_PRESS;
			setTimer2(0);
		}
		if (timer2_flag==1) {
			setTimer2(100);
			counter--;
			if (counter<0) counter=9;
		}
		break;

	case AUTO_DECREASING:
		display7SEG(counter);
		if (timer4_flag==1) {
			setTimer4(100);
			counter--;
			if (counter<=0) {
				counter=0;
				setTimer4(0);
				status=NO_BUTTON_PRESS;
			}
		}
		if(flagForButtonPress[INC_IDX]==1) {
			flagForButtonPress[INC_IDX]=0;
			status=INC_PRESS;
		}

		else if(flagForButtonPress[DEC_IDX]==1) {
			flagForButtonPress[DEC_IDX]=0;
			status=DEC_PRESS;
		}
		break;
	}
}
