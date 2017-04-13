/**
 * @file steering.h
 * @author Julian van Doorn and Kiet van Osnabrugge
 * @brief Contains functions for steering the NXT
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "sensors.h"

/**
 * @brief Turns left for the given time in ms
 * @param time
 */
void turn_left(int p){
	motor[MOTOR_L] = -p;
	motor[MOTOR_R] = p;

	waitUntil(get_light_left() < white_value - 5);

	motor[MOTOR_L] = -p;
	motor[MOTOR_R] = p;

	waitUntil(get_light_left() > white_value - 5);
	wait1Msec(50);

	motor[MOTOR_L] = -p;
	motor[MOTOR_R] = p;

	nullify_derivative();
	status = FOLLOWING_LINE;
}

/**
 * @brief Turns right for the given time in ms
 * @param time
 */
void turn_right(int p){
	motor[MOTOR_L] = p;
	motor[MOTOR_R] = -p;

	waitUntil(get_light_right() < white_value - 5);

	motor[MOTOR_L] = p;
	motor[MOTOR_R] = -p;

	waitUntil(get_light_right() > white_value - 5);
	wait1Msec(50);

	motor[MOTOR_L] = p;
	motor[MOTOR_R] = -p;

	nullify_derivative();
	status = FOLLOWING_LINE;
}

/**
 * @brief Drives straight for the given time in ms
 * @param time
 */
void go_forward(){
	status = FOLLOWING_LINE;
}

/**
 * @brief Slows down linearly and turns around until the line is found
 * @param power_left
 * @param power_right
 */
void turn_around(int power_left, int power_right) {
	motor[MOTOR_L] = 50;
	motor[MOTOR_R] = -50;
	wait1Msec(1400);
	nullify_derivative();
	waitUntil(get_light_right() < white_value - 5);
	waitUntil(get_light_right() > white_value - 5);
	nullify_derivative();
}
#endif
