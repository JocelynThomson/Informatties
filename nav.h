#include "queue.h"

enum DIRECTION {
	NONE = 0,
	FORWARD = 1,
	LEFT = 2,
	RIGHT = 3,
	TURNABOUT = 4
};

void init_nav_queue() {
	init_queue(&nav_queue);
}

void enqueue_direction(DIRECTION dir) {
	enqueue(&nav_queue, dir);
}

DIRECTION dequeue_direction() {
	return (DIRECTION) dequeue(&nav_queue);
}

DIRECTION peek_direction() {
	return (DIRECTION) peek(&nav_queue);
}
