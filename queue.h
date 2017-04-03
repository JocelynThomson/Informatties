#define QUEUESIZE 128

struct Queue {
		int a[QUEUESIZE];
		int head;
		int tail;
		int items;
};

void init_queue(Queue* pq) {
	pq->head = 0;
	pq->tail = 0;
	pq->items = 0;
}

void enqueue(Queue* pq, int data) {
	if (pq->items == QUEUESIZE) {
		return;
	}

	pq->a[pq->tail] = data;
	pq->tail--;

	if (pq->tail == -1) {
		pq->tail = QUEUESIZE - 1;
	}

	pq->items++;
}

int dequeue(Queue* pq) {
	if (pq->items == 0) {
		return 0;
	}

	int data = pq->a[pq->head];
	pq->head--;

	if (pq->head == -1) {
		pq->head = QUEUESIZE - 1;
	}

	pq->items--;

	return data;
}
