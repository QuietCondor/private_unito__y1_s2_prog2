#include "integer_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

List int_list_create(int value){
    List list = malloc(sizeof(struct node));
    list->next = NULL;
    list->data = value;

    return list;
}

void int_list_print(List list){
    printf("\nLIST PRINT\n");
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
void int_list_add_head(List* list, List node){
    if(list == NULL){
        return;
    }

    node->next = *list;
    *list = node;
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

    *list = (*list)->next;

    free(node);  

    return 1;
}

int delete_list_tail(List* list){
    if(list == NULL){
        return -1;
    }

    if(*list == NULL){ // nodo "vuoto"
        return 0;
    }

    if((*list)->next == NULL){ // lista con 1 nodo
        free((*list));
        *list = NULL;
        return 1;
    }

    List next = (*list)->next;
    if(next->next == NULL){
        free(next);
        (*list)->next = NULL;
        return 1;
    }


    return delete_list_tail(&next);
}