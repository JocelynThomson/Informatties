#define WHITE_VALUE 64
#define POWER 75

int get_sonar() {
	return SensorValue(SONAR);
}

int get_light_left() {
	return SensorValue(LIGHT_L);
}

int get_light_right() {
	return SensorValue(LIGHT_R);
}

int get_power_left() {
	int light_val_l = get_light_left();
	int error_l = light_val_l - WHITE_VALUE;
	int power_left = POWER + (error_l * 200 / WHITE_VALUE);

	return power_left;
}

int get_power_right() {
	int light_val_r = get_light_right();
	int error_r = light_val_r - WHITE_VALUE;
	int power_right = POWER + (error_r * 200 / WHITE_VALUE);

	return power_right;
}
