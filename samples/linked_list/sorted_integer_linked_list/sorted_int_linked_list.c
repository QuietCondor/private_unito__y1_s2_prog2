#include "./sorted_int_linked_list.h"
#include <stdlib.h>
#include <stdio.h>


List int_sorted_list_create(int data){
    List list = (List) malloc(sizeof(struct node));

    if(list == NULL){
        return NULL;
    }

    list->data = data;
    list->next = NULL;

    return list;
}

void internal_int_sorted_list_add(List* p_current, List node){
    if (p_current == NULL){
        return;
    }

    if(*p_current == NULL){ // lista vuota
        node->next = NULL;
        *p_current = node;
        return;
    }

    if(node->data < (*p_current)->data){ // inserimento all'inizio
        node->next = *p_current;
        *p_current = node;
        return;
    }

    if((*p_current)->next == NULL){ // inserimento alla fine 
        (*p_current)->next = node;
        node->next = NULL;
        return;
    }

    if(node->data < (*p_current)->next->data){
        node->next = (*p_current)->next;
        (*p_current)->next = node;
        return;
    }

    List next = (*p_current)->next;

    internal_int_sorted_list_add(&next, node);
}

void int_sorted_list_add(List* list, int data){
    if(list == NULL){
        return;
    }

    List node = int_sorted_list_create(data);

    internal_int_sorted_list_add(list, node);
}


int int_sorted_list_delete(List* list, int data){
    if(list == NULL){ // puntatore vuoto
        return -2;
    }

    if(*list == NULL){ // lista vuota / non trovato
        return -1;
    }

    if((*list)->data == data){ // nodo trovato
        free((*list));
        *list = NULL;
        return 1;
    }

    return int_sorted_list_delete(&((*list)->next), data);
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