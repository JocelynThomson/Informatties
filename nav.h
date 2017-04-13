/**
 * @file nav.h
 * @author Julian van Doorn
 * @brief This file defines the navigation queue
 */

#ifndef NAV_H_
#define NAV_H_

#include "queue.h"

#define NO_NODE -1
#define NUM_NODES 25
#define NUM_EDGES 4
#define INFINITY 0x7FFFFFFF

/**
 * @brief A node represent a single juntion on the map/route
 */
struct Node {
	int distance;			/**< The distance relative from the root node */
	struct Node* parent;	/**< The previous or parent node */
	int index;				/**< The index of the node */
	bool enabled;			/**< Boolean to indicate if there is a obstacle on the node */
};

/**
 * @brief Enumerates the values that are used inside the nav_queue
 */
enum DIRECTION {
	NONE = -1,			/**< No operation */
	FORWARD = 0,		/**< Steer forward at junction */
	RIGHT = 1,			/**< Steer right at junction */
	TURNABOUT = 2,		/**< Turn around at junction */
	LEFT = 3			/**< Steer left at junction */
};

/**
 * @brief Enumeration for the cardinal directions for the robot. This is used to determine
 *        what left, right, up and down for the robot is.
 */
enum CARDINAL_DIRECTION {
	NORTH = 0,	/**< North or up */
	EAST = 1,	/**< East or right */
	SOUTH = 2,	/**< South or down */
	WEST = 3	/**< West or left */
};

/**
 * @brief This 2d-integer array holds all the edges or connections between each individual node. Each node
 *        can have a maximum of four edges. For example, the first node N0 in the array is connected with
 *        the nodes N5 and N1.
 */
int edges[NUM_NODES][NUM_EDGES] = { // { N, E, S, W }
	{ 5, 1, NO_NODE, NO_NODE }, 	//N0
	{ 6, 2, NO_NODE, 0 }, 		//N1
	{ 7, 3, NO_NODE, 1 }, 		//N2
	{ 8, 4, NO_NODE, 2 }, 		//N3
	{ 9, NO_NODE, NO_NODE, 3 }, 	//N4
	{ 10, 6, 0, NO_NODE }, 		//N5
	{ 11, 7, 1, 5 }, 		//N6
	{ 12, 8, 2, 6 }, 		//N7
	{ 13, 9, 3, 7 },		//N8
	{ 14, NO_NODE, 4, 8 },		//N9
	{ 15, 11, 5, NO_NODE },		//N10
	{ 16, 12, 6, 10 },		//N11
	{ 17, 13, 7, 11 },		//N12
	{ 18, 14, 8, 12 },		//N13
	{ 19, NO_NODE, 9, 13 },		//N14
	{ 20, 16, 10, NO_NODE },	//N15
	{ 21, 17, 11, 15 },		//N16
	{ 22, 18, 12, 16 },		//N17
	{ 23, 19, 13, 17 },		//N18
	{ 24, NO_NODE, 14, 18 },	//N19
	{ NO_NODE, 21, 15, NO_NODE },	//N20
	{ NO_NODE, 22, 16, 20 },	//N21
	{ NO_NODE, 23, 17, 21 },	//N22
	{ NO_NODE, 24, 18, 22 },	//N23
	{ NO_NODE, NO_NODE, 19, 23 }	//N24
};

Node nodes[NUM_NODES];
Node* path[NUM_NODES];

Node* last_node = NULL;
Node* next_node = NULL;

Node* going_to_node = NULL;

CARDINAL_DIRECTION cur_car_dir = NORTH;

/**
 * @brief		This method is used to keep track of the position and orientation of the robot
 * @param dir 	The direction of the robot.
 */
void push_back_action(DIRECTION dir) {
	if (last_node == NULL) {
		next_node = &nodes[0];
	}

	cur_car_dir = (CARDINAL_DIRECTION) ((cur_car_dir + dir + 4) % 4);

	last_node = next_node;
	next_node = &nodes[edges[last_node->index][cur_car_dir]];
}

