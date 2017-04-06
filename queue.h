/**
 * @file    queue.h
 * @author  Julian van Doorn
 * @brief   This file implements the queue datastructure. 
 */

#define QUEUESIZE 128

/**
 * @brief The queue is a FIFO (first in firt out) data structure.
 *
 * The first item put in the queue is also the first item to be retrieved. Any subsequent items
 * are put on the "back" of the queue. 
 */
struct Queue {
		int a[QUEUESIZE];   /**< The array which hold the items on the queue.  */
		int head;           /**< The first item on the queue that gets returned. */
		int tail;           /**< The last item on the queue. */
		int item_count;     /**< The total count of items on the queue */
};

Queue nav_queue;

/**
 * @brief       This method empties the queue.
 * @param pq    Pointer to the queue that needs to be emptied.
 */
void empty_queue(Queue* pq) {
	pq->head = 0;
	pq->tail = -1;
	pq->item_count = 0;
}

/**
 * @brief       This method initializes the queue.
 * @param pq    Pointer to the queue that needs to be initialized.
 */
void init_queue(Queue* pq) {
	empty_queue(pq);
}

/**
 * @brief       Puts an item (data) on the queue.
 * @param pq    Pointer to the queue on wich to place the data.
 * @param data  The data that needs to be put in the queue.
 */
void enqueue(Queue* pq, int data) {
	if (pq->item_count == QUEUESIZE - 1) {
		return;
	}

	pq->tail++;

	nav_queue.a[pq->tail] = data;

	if (pq->tail == QUEUESIZE - 1) {
		pq->tail = 0;
	}

	writeDebugStreamLine("ENQUEUEING %d", data);

	pq->item_count++;
}

/**
 * @brief       This method returns the first item (at the head of the queue).
 * @param pq    Pointer to the queue from which the item needs to be returned.
 * @return      The item at the head of the queue.
 */
int dequeue(Queue* pq) {
	if (pq->item_count == 0) {
		return 0;
	}

	int data = pq->a[pq->head];
	pq->head++;

	if (pq->head == QUEUESIZE - 1) {
		pq->head = 0;
	}

	pq->item_count--;

	writeDebugStreamLine("DEQUEUEING %d", data);

	return data;
}

/**
 * @brief      Looks at the first item in the queue.
 * @param pq   The pointer to the queue.
 * @return     The first item in the queue or zero if the queue is empty.
 */
int peek(Queue* pq) {
	if (pq->item_count == 0) {
		return 0;
	}

	return pq->a[pq->head];
}
=======
#define QUEUESIZE 128

struct Queue {
		int a[QUEUESIZE];
		int head;
		int tail;
		int item_count;
};

Queue nav_queue;

void empty_queue(Queue* pq) {
	pq->head = 0;
	pq->tail = -1;
	pq->item_count = 0;
}

void init_queue(Queue* pq) {
	empty_queue(pq);
}

void enqueue(Queue* pq, int data) {
	if (pq->item_count == QUEUESIZE - 1) {
		return;
	}

	pq->tail++;

	nav_queue.a[pq->tail] = data;

	if (pq->tail == QUEUESIZE - 1) {
		pq->tail = 0;
	}

	writeDebugStreamLine("ENQUEUEING %d", data);

	pq->item_count++;
}

int dequeue(Queue* pq) {
	if (pq->item_count == 0) {
		return 0;
	}

	int data = pq->a[pq->head];
	pq->head++;

	if (pq->head == QUEUESIZE - 1) {
		pq->head = 0;
	}

	pq->item_count--;

	writeDebugStreamLine("DEQUEUEING %d", data);

	return data;
}

int peek(Queue* pq) {
	if (pq->item_count == 0) {
		return 0;
	}

	return pq->a[pq->head];
}
