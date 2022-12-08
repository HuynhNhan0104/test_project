/*
 * fsm_traffic.c
 *
 *  Created on: Dec 6, 2022
 *      Author: NHAN
 */


#include "fsm_traffic.h"



void fsm_traffic_1_run(){
	switch(state_led_traffic_1){
		case RED:
			//TODO
			turn_on_traffic_led_1(state_led_traffic_1);
			//STATE STRANSION
			// time out, RED-->GREEN
			if(is_timer_timeout(4)){
				state_led_traffic_1 =GREEN;
				set_timer(4,duration_time_of_GREEN);
			}
		break;

		case YELLOW:
			//TODO
			turn_on_traffic_led_1(state_led_traffic_1);
			//STATE STRANSION
			// time out, YELLOW --> RED
			if(is_timer_timeout(4)){
				state_led_traffic_1 = RED;
				set_timer(4,duration_time_of_RED);
			}
		break;

		case GREEN:
			//TODO
			turn_on_traffic_led_1(state_led_traffic_1);
			//STATE STRANSION
			// timeout, GREEN-->YELLOW
			if(is_timer_timeout(4)){
				state_led_traffic_1 = YELLOW;
				set_timer(4,duration_time_of_YELLOW);
			}
		break;
		default:
		break;
	}
}


void fsm_traffic_2_run(){
	switch(state_led_traffic_2){
		case RED:
			//TODO
			turn_on_traffic_led_2(state_led_traffic_2);
			//STATE STRANSION
			// time out, RED-->GREEN
			if(is_timer_timeout(5)){
				state_led_traffic_2 = GREEN;
				set_timer(5,duration_time_of_GREEN);
			}
		break;
		case YELLOW:
			//TODO
			turn_on_traffic_led_2(state_led_traffic_2);
			//STATE STRANSION
			// time out, YELLOW --> RED
			if(is_timer_timeout(5)){
				state_led_traffic_2 = RED;
				set_timer(5,duration_time_of_RED);
			}
		break;
		case GREEN:
			//TODO
			turn_on_traffic_led_2(state_led_traffic_2);
			//STATE STRANSION
			// timeout, GREEN-->YELLOW
			if(is_timer_timeout(5)){
				state_led_traffic_2 = YELLOW;
				set_timer(5,duration_time_of_YELLOW);
			}
		break;
		default:
		break;
	}
}


void fsm_system_run(){
	switch(mode){
		case INIT_SYSTEM:
			//TODO
			state_led_traffic_1 = RED;
			state_led_traffic_2 = GREEN;
			set_timer(4, duration_time_of_RED);
			set_timer(5, duration_time_of_GREEN);
			//STATE STRANSITION
			mode = NORMAL_MODE;

			//test
			state_led_traffic_1 = GREEN;
			state_led_traffic_2 = GREEN;
			set_timer(6, 500);
			turn_on_traffic_led_1(state_led_traffic_1);
			turn_on_traffic_led_2(state_led_traffic_2);
			is_on = 0;
		break;
		case NORMAL_MODE:
			//TODO
//			fsm_traffic_1_run();
//			fsm_traffic_2_run();

			blinking_led_traffic(state_led_traffic_1);
			//STATE STRANSITION
			//button 0 is pressed,  NORMAl_MODE -> MODIFY_RED_MODE
			if(is_pressed(1)){
				clear_timer(4);
				clear_timer(5);
				state_led_traffic_1 = RED;
				state_led_traffic_2 = RED;
				set_timer(6, 500);
				turn_on_traffic_led_1(state_led_traffic_1);
				turn_on_traffic_led_2(state_led_traffic_2);
				is_on = 0;
				buffer_duration_time = duration_time_of_RED;
				mode = MODIFY_RED_MODE;
			}
		break;
		case MODIFY_RED_MODE:
			//todo

			blinking_led_traffic(state_led_traffic_1);

			//button 1 is pressed, buffer_duration_time increase 1, if buffer exceed 99, buffer = 0;
			if(is_pressed(2)){
				buffer_duration_time = (buffer_duration_time +1000)% (100*1000);
			}
			//button 2 is pressed,  duration time of system = buffer_duration_time;
			if(is_pressed(3)){
				duration_time_of_RED = buffer_duration_time;
			}
			//STATE STRANSITION
			//button 0 is pressed, MODIFY_RED_MODE -> MODIFY_YELLOW_MODE
			if(is_pressed(1)){
				state_led_traffic_1 = YELLOW;
				state_led_traffic_2 = YELLOW;
				set_timer(6, 500);
				is_on = 0;
				turn_on_traffic_led_1(state_led_traffic_1);
				turn_on_traffic_led_2(state_led_traffic_2);
				buffer_duration_time = duration_time_of_YELLOW;
				mode = MODIFY_YELLOW_MODE;
			}
		break;
		case MODIFY_YELLOW_MODE:

			blinking_led_traffic(state_led_traffic_1);

			//button 1 is pressed, buffer_duration_time increase 1, if buffer exceed 99, buffer = 0;
			if(is_pressed(2)){
				buffer_duration_time = (buffer_duration_time +1000)% (100*1000);
			}
			//button 2 is pressed,  duration time of system = buffer_duration_time;
			if(is_pressed(3)){
				duration_time_of_YELLOW = buffer_duration_time;
			}

			//STATE STRANSITION
			//button 0 is pressed,MODIFY_YELLOW_MODE  ->  MODIFY_GREEN_MODE
			if(is_pressed(1)){
				state_led_traffic_1 = GREEN;
				state_led_traffic_2 = GREEN;
				set_timer(6, 500);
				is_on = 0;
				turn_on_traffic_led_1(state_led_traffic_1);
				turn_on_traffic_led_2(state_led_traffic_2);
				buffer_duration_time = duration_time_of_GREEN;
				mode = MODIFY_GREEN_MODE;
			}
		break;
		case MODIFY_GREEN_MODE:
			blinking_led_traffic(state_led_traffic_1);
			//button 1 is pressed, buffer_duration_time increase 1, if buffer exceed 99, buffer = 0;
			if(is_pressed(2)){
				buffer_duration_time = (buffer_duration_time +1000)% (100*1000);
			}
			//button 2 is pressed,  duration time of system = buffer_duration_time;
			if(is_pressed(3)){
				duration_time_of_GREEN = buffer_duration_time;
			}

			//STATE STRANSITION
			//button 0 is pressed, MODIFY_GREEN_MODE -> NORMAL_MODE
			if(is_pressed(1)){
				clear_timer(6);
				state_led_traffic_1 = RED;
				state_led_traffic_2 = GREEN;
				set_timer(4, duration_time_of_RED);
				set_timer(5, duration_time_of_GREEN);
				mode = NORMAL_MODE;
			}
		break;
		default:
		break;
	}
}



