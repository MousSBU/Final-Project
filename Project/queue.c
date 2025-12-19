#include "queue.h"

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front > q->rear;
}

void enqueue(Queue *q, int r, int c) {
    q->rear++;
    q->data[q->rear].r = r;
    q->data[q->rear].c = c;
}

Point dequeue(Queue *q) {
    return q->data[q->front++];
}