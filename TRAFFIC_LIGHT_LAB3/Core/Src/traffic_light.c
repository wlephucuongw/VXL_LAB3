/*
 * traffic_light.c
 *
 *  Created on: Oct 26, 2024
 *      Author: Administrator
 */
#include "traffic_light.h"
int TIME_FOR_GREEN = 10;
int TIME_FOR_RED = 15;
int TIME_FOR_AMBER = 5;
int time_red;
int time_green;
int time_amber;
int newTime = 0;
void init(){
	HAL_GPIO_TogglePin(GPIOA, SIGNAL_Pin);
	if(TIME_FOR_GREEN < TIME_FOR_RED){
		 time_red = TIME_FOR_RED;
		 time_green = TIME_FOR_GREEN;
		 time_amber = TIME_FOR_RED - TIME_FOR_GREEN - 1;
	}
	else {
	 time_red = 10;
	 time_green = 15;
	 time_amber = 5 - 1;
	}
}
void auto_green_red(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);

	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);

	update_led_buffer_A(time_green);
	update_led_buffer_B(time_red);
	display();
	if(timers[1].flag == 1) // flag for display 7
		{
			time_green--;
			time_red--;
			setTimer(1, 1000);
		}
}
void auto_amber_red(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, SET);

	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);

	update_led_buffer_A(time_amber);
	update_led_buffer_B(time_red);
	display();
	if(timers[1].flag == 1) // flag for display 7
		{
			time_amber--;
			time_red--;
			setTimer(1, 1000);
		}
}
void auto_red_green(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);

	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);

	update_led_buffer_A(time_red);
	update_led_buffer_B(time_green);
	display();
	if(timers[1].flag == 1) // flag for display 7
		{
			time_red--;
			time_green--;
			setTimer(1, 1000);
		}
}
void auto_red_amber(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);

	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, SET);

	update_led_buffer_A(time_red);
	update_led_buffer_B(time_amber);
	display();
	if(timers[1].flag == 1) // flag for display 7
		{
			time_red--;
			time_amber--;
			setTimer(1, 1000);
		}
}

// use timer 3
void modify_red_led(){

	if(timers[3].flag == 1){
		HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);

		HAL_GPIO_TogglePin(LED_RED_A_GPIO_Port, LED_RED_A_Pin);
		HAL_GPIO_TogglePin(LED_RED_B_GPIO_Port, LED_RED_B_Pin);
		setTimer(3, 500);
	}
	update_led_buffer_B(2); // mode name
	update_led_buffer_A(newTime); //new time
	display();
}
void modify_green_led(){
	if(timers[3].flag == 1){
		HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);

		HAL_GPIO_TogglePin(LED_GREEN_A_GPIO_Port, LED_GREEN_A_Pin);
		HAL_GPIO_TogglePin(LED_GREEN_B_GPIO_Port, LED_GREEN_B_Pin);
		setTimer(3, 500);
	}
	update_led_buffer_B(3); // mode name
	update_led_buffer_A(newTime); // new time
	display();
}
void modify_amber_led(){
	if(timers[3].flag == 1){
		HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, RESET);
		HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);

		HAL_GPIO_TogglePin(LED_YELLOW_A_GPIO_Port, LED_YELLOW_A_Pin);
		HAL_GPIO_TogglePin(LED_YELLOW_B_GPIO_Port, LED_YELLOW_B_Pin);
		setTimer(3, 500);
	}
	update_led_buffer_B(4); //  mode name
	update_led_buffer_A(newTime); //new time
	display();
}
void clear_all_led(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);
}
void manual_green_red(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);
	update_led_buffer_B(1); //  mode name
	update_led_buffer_A(0); //00
	display();
}
void manual_red_green(){
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_A_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_RED_B_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_GREEN_B_Pin, SET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_A_Pin, RESET);
	HAL_GPIO_WritePin(GPIOB, LED_YELLOW_B_Pin, RESET);
	update_led_buffer_B(1); //  mode name
	update_led_buffer_A(0); //00
	display();
}
