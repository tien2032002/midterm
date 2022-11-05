/*
 * fsm_simple_button_run.h
 *
 *  Created on: Nov 5, 2022
 *      Author: Administrator
 */

#ifndef INC_FSM_SIMPLE_BUTTON_RUN_H_
#define INC_FSM_SIMPLE_BUTTON_RUN_H_

extern int counter;
extern int status;

#define INIT				0
#define INC_PRESS			1
#define DEC_PRESS			2
#define RESET_PRESS			3

#define INC_LONG_PRESS		11
#define DEC_LONG_PRESS		12
#define NO_BUTTON_PRESS		13

#define AUTO_DECREASING		21

void fsm_simple_button_run();

#endif /* INC_FSM_SIMPLE_BUTTON_RUN_H_ */
