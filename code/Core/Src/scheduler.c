/*
 * scheduler.c
 *
 *  Created on: Dec 6, 2022
 *      Author: NHAN
 */


#include "scheduler.h"

Scheduler_Task Scheduler_Task_Array[MAX_TASK];
uint32_t current_index = 0;
uint8_t ERROR_CODE_G = NORMAL;



void Scheduler_Init(){
	 current_index = 0;
}
uint32_t Scheduler_Add_Task(void (*pfunction)(),uint32_t delay, uint32_t period){
	if(current_index < MAX_TASK){
		Scheduler_Task_Array[current_index].pfunction = pfunction;
		Scheduler_Task_Array[current_index].Delay = delay;
		Scheduler_Task_Array[current_index].Period = period;
		Scheduler_Task_Array[current_index].Runme = 0;
		Scheduler_Task_Array[current_index].Task_ID = current_index;
		current_index++;
		return current_index;
	}
	else{
		ERROR_CODE_G = ERROR_SCHEDULER_TOO_MANY_TASK;
		return 0;
	}

}
void Scheduler_Update(){
	for(int index = 0 ; index  < current_index ; ++index){
		if(Scheduler_Task_Array[index].Delay > 0){
			Scheduler_Task_Array[index].Delay -= TICK;
		}
		else{
			Scheduler_Task_Array[index].Runme += 1;
			if(Scheduler_Task_Array[index].Period >0){
				Scheduler_Task_Array[index].Delay = Scheduler_Task_Array[index].Period;
			}
		}
	}
}
void Scheduler_Dispatch_Task(){
	for(int index = 0 ; index  < current_index; ++index){
		if(Scheduler_Task_Array[index].Runme >0){
			(*Scheduler_Task_Array[index].pfunction)();
			Scheduler_Task_Array[index].Runme -= 1;
			if(Scheduler_Task_Array[index].Period == 0){
				Scheduler_Delete_Task(Scheduler_Task_Array[index].Task_ID);
			}
		}
	}

}
uint32_t Scheduler_Delete_Task(uint32_t task_ID){
	if(task_ID >= current_index || current_index == 0){
		ERROR_CODE_G = ERROR_NO_TASK_TO_DELETE ;
		return 0;
	}
	else{
		for(int index = 0 ; index < current_index - 1; ++index){
			Scheduler_Task_Array[index].pfunction = Scheduler_Task_Array[index + 1].pfunction;
			Scheduler_Task_Array[index].Delay = Scheduler_Task_Array[index + 1].Delay;
			Scheduler_Task_Array[index].Period = Scheduler_Task_Array[index + 1].Period;
			Scheduler_Task_Array[index].Runme = Scheduler_Task_Array[index + 1].Runme;
			Scheduler_Task_Array[index].Task_ID = Scheduler_Task_Array[index + 1].Task_ID;
		}
		Scheduler_Task_Array[current_index].pfunction =0x0000;
		Scheduler_Task_Array[current_index].Delay = 0;
		Scheduler_Task_Array[current_index].Period = 0;
		Scheduler_Task_Array[current_index].Runme = 0;
		Scheduler_Task_Array[current_index].Task_ID = 0;
		current_index--;
		return current_index;
	}
}
