#include "./int_arr_queue.h"
#include <stdio.h>
#define ARR_DIM 4

struct queue{
    int size;
    int* arr;
    int head;
    int tail;
};


Queue int_arr_queue_create(){
    Queue queue = (Queue) malloc(sizeof(struct queue));

    if(queue == NULL){
        return NULL;
    }

    int* arr = (int*) malloc(sizeof(int) * ARR_DIM);

    queue->size = 0;
    queue->arr = arr;
    queue->head = 0;
    queue->tail = 0;

    return queue;
}



void int_arr_queue_print(Queue queue){
    if(queue == NULL || queue->size == 0){
        printf("\nQUEUE Vuota!\n");
        return;
    }

    int c = queue->head;
    for(int i = 0; i < queue->size; i++){
        printf("\tqueue[%d] = %d\t", c, queue->arr[c]);
        c = (c + 1 ) % ARR_DIM;
    }
}

void int_arr_queue_enqueue(Queue queue, int data){
    if(queue == NULL || queue->size >= ARR_DIM){
        return;
    }

    

    queue->arr[(queue->tail % ARR_DIM)] = data;
    queue->size++;
    queue->tail = (queue->tail % ARR_DIM) + 1;
}

int int_arr_queue_dequeue(Queue queue){
    if (queue == NULL || queue->size == 0){
        return -1;
    }

    queue->size--;

    int data = queue->arr[queue->head];

    queue->head = (queue->head % ARR_DIM) + 1;

    return data;
}