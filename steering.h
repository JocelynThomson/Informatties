#include "sensors.h"


void turn_left(int time){
	motor[MOTOR_L] = -POWER;
	motor[MOTOR_R] = POWER;
	wait1Msec(time);
}

void turn_right(int time){
	motor[MOTOR_L] = POWER;
	motor[MOTOR_R] = -POWER;
	wait1Msec(time);
}

void go_straight(int time){
	motor[MOTOR_L] = POWER;
	motor[MOTOR_R] = POWER;
	wait1Msec(time);
}

void steer_left(int ms) {
	clearTimer(T1);
	while (time1[T1] < ms) {
		motor[MOTOR_L] = get_power_left();
		motor[MOTOR_R] = POWER;
	}
}

void steer_right(int ms) {
	clearTimer(T1);
	while (time1[T1] < ms) {
		motor[MOTOR_L] = POWER;
		motor[MOTOR_R] = get_power_right();
	}
}

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

int scan(int distance) {
	bool object = true;
	int sonar_value = get_sonar();

	turn_right(600);
	go_straight(700);
	turn_left(600);
	sonar_value = get_sonar();
	if (sonar_value > distance){
		object = false;
	}
	return object;
}
