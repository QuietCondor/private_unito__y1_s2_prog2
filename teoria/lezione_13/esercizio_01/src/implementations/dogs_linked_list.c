#include "../interfaces/dogs_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char* nome;
    char* razza;
    char* eta;
    char* genere;
    // metadata
    List next;
};

List* list_create_node_by_user(){
    return NULL;
}

List list_create_node(char* nome, char* razza, char* eta, char* genere){
    List list = (List) malloc(sizeof(struct Node));

    if (list == NULL){
        return NULL;
    }

    list->nome = nome;
    list->razza = razza;
    list->eta = eta;
    list->genere = genere;

    return list;
}

void list_insert_in_head(List *p_list, List node){
    if(p_list == NULL){
        return;
    }

    node->next = *p_list;
    *p_list = node;
}

void list_remove_from_head(List *p_list){

}

void list_print(List* p_list){
    if(p_list == NULL){
        return;
    }

    List list = *p_list;

    int i = 1;
    for(List current_node = list; current_node != NULL; current_node = current_node->next){
        printf("\n\t\t------------------\n");
        printf("\n\t\tDati Cane %d:\n", i);
        printf("\n\t\t------------------\n");
        printf("\n\t\tNome: %s\n", current_node->nome);
        printf("\n\t\tRazza: %s\n", current_node->razza);
        printf("\n\t\tEta': %s\n", current_node->eta);
        printf("\n\t\tGenere: %s\n", current_node->genere);
        printf("\n\t\t------------------\n");
        i++;
    }
}