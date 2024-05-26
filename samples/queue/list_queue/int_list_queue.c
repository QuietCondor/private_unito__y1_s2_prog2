#include "./int_list_queue.h"
#include <stdio.h>

typedef struct node Node, *List;

struct node {
    int data;
    List next;
};

struct queue{
    int size;
    List head;
    List tail;
};

// LIST METHODS
List int_list_create(int value){
    List list = malloc(sizeof(struct node));
    list->next = NULL;
    list->data = value;

    return list;
}

void int_list_add_tail(List* list, List node){
    if(list == NULL){
        return;
    }

    if(*list == NULL){
        *list = node;
        (*list)->next = NULL;
        return;
    }

    int_list_add_tail(&((*list)->next), node);
}

int delete_list_head(List* list){
    if(list == NULL){
        return -1;
    }

    List node = *list;

    int data = node->data;

    *list = (*list)->next;

    free(node);  

    return data;
}

void int_list_print(List list){
    printf("\nQUEUE PRINT\n");
    if(list == NULL){
        return;
    }

    int i=0;
    for(List node = list; node != NULL; node = node->next){
        printf("\tlist[%d] = %d\n", i, node->data);
        i++;
    }

    printf("\n");
}


Queue int_list_queue_create(){
    Queue queue = (Queue) malloc(sizeof(struct queue));

    if(queue == NULL){
        return NULL;
    }

    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
}

void int_list_queue_print(Queue queue){
    if(queue == NULL || queue->size == 0){
        printf("\nQUEUE Vuota!\n");
        return;
    }

    int_list_print(queue->head);
}

void int_list_queue_enqueue(Queue queue, int data){
    if(queue == NULL){
        return;
    }

    List node = int_list_create(data);

    if(node == NULL){
        return;
    }

    int_list_add_tail(&(queue->head), node);

    queue->tail = node;
    queue->size++;
}
int int_list_queue_dequeue(Queue queue){
    if(queue == NULL || queue->size == 0){
        return -1;
    }


    int data = delete_list_head(&(queue->head));
    queue->size--;

    if(queue->size == 0){
        queue->head = NULL;
        queue->tail = NULL;
    }

    return data;
}