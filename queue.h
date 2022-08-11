#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 60

struct Queue {
    float array[QUEUE_CAPACITY];
    int front, rear;    // pointers to insert and delete data
};

struct Queue create_queue();
void enqueue(struct Queue* queue, float num);
void dequeue(struct Queue* queue);
void print_whole_queue(struct Queue queue);

#endif
