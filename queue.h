/**
 * @file    queue.h
 * @author  Julian van Doorn
 * @brief   This file implements the queue datastructure.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

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

	pq->a[pq->tail] = data;

	if (pq->tail == QUEUESIZE - 1) {
		pq->tail = 0;
	}

	pq->item_count++;
}

/**
 * @brief       This method returns the first item (at the head of the queue).
 * @param pq    Pointer to the queue from which the item needs to be returned.
 * @return      The item at the head of the queue.
 */
int dequeue(Queue* pq) {
	if (pq->item_count == 0) {
		return -1;
	}

	int data = pq->a[pq->head];
	pq->head++;

	if (pq->head == QUEUESIZE - 1) {
		pq->head = 0;
	}

	pq->item_count--;

	return data;
}
#endif
