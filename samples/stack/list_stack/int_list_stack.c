#include "./int_list_stack.h"
#include <stdio.h>

typedef struct node Node, *List;

struct node {
    int data;
    List next;
};

struct stack{
    int size;
    List head;
};


List int_list_create(int value){
    List list = malloc(sizeof(struct node));
    list->next = NULL;
    list->data = value;

    return list;
}

void int_list_print(List list){
    printf("\nSTACK PRINT\n");
    if(list == NULL){
        return;
    }

    int i=0;
    for(List node = list; node != NULL; node = node->next){
        printf("\nstack[%d] = %d\n", i, node->data);
        i++;
    }

    printf("\n");
}

void int_list_add_head(List* list, List node){
    if(list == NULL){
        return;
    }

    node->next = *list;
    *list = node;
}

Stack int_list_stack_create(){
    Stack stack = malloc(sizeof(struct stack));

    if (stack == NULL){
        return NULL;
    }

    stack->size = 0;
    stack->head = NULL;
}

void int_list_stack_print(Stack stack){
    if(stack == NULL){
        return;
    }

    if(stack->size = 0){
        return;
    }

    int_list_print(stack->head);
}
void int_list_stack_push(Stack stack, int data){
    if(stack == NULL){
        return;
    }

    List node = int_list_create(data);
    int_list_add_head(&(stack->head), node);
}

int delete_list_head(List* list){
    if(list == NULL){
        return -1;
    }

    List node = *list;

    *list = (*list)->next;

    free(node);  

    return 1;
}

void int_list_stack_pop(Stack stack){
    if(stack == NULL){
        return;
    }

    delete_list_head(&(stack->head));
}