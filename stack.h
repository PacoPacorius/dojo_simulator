#ifndef _STACK
#define _STACK

#include <stdlib.h>

struct Stack {
    int top;
    unsigned int capacity;
    float array[60];
};

struct Stack create_stack();

int is_stack_full(struct Stack* stack);

int is_stack_empty(struct Stack* stack);

void push(struct Stack* stack, float number);

float pop(struct Stack* stack);

int number_of_items(struct Stack* stack);

float peek(struct Stack* stack, int index);

#endif
