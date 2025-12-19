#ifndef QUEUE_H
#define QUEUE_H

#define MAX 1000

typedef struct {
    int r, c;
} Point;

typedef struct {
    Point data[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int r, int c);
Point dequeue(Queue *q);

#endif
