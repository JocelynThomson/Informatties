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
	pq->tail = 0;
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

	pq->item_count++;
}

int dequeue(Queue* pq) {
	if (pq->item_count == 0) {
		return 0;
	}

	pq->head++;
	int data = pq->a[pq->head];

	if (pq->head == QUEUESIZE - 1) {
		pq->head = 0;
	}

	pq->item_count--;

	return data;
}

int peek(Queue* pq) {
	if (pq->item_count == 0) {
		return 0;
	}

	return pq->a[pq->head];
}
