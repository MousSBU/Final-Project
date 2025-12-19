#ifndef STACK_H
#define STACK_H
#define MAX 1000

typedef struct {
    int r, c;
} Point;

typedef struct {
    Point data[MAX];
    int top;
} Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
void push(Stack *s, int r, int c);
Point pop(Stack *s);

#endif