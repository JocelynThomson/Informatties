/**
 * @file nav.h
 * @author Julian van Doorn
 * @brief This file defines the navigation queue
 */

#include <limits.h>

#define NO_NODE -1
#define NUM_NODES 8
#define NUM_EDGES 4
#define INFINITY INT_MAX

#include "queue.h"

typedef struct Node {
	int distance;
	struct Node* predecessor;
	int index;
} Node;


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

int edges[NUM_NODES][NUM_EDGES] = {
	{ 1, 4, NO_NODE, NO_NODE },
	{ 0, 5, NO_NODE, NO_NODE },
	{ 3, 5, 6, NO_NODE },
	{ 2, 6, 7, NO_NODE },
	{ 0, NO_NODE, NO_NODE, NO_NODE },
	{ 1, 2, 6, NO_NODE },
	{ 2, 3, 5, 7 },
	{ 3, 6, NO_NODE, NO_NODE }
};

Node nodes[NUM_NODES];

void clear_nodes(Node nodes[NUM_NODES]) {
	for (int i = 0; i < NUM_NODES; i++) {
		nodes[i].distance = INFINITY;
		nodes[i].predecessor = NULL;
		nodes[i].index = i;
	}
}

void breadth_first_search(Node* start_node, Node* stop_node, int num_nodes, int num_edges, int edges[num_nodes][num_edges]) {
	clear_nodes(nodes);
	start_node->predecessor = NULL;
	start_node->distance = 0;
	
	for (int i = 0; i < num_nodes; i++) {
		if (&nodes[i] != start_node) {
			nodes[i].distance = INFINITY;
		}
	}
	
	Queue q; // inits queue on stack
	Queue* pq = &q; // references queue
	init_queue(pq);
	
	enqueue(pq, start_node);
	
	Node* predecessor;
	
	while (pq->item_count > 0) {
		Node* node = (Node*) dequeue(pq);
		
		for (int  j = 0; j < num_edges; j++) {
			int connected_node_index = edges[node->index][j];
			
			
			if (connected_node_index != -1) {
				Node* connected_node = &nodes[connected_node_index];
				
				if (connected_node == stop_node) {
					stop_node->predecessor = node;
					goto found_route;
				}
				
				if (connected_node->distance == INFINITY) {
					connected_node->distance = node->distance + 1;
					connected_node->predecessor = node;
					enqueue(pq, connected_node);
				}
			}
		}
	}
	
	// No valid route found
	return -1;
	
found_route:
	predecessor = stop_node;
	
	do {
		//printf("%d<-", predecessor->index);
		predecessor = predecessor->predecessor;
	} while (predecessor != start_node);
	
	//printf("%d\n", predecessor->index);
	
	return 1;
}

// int main(void) {
	// breadth_first_search(&nodes[4], &nodes[7], NUM_NODES, NUM_EDGES, edges);
	// breadth_first_search(&nodes[2], &nodes[4], NUM_NODES, NUM_EDGES, edges);
// }