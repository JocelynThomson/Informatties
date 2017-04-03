#include "queue.h"

enum DIRECTION {
	FORWARD = 0,
	LEFT = 1,
	RIGHT = 2,
	TURNABOUT = 3
};

Queue* nav_queue;

void init_nav_queue() {
	init_queue(nav_queue);
}

void enqueue_direction(DIRECTION dir) {
	enqueue(nav_queue, dir);
}

DIRECTION dequeue_direction() {
	return (DIRECTION) dequeue(nav_queue);
}

void resolveJunction() {
	dequeue(nav_queue);
}
