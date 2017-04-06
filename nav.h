/**
 * @file nav.h
 * @author Julian van Doorn
 * @brief This file defines the navigation queue
 */

#include "queue.h"

/**
 * @brief Enumerates the values that are used inside the nav_queue
 */
enum DIRECTION {
	NONE = 0, /**< No operation*/
	FORWARD = 1, /**< Steer forward at junction*/
	LEFT = 2, /**< Steer left at junction*/
	RIGHT = 3, /**< Steer right at junction*/
	TURNABOUT = 4 /**< Turn around at junction*/
};

/**
 * @brief Initializes the nav_queue
 */
void init_nav_queue() {
	init_queue(&nav_queue);
}

/**
 * @brief Enqueues the provided arguments into the nav_queue
 * @param dir
 */
void enqueue_direction(DIRECTION dir) {
	enqueue(&nav_queue, dir);
}

/**
 * @brief Dequeues and returns a direction from the nav_queue
 */
DIRECTION dequeue_direction() {
	return (DIRECTION) dequeue(&nav_queue);
}

/**
 * @brief Returns but does not remove the next element from the queue
 */
DIRECTION peek_direction() {
	return (DIRECTION) peek(&nav_queue);
}
