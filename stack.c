#include <stdio.h>
#include "stack.h"

struct Stack create_stack(unsigned int capacity){
    
    struct Stack temp_stack;
    temp_stack.capacity = 60;
    temp_stack.top = -1;

    int i;
    for(i = 0; i < temp_stack.capacity - 1; i++) {
        temp_stack.array[i] = 0.0;
        printf("\nok");
    }
    return temp_stack;
}

int is_stack_full(struct Stack* stack){
    return (stack->top == stack->capacity); 
}

int is_stack_empty(struct Stack* stack){
    return stack->top == -1;
}

void push(struct Stack* stack, float number){

    if(is_stack_full(stack) == 1){          // overflow condition, wrap back at the beginning of the int array and continue
        stack->top = 0;
        stack->array[stack->top] = number;
    }
    else {
        stack->top++;
        stack->array[stack->top] = number;
    }
}

float pop(struct Stack* stack){               
    int previous_top;

    previous_top = stack->array[stack->top];
    stack->array[stack->top] = -1;

    if(stack->top == 0)                     // underflow condition, wrap at the end of the array and continue
        stack->top = stack->capacity;
    else stack->top--;
    
    return previous_top;
}

int number_of_items(struct Stack* stack){
    int i, counter;

    for(i = 0, counter = 0; i < stack->capacity; i++)
        if(stack->array[i] != -1) counter++;
    
    return counter;
}

float peek(struct Stack* stack, int index){
    return stack->array[index];
}
