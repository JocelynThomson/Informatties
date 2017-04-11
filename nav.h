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
};

Node nodes[NUM_NODES];
Node* path[NUM_NODES];

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

enum CARDINAL_DIRECTION {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

int edges[NUM_NODES][NUM_EDGES] = { // { N, E, S, W }
	{ 5, NO_NODE, NO_NODE, NO_NODE }, 	//N0
	{ 6, 2, 0, NO_NODE }, 		//N1
	{ 7, 3, NO_NODE, 1 }, 		//N2
	{ 8, 4, NO_NODE, 2 }, 		//N3
	{ 9, NO_NODE, NO_NODE, 3 }, 	//N4
	{ 10, 6, 0, NO_NODE }, 		//N5
	{ 11, NO_NODE, 1, 5 }, 		//N6
	{ 12, 8, 2, 6 }, 		//N7
	{ 13, 9, 3, 7 },		//N8
	{ 14, NO_NODE, 4, 8 },		//N9
	{ NO_NODE, 11, 5, NO_NODE },		//N10
	{ NO_NODE, 12, 6, 10 },		//N11
	{ 17, 13, 7, 11 },		//N12
	{ 18, 14, 8, 12 },		//N13
	{ 19, NO_NODE, 9, 13 },		//N14
	{ 20, 16, 10, NO_NODE },	//N15
	{ 21, 17, 11, 15 },		//N16
	{ NO_NODE, 18, 12, 16 },		//N17
	{ 23, 19, 13, 17 },		//N18
	{ 24, NO_NODE, 14, 18 },	//N19
	{ NO_NODE, 21, 15, NO_NODE },	//N20
	{ NO_NODE, 22, 16, 20 },	//N21
	{ NO_NODE, 23, 17, 21 },	//N22
	{ NO_NODE, 24, 18, 22 },	//N23
	{ NO_NODE, NO_NODE, 19, 23 }	//N24
};

/*
	{ 5, 1, NO_NODE, NO_NODE }, 	//N0
	{ 6, 2, 0, NO_NODE }, 		//N1
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
*/

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
	enqueue(pq, (int) (data - nodes));
}

Node* dequeue_node(Queue* pq) {
	return (Node*) dequeue(pq);
}

DIRECTION translate_world_to_local(int curr, int next) {
	return (DIRECTION) ((next - curr + 4) % 4);
}

void enqueue_path(int depth) {
	int curr_car_dir = NORTH;

	writeDebugStreamLine("Enqueing path depth: %d", depth);


	for (int i = 0; i < depth; i++) {
		Node* n = path[i];
		writeDebugStreamLine("%d: %d", i, n->index);
	}

	for (int i = 0; i < depth - 1; i++) {
		Node* curr_node = path[i];
		Node* next_node = path[i + 1];

		for (int j = 0; j < 4; j++) {
			//writeDebugStreamLine("Left: %d Right: %d", edges[curr_node->index][j], next_node->index);
			if (edges[curr_node->index][j] == next_node->index) {
				DIRECTION turn_dir = translate_world_to_local(curr_car_dir, j);
				print_direction(turn_dir);
				enqueue_direction(turn_dir);
				curr_car_dir = j;
			}
		}
	}
}

void clear_nodes(Node* nodes) {
	for (int i = 0; i < NUM_NODES; i++) {
		nodes[i].distance = INFINITY;
		nodes[i].parent = NULL;
		nodes[i].index = i;
	}
}

void clear_path() {
	for (int i = 0; i < NUM_NODES; i++) {
		path[i] = NULL;
	}
}

//int main(void){
//    int card_dir = compass(prev_node, current_node);
//    printf("card_dir: %d \n", card_dir);
//    int richting = action(current_node, next_node);
//    printf("richting: %d\n", richting);
//}

//Grid is 5x5 met linksonder = 0, rechtsonder = 4, linksboven = 20, rechtsboven = 24
//CARDINAL_DIRECTION cardinal_dir = NORTH;
//Node* current_node = &NODES[0];

//if (next_node > current_node) {
//	if (next_node == current_node + 1) {
//		return EAST;
//	} else {
//		return NORTH;
//	}
//} else {
//	if (next_node == current_node - 1) {
//		return WEST;
//	} else {
//		return SOUTH;
//	}
//}

Queue bfs_queue; // inits queue on stack

int breadth_first_search(Node* start_node, Node* stop_node) {
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

				if (connected_node->distance == INFINITY) {
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

	depth++;

	for (int i = 0; i < depth; i++) {
		Node* n = path[i];
		writeDebugStreamLine("%d: %d", i, n->index);
	}

	enqueue_path(depth);

	return 1;
}

// int main(void) {
	// breadth_first_search(&nodes[4], &nodes[7], NUM_NODES, NUM_EDGES, edges);
	// breadth_first_search(&nodes[2], &nodes[4], NUM_NODES, NUM_EDGES, edges);
// }
