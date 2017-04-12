/**
 * @file nav.h
 * @author Julian van Doorn
 * @brief This file defines the navigation queue
 */

#include "queue.h"

#define NO_NODE -1
#define NUM_NODES 25
#define NUM_EDGES 4
#define INFINITY 0x7FFFFFFF

struct Node {
	int distance;
	struct Node* parent;
	int index;
	bool enabled;
};

/**
 * @brief Enumerates the values that are used inside the nav_queue
 */
enum DIRECTION {
	NONE = -1,			/**< No operation*/
	FORWARD = 0,	/**< Steer forward at junction*/
	RIGHT = 1,		/**< Steer right at junction*/
	TURNABOUT = 2,	/**< Turn around at junction*/
	LEFT = 3			/**< Steer left at junction*/
};

enum CARDINAL_DIRECTION {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

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

void push_back_action(DIRECTION dir) {
	if (last_node == NULL) {
		next_node = &nodes[0];
	}

	cur_car_dir = (CARDINAL_DIRECTION) ((cur_car_dir + dir + 4) % 4);

	last_node = next_node;
	next_node = &nodes[edges[last_node->index][cur_car_dir]];

	writeDebugStreamLine("MOVING FROM NODE: %d TOWARDS NODE: %d", last_node->index, next_node->index);
	writeDebugStreamLine("CARDINAL_DIRECTION: %d", cur_car_dir);

}

void print_direction(DIRECTION dir) {
	switch (dir) {
		case NONE:
			writeDebugStreamLine("NONE");
		break;
		case FORWARD:
			writeDebugStreamLine("FORWARD");
		break;
		case RIGHT:
			writeDebugStreamLine("RIGHT");
		break;
		case TURNABOUT:
			writeDebugStreamLine("TURNABOUT");
		break;
		case LEFT:
			writeDebugStreamLine("LEFT");
		break;
	}
}

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

void enqueue_node(Queue* pq, Node* data) {
	//writeDebugStreamLine("ENQUEUEING %d", (int) (data->index));
	enqueue(pq, (int) (data->index));
}

Node* dequeue_node(Queue* pq) {
	Node* data = (Node*) dequeue(pq);
	//writeDebugStreamLine("DEQUEUEING %d", data);
	return &nodes[data];
}

DIRECTION translate_world_to_local(int curr, int next) {
	return (DIRECTION) ((next - curr + 4) % 4);
}

void enqueue_path(int depth) {
	//writeDebugStreamLine("Enqueing path depth: %d", depth);
	CARDINAL_DIRECTION loc_cur_car_dir = cur_car_dir;


//	for (int i = 0; i < depth; i++) {
//		Node* n = path[i];
		//writeDebugStreamLine("%d: %d", i, n->index);
//	}

	for (int i = 0; i < depth - 1; i++) {
		Node* curr_node = path[i];
		Node* next_node = path[i + 1];

		for (int j = 0; j < 4; j++) {
			if (edges[curr_node->index][j] == next_node->index) {
				DIRECTION turn_dir = translate_world_to_local(loc_cur_car_dir, j);
				print_direction(turn_dir);
				enqueue_direction(turn_dir);
				loc_cur_car_dir = j;
			}
		}
	}
}

void clear_nodes(Node* nodes) {
	for (int i = 0; i < NUM_NODES; i++) {
		nodes[i].distance = INFINITY;
		nodes[i].parent = NULL;
		nodes[i].index = i;
		nodes[i].enabled = true;
	}
}

Queue bfs_queue; // inits queue on stack

int breadth_first_search(Node* start_node, Node* stop_node) {
	going_to_node = stop_node;
	writeDebugStreamLine("CALCULATING PATH FROM: %d TO: %d", start_node->index, stop_node->index);

	clear_nodes(nodes);
	start_node->parent = NULL;
	start_node->distance = 0;

	for (int i = 0; i < NUM_NODES; i++) {
		if (&nodes[i] != start_node) {
			nodes[i].distance = INFINITY;
		}
	}

	init_queue(&bfs_queue);
	enqueue_node(&bfs_queue, start_node);
	//writeDebugStreamLine("%p", dequeue_node(&bfs_queue));
	Node* parent;

	while (bfs_queue.item_count > 0) {
		Node* node = dequeue_node(&bfs_queue);
		//writeDebugStreamLine("%p", node);

		if (node->enabled) {
			for (int  j = 0; j < NUM_EDGES; j++) {
				int connected_node_index = edges[node->index][j];

				if (connected_node_index != -1) {
					Node* connected_node = &nodes[connected_node_index];

					if (connected_node == stop_node) {
						stop_node->parent = node;
						goto found_route;
					}

					if (connected_node->distance == INFINITY) {
						connected_node->distance = node->distance + 1;
						connected_node->parent = node;
						enqueue_node(&bfs_queue, connected_node);
					}
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

	depth++;

	for (int i = 0; i < depth; i++) {
		Node* n = path[i];
		writeDebugStreamLine("%d: %d", i, n->index);
	}

	enqueue_path(depth);

	return 1;
}
