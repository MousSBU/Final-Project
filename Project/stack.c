#include "stack.h"

void initStack(Stack *s){
    s->top = -1;
}

int isEmpty(Stack *s){
    return s->top == -1;
}

void push(Stack *s, int r, int c){
    s->top++;
    s->data[s->top].r=r;
    s->data[s->top].c=c;
}

Point pop(Stack *s){
    return s->data[s->top--];
}