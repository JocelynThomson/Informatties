/**
 * @file steering.h
 * @author Julian van Doorn and Kiet van Osnabrugge
 * @brief Contains functions for steering the NXT
 */

#include "sensors_pid_enhanced.h"

/**
 * @brief Turns left for the given time in ms
 * @param time
 */
void turn_left(int time){
	int p = get_power();
	motor[MOTOR_L] = -p;
	motor[MOTOR_R] = p;
	wait1Msec(time);
}

/**
 * @brief Turns right for the given time in ms
 * @param time
 */
void turn_right(int time){
	int p = get_power();
	motor[MOTOR_L] = p;
	motor[MOTOR_R] = -p;
	wait1Msec(time);
}

/**
 * @brief Drives straight for the given time in ms
 * @param time
 */
void go_straight(int time){
	int p = get_power();
	motor[MOTOR_L] = p;
	motor[MOTOR_R] = p;
	wait1Msec(time);
}

/**
 * @brief Steers left at a junction for a given time
 * @param time
 */
void steer_left(int time) {
	int p = get_power();
	clearTimer(T1);
	while (time1[T1] < time) {
		motor[MOTOR_L] = get_power_left();
		motor[MOTOR_R] = p;
	}
}

/**
 * @brief Steers right at a junction for a given time
 * @param time
 */
void steer_right(int time) {
	int p = get_power();
	clearTimer(T1);
	while (time1[T1] < time) {
		motor[MOTOR_L] = p;
		motor[MOTOR_R] = get_power_right();
	}
}

/**
 * @brief Slows down linearly and turns around until the line is found
 * @param power_left
 * @param power_right
 */
void turn_around(int power_left, int power_right) {
	for (int i = (power_left + power_right) / 2; i > 0; i--) {
		motor[MOTOR_L] = i;
		motor[MOTOR_R] = i;
		wait1Msec(10);
	}

	for (int i = 0; i < 50; i++) {
		motor[MOTOR_L] = 20;
		motor[MOTOR_R] = -30;

		if (get_light_left() < 50 && i > 20) {
			motor[MOTOR_L] = 0;
			motor[MOTOR_R] = 0;
			break;
		}

		wait1Msec(100);
	}
}
