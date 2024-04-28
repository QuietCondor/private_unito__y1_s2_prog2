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
    ListNodePtr set_2_pointier = set2->front;

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

void copy_set(const IntSetADT set1, IntSetADT* set2){
    if(set2 == NULL){
        *set2 = mkSet();
    }

    for(ListNodePtr node=set1->front; node != NULL; node = node->next){
        ListNodePtr prev = NULL;
        ListNodePtr found_node_in_one = try_find((*set2)->front, node->data, &prev );

        if(found_node_in_one == NULL){
            set_add(*set2, node->data);
        }
    }
}

IntSetADT set_union(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL && set2 == NULL){
        return NULL;
    }

    if(set1 == NULL){
        return NULL;
    }

    if(set2 == NULL){
        return NULL;
    }

    IntSetADT union_set = mkSet();

    if (union_set == NULL){
        return NULL;
    }

    if(set_equals(set1, set2)){
        copy_set(set2, &union_set);
        return union_set;
    }


    if(set1->front == NULL || set1->size == 0){
        copy_set(set2, &union_set);
        return union_set;
    }

    if(set2->front == NULL || set2->size == 0){
        copy_set(set1, &union_set);
        return union_set;
    }

    int max_size = set1->size > set2->size ? set1->size : set2->size;
    ListNodePtr set_one_node = set1->front;
    ListNodePtr set_two_node = set2->front;

    

    for(int i=0; i<max_size; i++){
        ListNodePtr prev = NULL;
        
        if(set_two_node != NULL){
            ListNodePtr found_node_in_one = try_find(union_set->front, set_two_node->data, &prev );
            if(found_node_in_one == NULL){
                set_add(union_set, set_two_node->data);
            }
            set_two_node = set_two_node->next;
        }

        if(set_one_node != NULL){
            ListNodePtr found_node_in_two = try_find(union_set->front, set_one_node->data, &prev );
            if(found_node_in_two == NULL){
                set_add(union_set, set_one_node->data);
            }
            set_one_node = set_one_node->next;
        }

    }

    return union_set;
}

IntSetADT set_intersection(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL && set2 == NULL){
        return NULL;
    }

    if(set1 == NULL){
        return NULL;
    }

    if(set2 == NULL){
        return NULL;
    }

    IntSetADT intersection_set = mkSet();

    if (intersection_set == NULL){
        return NULL;
    }

    if(set1->front == NULL || set1->size == 0){
        return intersection_set;
    }

    if(set2->front == NULL || set2->size == 0){
        return intersection_set;
    }

    if(set_equals(set1, set2)){
        copy_set(set2, &intersection_set);
        return intersection_set;
    }

    int max_size = set1->size > set2->size ? set1->size : set2->size;
    ListNodePtr set_one_node = set1->front;
    ListNodePtr set_two_node = set2->front;

    

    for(int i=0; i<max_size; i++){
        ListNodePtr prev = NULL;
        
        if(set_two_node != NULL){
            ListNodePtr found_node_in_one = try_find(set1->front, set_two_node->data, &prev );
            ListNodePtr found_intersect = try_find(intersection_set->front, set_two_node->data, &prev );
            if(found_node_in_one != NULL && found_intersect == NULL){
                set_add(intersection_set, set_two_node->data);
            }
            set_two_node = set_two_node->next;
        }

        if(set_one_node != NULL){
            ListNodePtr found_two_in_one = try_find(set2->front, set_one_node->data, &prev );
            ListNodePtr found_intersect = try_find(intersection_set->front, set_one_node->data, &prev );
            if(found_two_in_one != NULL && found_intersect == NULL){
                set_add(intersection_set, set_one_node->data);
            }
            set_one_node = set_one_node->next;
        }

    }

    return intersection_set;
}

IntSetADT set_subtraction(const IntSetADT set1, const IntSetADT set2) {
    if(set1 == NULL || set2 == NULL || set1->front == NULL || set1->front == NULL){
        return NULL;
    }

    IntSetADT subtr_set = mkSet();

    if (subtr_set == NULL){
        return NULL;
    }

    if(set_size(set1) == 0){
        return subtr_set;
    }

    if(set_size(set2) == 0){
        copy_set(set1, &subtr_set);

        return subtr_set;
    }

    copy_set(set1, &subtr_set);

    // devo togliere gli elementi di set2 che stanno in set1
    for(ListNodePtr node = set2->front; node != NULL; node = node->next){
        set_remove(subtr_set, node->data);
    }

    return subtr_set;
}