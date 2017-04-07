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

int edges[NUM_NODES][NUM_EDGES] = { // { N, E, S, W }
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
};

Node nodes[NUM_NODES];

/**
 * @brief Enumerates the values that are used inside the nav_queue
 */
enum DIRECTION {
	NONE = 0,			/**< No operation*/
	FORWARD = 1,	/**< Steer forward at junction*/
	LEFT = 2,			/**< Steer left at junction*/
	RIGHT = 3,		/**< Steer right at junction*/
	TURNABOUT = 4	/**< Turn around at junction*/
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

void enqueue_node(Queue* pq, Node* data) {
	enqueue(pq, (int) (data - nodes));
}

Node* dequeue_node(Queue* pq) {
	return &nodes[dequeue(pq)];
}

void clear_nodes(Node* nodes) {
	for (int i = 0; i < NUM_NODES; i++) {
		nodes[i].distance = INFINITY;
		nodes[i].parent = NULL;
		nodes[i].index = i;
	}
}

int breadth_first_search(Node* start_node, Node* stop_node) {
	clear_nodes(nodes);
	start_node->parent = NULL;
	start_node->distance = 0;

	for (int i = 0; i < NUM_NODES; i++) {
		if (&nodes[i] != start_node) {
			nodes[i].distance = INFINITY;
		}
	}

	Queue q; // inits queue on stack
	Queue* pq = &q; // references queue
	init_queue(pq);

	enqueue_node(pq, start_node);

	Node* parent;

	while (pq->item_count > 0) {
		Node* node = dequeue_node(pq);

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
					enqueue_node(pq, connected_node);
				}
			}
		}
	}

	// No valid route found
	return -1;

found_route:
	parent = stop_node;

	do {
		//printf("%d<-", parent->index);
		parent = parent->parent;
	} while (parent != start_node);

	//printf("%d\n", parent->index);

	return 1;
}

// int main(void) {
	// breadth_first_search(&nodes[4], &nodes[7], NUM_NODES, NUM_EDGES, edges);
	// breadth_first_search(&nodes[2], &nodes[4], NUM_NODES, NUM_EDGES, edges);
// }
