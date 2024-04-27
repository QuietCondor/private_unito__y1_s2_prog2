#include <stdlib.h>
#include <stdbool.h>

#include "./intSetADT.h"
#include "./intLinkedListSet.h"

IntSetADT mkSet() {
    IntSetADT set = (IntSetADT) malloc(sizeof(struct intSet));

    if (set == NULL){
        return NULL;
    }

    set->size = 0;
    set->front = NULL;

    return set;
}

_Bool dsSet(IntSetADT *sp) {
    if (sp == NULL){
        return 0;
    }

    IntSetADT set = *sp;

    for(ListNodePtr node = set->front; node != NULL; ){
        ListNodePtr temp_node = node;
        node = node->next;
        free(temp_node);
    }

    free(set);

    *sp = NULL;

    return 1;
}

ListNodePtr recursive_add(ListNodePtr list, ListNodePtr node, _Bool *result){
    if(list == NULL){               // lista vuota
        node->next = NULL;
        *result = true;
        return node;
    }

    if(node->data == list->data){   // il valore esiste gia' nel SET non faccio niente
        *result = false;
        return list;
    }

    if (node->data < list->data){ // elemento all'inizio
        node->next = list;
        *result = true;
        return node;
    }

    if (list->next == NULL){ // elemento alla fine
        list->next = node;
        node->next = NULL;
        *result = true;
        return list;
    }

    if (node->data < list->next->data){ // inserimento in mezzo
        *result = true;
        node->next = list->next;
        list->next = node;
        return list;
    }

    list->next = recursive_add(list->next, node, result);
    return list;
}

_Bool set_add(IntSetADT set, const int elem) {
    if(set == NULL){
        return 0;
    }

    ListNodePtr elem_to_add = (ListNodePtr) malloc(sizeof(struct listNode));
    elem_to_add->data = elem;
    elem_to_add->next = NULL;
    _Bool result = 1;


    ListNodePtr new_front = recursive_add(set->front, elem_to_add, &result);
    set->front = new_front;
    if(result == true){
        set->size++;
    }

    return result;
}

ListNodePtr try_find(ListNodePtr front, const int elem, ListNodePtr* node_predecessor){
    if(front == NULL){
        return NULL;
    }

    if (front->next == NULL){ // lista con solo 1 elemento
        *node_predecessor = NULL; // non ha predecessore il 1mo

        if (front->data == elem){
            return front;
        }

        // elemento non trovato
        return NULL;
    }

    if (front->data == elem){
        *node_predecessor = NULL; // primo elemento
        return front;
    }
    *node_predecessor = front;

    ListNodePtr node = front->next;
    for(; node->next != NULL && node->data != elem; node=node->next){
        *node_predecessor = (*node_predecessor)->next;
    }

    if(node == NULL || node->data != elem){     // elemento non trovato
        return NULL;
    }

    return node;
}

_Bool set_remove(IntSetADT set, const int elem) {
    if (set == NULL){
        return false;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr found_node = try_find(set->front, elem, &predecessor);

    if ( found_node == NULL ){ // nodo con elem non trovato
        return false;
    }

    // nodo trovato, va rimosso
    set->size--;

    if (predecessor == NULL){   // rimozione primo elemento
        if(set->front->next == NULL){   // lista con solo 1 elemento
            free(set->front);
            set->front = NULL;
            return true;
        }

        // lista con piu' elementi
        set->front = set->front->next;
        free(found_node);
        return true;
    }

    if(found_node->next == NULL){ // rimozione ultimo elemento
        predecessor->next = NULL;
        free(found_node);
        return true;
    }

    // rimozione elemento intermedio
    predecessor->next = found_node->next;
    free(found_node);

    return true;
}

_Bool set_member(const IntSetADT set, const int elem) {
    if (set == NULL){
        return false;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr found_node = try_find(set->front, elem, &predecessor);

    return found_node != NULL;
}

_Bool isEmptySet(const IntSetADT set) {
    if (set == NULL){
        return false;
    }

    return set->size == 0;
}

int set_size(const IntSetADT set) {
    if (set == NULL){
        return -1;
    }

    return set->size;
}



_Bool set_extract(IntSetADT set, int *datap) {
    if (set == NULL || set->front == NULL){
        return false;
    }

    // tolgo il primo
    ListNodePtr front = set->front;
    set->front = set->front->next;
    set->size--;
    *datap = front->data;
    free(front);

    return true;
}

_Bool set_equals(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL && set2 == NULL){
        return true;
    }

    if (set1 == NULL && set2 != NULL){
        return false;
    }

    if (set1 != NULL && set2 == NULL ){
        return false;
    }

    if (set1->size != set2->size ){
        return false;
    }

    ListNodePtr set_1_pointier = set1->front;
    ListNodePtr set_2_pointier = set1->front;

    bool are_equal = true;
    for(int i=0; i < set1->size && are_equal; i++){
        are_equal = set_1_pointier->data == set_2_pointier->data;

        set_1_pointier = set_1_pointier->next;
        set_2_pointier = set_2_pointier->next;
    }

    return are_equal;
}

_Bool subseteq(const IntSetADT set1, const IntSetADT set2) {
    bool are_equal = set_equals(set1, set2);

    if(are_equal){
        return true;
    }

    if((set1 == NULL && set2 != NULL) || (set1 != NULL && set2 == NULL)){
        return false;
    }

    if(set1->size == 0  && set2->size > 0){
        return true;
    }

    if(set1->size > set2->size){
        return false;
    }

    if((set1->front == NULL && set2->front != NULL) || (set1->front != NULL && set2->front == NULL)){
        return false;
    }

    bool is_subset = true;
    for(ListNodePtr node = set1->front; node->next != NULL && is_subset; node = node->next){
        ListNodePtr predecessor = NULL;
        ListNodePtr found_node = try_find(set2->front, node->data, &predecessor);
        is_subset = found_node != NULL;
    }

    return is_subset;
}

_Bool subset(const IntSetADT set1, const IntSetADT set2) {
    _Bool is_equal = set_equals(set1, set2);  

    if(is_equal){
        return false;
    }

    return subseteq(set1, set2);
}

IntSetADT set_union(const IntSetADT set1, const IntSetADT set2) {
    return NULL;
}

IntSetADT set_intersection(const IntSetADT set1, const IntSetADT set2) {
    return NULL;
}

IntSetADT set_subtraction(const IntSetADT set1, const IntSetADT set2) {
    return NULL;
}