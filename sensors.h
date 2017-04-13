/**
 * @file    sensors_pid_enhanced.h
 * @author  Julian van Doorn
 * @brief   This file is responsible for the calibration of the right and left engines. It reads the values of the different sensors and
 *          adjusts the motors accordingly. The calbiration is done by a PD-conrtroller (Proportional Differential).
 */

#ifndef SENSORS_H_
#define SESNORS_H_

#include "nav.h"
int power = 0;	/**< Defines the power value for the speed of the engines. */

int white_value = 64;         /**< The value for the white colour of the board. */
int junction_derivative = 0x7FFFFFFF;  /**< The derivative for junctions. */

int last_error_l = 0;   /**< The last error from the left sensor. */
int last_error_r = 0;   /**< The last error from the right sensor. */

/**
 * @brief   This method returns the power for the engines which depends on the direction of the robot.
 * @return  The power for the engines.
 */
int get_power() {
	return power;
}

/**
 * @brief   Returns the value of the sonar sensor.
 * @return  The value of the sonar sensor.
 */
int get_sonar() {
	return SensorValue(SONAR);
}

/**
 * @brief   Returns the value of the left light sensor.
 * @return  The value of the left light sensor.
 */
int get_light_left() {
	return SensorValue(LIGHT_L);
}

/**
 * @brief   Returns the value of the right light sensor.
 * @return  The value of the right light sensor.
 */
int get_light_right() {
	return SensorValue(LIGHT_R);
}

/**
 * @brief                       This method calculates the appropiate power that needs to go to the left engine.
 * @param stop_speed_multiplier The value by which the engine gets slowed down.
 * @return                      The appropiate power value for the left engine.
 */
int get_power_left(float stop_speed_multiplier = 1.0) {
	int light_val = get_light_left();
	int error = (light_val - white_value);
	int derivative = error - last_error_l;

	if (-derivative > junction_derivative) {
		status = SLOWING_DOWN_JUNCTION;
	}

	int net_power = get_power() * stop_speed_multiplier + ((error + derivative) * (300 / white_value));

	last_error_l = error;

	return net_power;
}

/**
 * @brief                       This method calculates the appropiate power that needs to go to the right engine.
 * @param stop_speed_multiplier The value by which the engine gets slowed down.
 * @return                      The appropiate power value for the right engine.
 */
int get_power_right(float stop_speed_multiplier = 1.0) {
	int light_val = get_light_right();
	int error = (light_val - white_value);
	int derivative = error - last_error_r;

	if (-derivative > junction_derivative) {
		status = SLOWING_DOWN_JUNCTION;
	}

	int net_power = get_power() * stop_speed_multiplier + ((error + derivative) * (300 / white_value));

	last_error_r = error;

	return net_power;
}

/**
 * @brief This sets the last error to the current error so the derivative becomes 0.
 */
void nullify_derivative() {
	int light_val;
	int error;

	light_val = get_light_left();
	error = (light_val - white_value);
	last_error_l = error;

	light_val = get_light_right();
	error = (light_val - white_value);
	last_error_r = error;
}
#endif
