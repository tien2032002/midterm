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
		//trang thai ban dau cua may
		status=NO_BUTTON_PRESS;
		break;

	case NO_BUTTON_PRESS:
		//hiển thị led
		display7SEG(counter);

		//set timer để về chế độ AUTO_DEACREASING
		if (timer3_flag==1) {
			//set timer để đếm lùi sau 1s
			setTimer4(100);

			//clear timer 3
			setTimer3(0);

			//qua trạng thái đếm lùi
			status=AUTO_DECREASING;
			break;
		}

		//ấn nút reset
		if (flagForButtonPress[RESET_IDX]==1) {
			//reset flag
			flagForButtonPress[RESET_IDX]=0;

			//chuyển trạng thái
			status=RESET_PRESS;
		}

		//ấn nút INC, tương tự nút reset
		else if(flagForButtonPress[INC_IDX]==1) {
			flagForButtonPress[INC_IDX]=0;
			status=INC_PRESS;
		}


		//ấn nút DEC, tương tự ấn nút RESET
		else if(flagForButtonPress[DEC_IDX]==1) {
			flagForButtonPress[DEC_IDX]=0;
			status=DEC_PRESS;
		}

		//ấn đè nút INC
		else if (flagForButtonPress3s[INC_IDX]==1) {
			//set timer để tự động đếm lên
			setTimer2(100);

			//tăng counter
			counter++;

			//reset counter nếu lớn hơn hoặc bằng 10
			if (counter>=10) counter=0;

			//chuyển trạng thái
			status=INC_LONG_PRESS;
		}

		//ấn đè nút DEC, tương tự INC
		else if (flagForButtonPress3s[DEC_IDX]==1) {
			setTimer2(100);
			counter--;
			if (counter<0) counter=9;
			status=DEC_LONG_PRESS;
		}

		break;

	case RESET_PRESS:
		//set counter về 0
		counter=0;

		//đặt timer cho chế độ tự động đếm lùi
		setTimer3(1000);

		//chuyển trạng thái
		status=NO_BUTTON_PRESS;
		break;

	case INC_PRESS:
		//tăng counter
		counter++;

		//reset counter nếu lớn hơn 9
		if (counter>=10) counter=0;

		//đặt timer cho chế độ tự động đếm lùi
		setTimer3(1000);

		//chuyển trạng thái
		status=NO_BUTTON_PRESS;
		break;

	case DEC_PRESS:
		//tương tự INC_PRESS
		counter--;
		if (counter<0) counter=9;
		setTimer3(1000);
		status=NO_BUTTON_PRESS;
		break;

	case INC_LONG_PRESS:
		//hiển thị led
		display7SEG(counter);

		//nếu nhả nút ra, trở về trạng thái NO_BUTTON_PRESS
		if (flagForButtonPress3s[INC_IDX]==0) {
			//đặt timer cho chế độ tự động đếm lùi
			setTimer3(1000);

			//clear timer2
			setTimer2(0);

			//chuyển trạng thái
			status=NO_BUTTON_PRESS;

		}

		//nếu hết 1s thì tăng counter lên
		if (timer2_flag==1) {
			//đặt lại timer
			setTimer2(100);

			//tăng giá trị counter và reset nếu hơn 9
			counter++;
			if (counter>=10) counter=0;
		}
		break;

	//tương tự INC_LONG_PRESS
	case DEC_LONG_PRESS:
		display7SEG(counter);
		if (flagForButtonPress3s[DEC_IDX]==0) {
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

	//chế độ tự động đếm lùi
	case AUTO_DECREASING:
		// hiển thị led
		display7SEG(counter);
		//nếu hết 1s sẽ giảm counter
		if (timer4_flag==1) {
			//đặt timer 1s
			setTimer4(100);
			//giảm counter
			counter--;
			//nếu counter<=0 sẽ về lại trạng thái NO_BUTTON_PRESS
			if (counter<=0) {
				counter=0;
				//clear timer
				setTimer4(0);
				//chuyển trạng thái
				status=NO_BUTTON_PRESS;
			}
		}
		//nếu bấm nút INC sẽ qua trạng thái INC
		if(flagForButtonPress[INC_IDX]==1) {
			flagForButtonPress[INC_IDX]=0;
			status=INC_PRESS;
		}
		//nếu bấm nút DEC sẽ qua trạng thái DEC
		else if(flagForButtonPress[DEC_IDX]==1) {
			flagForButtonPress[DEC_IDX]=0;
			status=DEC_PRESS;
		}
		break;
	default:
		break;
	}
}
