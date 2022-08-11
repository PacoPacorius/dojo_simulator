/* implement queue with mod N indexing */

/* some weird shit is happening with the rear and front indexes draw them on paper,
 * find out what is wrong
 */

#include "queue.h"

//int main(){
//    struct Queue business = create_queue();
//    char c;
//    float f;
//
//    while(c != 'q'){
//        printf("\nfront: %d\t\trear: %d", business.front, business.rear);
//        printf("\n1. Insert");
//        printf("\n2. Dequeue");
//        printf("\n3. Print");
//        printf("\n\nWhat do? ");
//
//        scanf(" %c", &c);
//        getchar();      // consume the newline
//        
//        switch(c){
//        case '1':
//            printf("Type number: ");
//            scanf("%f", &f);
//            insert(&business, f);
//            break;
//        case '2':
//            dequeue(&business);
//            break;
//        case '3':
//            print_whole_queue(business);
//            break;
//        }
//    }
//    
//}


struct Queue create_queue(){
    struct Queue temp_queue;
    int i;

    for(i = 0; i < QUEUE_CAPACITY; i++)
        temp_queue.array[i] = 0.0;

    temp_queue.front = -1; temp_queue.rear = -1;

    return temp_queue;
}

void enqueue(struct Queue* queue, float num){
    if((queue->front - queue->rear) % QUEUE_CAPACITY == 1 || (queue->front == 0 && queue->rear == 4)) dequeue(queue);          // y does this no work when rear = 4 and front = 0???
    if(queue->front == -1 || queue->rear == -1){
        queue->front = 0;      // if queue is empty, move front to right position
        queue->rear = 0;
    }
    else {
        queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;       // wrap around to the start if end is reached
    }
    queue->array[queue->rear] = num;
}

void dequeue(struct Queue* queue){
    if(queue->front == -1){
        printf("Queue Underflow");
        queue->rear = -1;
        queue->front = -1;
    }
    else {
        queue->front = (queue->front + 1) % QUEUE_CAPACITY;
    }
}

void print_whole_queue(struct Queue queue){
   int i;
   int j = 0;
   printf("\n");
   if(queue.rear >= queue.front){
       for(i = queue.front; i < queue.rear + 1; i++){
           printf("%f ", queue.array[i]);
           if(i % 10 == 0) printf("\n");
       }
   }
   else {
        for(i = queue.front; i < QUEUE_CAPACITY; i++){
            printf("%f ", queue.array[i]);
            j++;
            if(j % 10 == 0){
                printf("\n");
                j = 0; 
            }
        }

        for(i = 0; i < queue.rear + 1; i++){
            printf("%f ", queue.array[i]);
            j++;
            if(j % 10 == 0){
                printf("\n");
                j = 0; 
            }
        }
   }
   printf("\n\n");
}