/**
 * @brief Initializes the nav_queue
 */
void init_nav_queue() {
	init_queue(&nav_queue);
}

/**
 * @brief Enqueues the provided arguments into the nav_queue
 * @param dir The desired direction to be executed by the robot
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
 * @brief 		Enqueues the next node in the path in the queue datastructure
 * @param pq 	Pointer to the queue datastructure
 * @param data 	The node that needs to be enqueued in the queue
 */
void enqueue_node(Queue* pq, Node* data) {
	enqueue(pq, (int) (data->index));
}

/**
 * @brief		This method returns the first node in the queue.
 * @param pq	Pointer to the queue datastructure
 * @return 		The (address of) first node in the queue
 */
Node* dequeue_node(Queue* pq) {
	Node* data = (Node*) dequeue(pq);
	return &nodes[data];
}

/**
 * @brief 		This method determines the turn direction based on the cardinal direction of the robot
 * @param curr  The current direction of the robot
 * @param next  The next direction the robot must go to
 * @return 		The next turn direction for the robot
 */
DIRECTION translate_world_to_local(int curr, int next) {
	return (DIRECTION) ((next - curr + 4) % 4);
}

/**
 * @brief		Translates all global cardinal directions to local turn directions.
 * @param depth The depth of the tree (the length of the path)
 */
void enqueue_path(int depth) {
	CARDINAL_DIRECTION loc_cur_car_dir = cur_car_dir;

	for (int i = 0; i < depth - 1; i++) {
		Node* curr_node = path[i];
		Node* next_node = path[i + 1];

		for (int j = 0; j < 4; j++) {
			if (edges[curr_node->index][j] == next_node->index) {
				DIRECTION turn_dir = translate_world_to_local(loc_cur_car_dir, j);
				enqueue_direction(turn_dir);
				loc_cur_car_dir = (CARDINAL_DIRECTION) j;
			}
		}
	}
}

/**
 * @brief 		Resets all the nodes to their default state
 * @param nodes The nodes array
 */
void clear_nodes(Node* nodes) {
	for (int i = 0; i < NUM_NODES; i++) {
		nodes[i].distance = INFINITY;
		nodes[i].parent = NULL;
		nodes[i].index = i;
		nodes[i].enabled = true;
	}
}

Queue bfs_queue; // inits queue on stack

/**
 * @brief				Calculates and immediatly enqueues the path
 * @param start_node	The start node/point of the robot
 * @param stop_node		The end node/destination of the robot
 * @return 				Returns 1 on succes -1 otherwise
 */
int breadth_first_search(Node* start_node, Node* stop_node) {
	going_to_node = stop_node;

	start_node->parent = NULL;
	start_node->distance = 0;

	for (int i = 0; i < NUM_NODES; i++) {
		if (&nodes[i] != start_node) {
			nodes[i].distance = INFINITY;
		}
	}

	init_queue(&bfs_queue);
	enqueue_node(&bfs_queue, start_node);

	Node* parent;

	while (bfs_queue.item_count > 0) {
		Node* node = dequeue_node(&bfs_queue);

		for (int  j = 0; j < NUM_EDGES; j++) {
			int connected_node_index = edges[node->index][j];

			if (connected_node_index != -1) {
				Node* connected_node = &nodes[connected_node_index];

				if (connected_node == stop_node) {
					stop_node->parent = node;
					goto found_route;
				}

				if (connected_node->distance == INFINITY && connected_node->enabled) {
					connected_node->distance = node->distance + 1;
					connected_node->parent = node;
					enqueue_node(&bfs_queue, connected_node);
				}
			}
		}
	}

	// No valid route found
	return -1;

found_route:
	parent = stop_node;

	int depth = 0;

	do {
		parent = parent->parent;
		depth++;
	} while (parent != start_node);

	parent = stop_node;

	for (int i = depth; i >= 0; i--) {
		path[i] = parent;
		parent = parent->parent;
	}

	enqueue_path(++depth);

	return 1;
}
#endif
