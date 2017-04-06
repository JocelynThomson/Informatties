#include "nav.h"

#define POWER 75

const int white_value = 64;
const int junction_derivative = 1;

int last_error_l = 0;
int last_error_r = 0;

int get_power() {
	if (peek_direction() == FORWARD) {
		return 1.0 * POWER;
	}

	return 0.6 * POWER;
}

int get_sonar() {
	return SensorValue(SONAR);
}

int get_light_left() {
	return SensorValue(LIGHT_L);
}

int get_light_right() {
	return SensorValue(LIGHT_R);
}

int get_power_left(float stop_speed_multiplier = 1.0) {
	int light_val = get_light_left();
	int error = (light_val - white_value);
	int derivative = error - last_error_l;

	if (-derivative > junction_derivative) {
		status = SLOWING_DOWN_JUNCTION;
	}

	int net_power = get_power() * stop_speed_multiplier + ((error + derivative) * 300 / white_value);

	last_error_l = error;

	return net_power;
}

int get_power_right(float stop_speed_multiplier = 1.0) {
	int light_val = get_light_right();
	int error = (light_val - white_value);
	int derivative = error - last_error_r;

	if (-derivative > junction_derivative) {
		status = SLOWING_DOWN_JUNCTION;
	}

	int net_power = get_power() * stop_speed_multiplier + ((error + derivative) * 300 / white_value);

	last_error_r = error;

	return net_power;
}

void undo_derivative() {
	int light_val;
	int error;

	light_val = get_light_left();
	error = (light_val - white_value);
	last_error_l = error;

	light_val = get_light_right();
	error = (light_val - white_value);
	last_error_r = error;
}
