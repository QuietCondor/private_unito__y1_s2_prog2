#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSet() {
    IntSortedSetADT sorted_set = (IntSortedSetADT) malloc(sizeof(struct intSortedSet));

    if(sorted_set == NULL){
        return NULL;
    }

    sorted_set->first = NULL;
    sorted_set->last = NULL;
    sorted_set->size = 0;

    return sorted_set;
}

/**
 * Elimina tutti i nodi partendo da un nodo iniziale in maniera ricorsiva
 * @param first - Il nodo di partenza
*/
void delete_nodes_recursive(ListNodePtr first){
    if(first == NULL){
        return;
    }

    delete_nodes_recursive(first->next);
    // da cui sto facendo la ricorsione al contrario
    free(first);
}

_Bool dsSSet(IntSortedSetADT *set_pointier) {
    if(set_pointier == NULL){
        return false;
    }

    IntSortedSetADT set = *set_pointier;
    if(set->size > 0) {
        // elimino i nodi dentro il set
        delete_nodes_recursive(set->first);
    }

    free(set);
    *set_pointier = NULL;

    return true;
}

/**
 * Aggiunge un nodo in una lista ordinata in maniera ricorsiva
 * @param first - Il puntamento al primo nodo della lista
 * @param node_to_add - Il nodo da aggiungere
 * @param new_end - Il puntatore con la fine:
 *      - Impostato a NULL se la fine non cambia.
 *      - Impostato con un valore se la fine e' cambiata
 * @returns Il primo nodo della lista (se serve aggiornato)
*/
ListNodePtr add_node_recursive(ListNodePtr first, ListNodePtr node_to_add, ListNodePtr* new_end){
    if(first == NULL) {  // Lista vuota. Il nodo da inserire diventa la testa
        node_to_add->next = NULL;
        *new_end = node_to_add;
        return node_to_add;
    }

    if (node_to_add->elem < first->elem){ // Il nodo deve stare prima della lista
        node_to_add->next = first;
        *new_end = NULL;
        return node_to_add;
    }

    if (first->next == NULL){ // Fine raggiunta. Il nodo deve stare alla fine
        node_to_add->next = NULL;
        first->next = node_to_add;
        *new_end = node_to_add;
        return first;
    }

    if (node_to_add->elem < first->next->elem){ // Il nodo da inserire si trova in mezzo
        node_to_add->next = first->next;
        first->next = node_to_add;
        return first;
    }

    first->next = add_node_recursive(first->next, node_to_add, new_end); // richiamo ricorsivo

    return first;
}

_Bool sset_add(IntSortedSetADT set, const int elem) {
    if (set == NULL){
        return false;
    }
    
    if(sset_member(set, elem)){
        return false; // Il set e' vuoto o L'elemento esiste gia'
    }

    // va aggiunto nel set
    ListNodePtr new_end = NULL;
    ListNodePtr node_to_add = (ListNodePtr) malloc(sizeof(struct listNode));
    node_to_add->elem = elem;
    
    ListNodePtr updated_first = add_node_recursive(set->first, node_to_add, &new_end);
    set->first = updated_first;
    if(new_end != NULL){
        set->last = new_end;
        set->last->next = NULL;
    }

    set->size++;

    return true;
}

_Bool sset_remove(const IntSortedSetADT set, const int elem) {
    if (set == NULL){
        return false;
    }

    if(isEmptySSet(set)){
        return false;
    }

    if(!sset_member(set, elem)){
        return false;
    }

    // rimozione
    ListNodePtr prev = set->first;

    if(prev->elem == elem){ // rimozione all'inizio
        if(set->size == 1){ // all'inizio con solo 1 elemento
            set->first = NULL;
            set->last = NULL;
        } else {
            set->first = set->first->next;
        }
        free(prev);
        set->size--;
        return true;
    }

    ListNodePtr node = set->first->next;
    for(; node != NULL && node->elem != elem; node = node->next){   
        prev = prev->next;
    }

    if(node == set->last){ // rimozione alla fine 
        prev->next = NULL;
        free(node);
        set->last = prev;
        set->size--;
        return true;
    }

    // rimozione in mezzo
    prev->next = node->next;
    free(node);
    set->size--;

    return true;
}

_Bool sset_member(const IntSortedSetADT set, const int elem) {
    if(set == NULL){
        return false;
    }

    if(isEmptySSet(set)){
        return false;
    }

    // ricerca dell'elemento
    ListNodePtr node = set->first;
    for(; node != NULL && node->elem != elem; node = node->next){
    }

    return node != NULL;
}

_Bool isEmptySSet(const IntSortedSetADT set) {
    if(set == NULL){
        return false;
    }

    return sset_size(set) == 0;
}

int sset_size(const IntSortedSetADT set) {
    if (set == NULL){
        return -1;
    }

    return set->size;
}

_Bool sset_extract(IntSortedSetADT set, int *ptr) {
    if(set == NULL || isEmptySSet(set)){
        return false;
    }

    *ptr = set->last->elem;
    sset_remove(set, *ptr);
    set->size--;

    return true;
}

_Bool sset_equals(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (s1 == NULL && s2 == NULL){
        return true;
    }
    
    if(s1 == NULL || s2 == NULL){
        return false;
    }

    if (isEmptySSet(s1) && isEmptySSet(s2)){
        return true;
    }


    if(sset_size(s1) != sset_size(s2)){
        return false;
    }

    ListNodePtr node_first = s1->first;
    ListNodePtr node_second = s2->first;

    bool are_equal = true;

    for(int i =0 ; i < sset_size(s1) && are_equal; i++){
        
        are_equal = node_first->elem == node_second->elem;

        node_first = node_first->next;
        node_second = node_second->next;
    }

    return are_equal;
}

_Bool sset_subseteq(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (s1 == NULL && s2 == NULL){
        return true;
    }
    if (s1 == NULL || s2 == NULL){
        return false;
    }

    if (isEmptySSet(s1) && isEmptySSet(s2)){
        return true;
    }

    if(isEmptySSet(s1)){
        return true;
    }

    if(sset_size(s1) > sset_size(s2)){
        return false;
    }

    if (sset_equals(s1,s2)){
        return true;
    }

    bool is_first_subset = true;

    ListNodePtr node_one = s1->first;
    ListNodePtr node_two = s2->first;

    for(int i=0; i<sset_size(s1) && is_first_subset && node_two != NULL ; i++){
        is_first_subset = node_one->elem == node_two->elem;

        node_one = node_one->next;
        node_two = node_two->next;
    }

    return is_first_subset;
}

_Bool sset_subset(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 == NULL && s2 == NULL){
        return false;
    }

    if(s1 == NULL || s2 == NULL){
        return false;
    }

    if(isEmptySSet(s1) && isEmptySSet(s2)){
        return false;
    }

    if(isEmptySSet(s2)){
        return false;
    }

    if(isEmptySSet(s1)){
        return true;
    }

    if(sset_equals(s1,s2)){
        return false;
    }

    return sset_subseteq(s1,s2);
}

IntSortedSetADT sset_union(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 == NULL || s2 == NULL){
        return NULL;
    }

    IntSortedSetADT new_set = mkSSet();
    if(new_set == NULL){
        return NULL;
    }

    if(isEmptySSet(s1) && isEmptySSet(s2)){ // vuoto
        return new_set;
    }

    if(isEmptySSet(s1) || isEmptySSet(s2)){ // solo 1 e' vuoto
        IntSortedSetADT bigger_set = isEmptySSet(s1) ?
        s2
        :
        s1
        ;

        for(ListNodePtr node = bigger_set->first; node != NULL; node = node->next){
            sset_add(new_set, node->elem);
        }

        return new_set;
    }

    int bigger_size = sset_size(s1) > sset_size(s2) ? sset_size(s1) : sset_size(s2);

    ListNodePtr first_node = s1->first;
    ListNodePtr second_node = s2->first;

    for(int i=0; i<bigger_size; i++){
        if (first_node != NULL){
            sset_add(new_set, first_node->elem);

            first_node = first_node->next;
        }
        if (second_node != NULL){
            sset_add(new_set, second_node->elem);
            second_node = second_node->next;
        }
    }

    return new_set; 
}

IntSortedSetADT sset_intersection(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (s1 == NULL || s2 == NULL){
        return NULL;
    }

    IntSortedSetADT new_set = mkSSet();

    if (isEmptySSet(s1) || isEmptySSet(s2)){
        return new_set;
    }

    int bigger_size = sset_size(s1) > sset_size(s2) ? sset_size(s1) : sset_size(s2);

    ListNodePtr first_node = s1->first;
    ListNodePtr second_node = s2->first;

    for(int i=0; i<bigger_size; i++){
        if(first_node != NULL && sset_member(s2, first_node->elem)){
            sset_add(new_set, first_node->elem);
            first_node = first_node->next;
        }

        if(second_node != NULL && sset_member(s1, second_node->elem)){
            sset_add(new_set, second_node->elem);
            second_node = second_node->next;
        }
    }

    return new_set;
}

IntSortedSetADT sset_subtraction(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (s1 == NULL || s2 == NULL){
        return NULL;
    }

    IntSortedSetADT new_set = mkSSet();

    if (isEmptySSet(s1)){
        return new_set;
    }


    ListNodePtr first_node = s1->first;

    for(; first_node != NULL ; first_node = first_node->next){
        if(!sset_member(s2, first_node->elem)){
            sset_add(new_set, first_node->elem);
        }
    }

    return new_set;   
}

/*
 * Cerca l'elemento massimo nella linked list e lo restituisce
 * insieme al suo predecessore.
 * @param first - Il primo nodo della lista
 * @param *predecessor - Il puntatore al predecessore
 * @returns Il nodo con il valore massimo
*/
ListNodePtr internal_get_max(ListNodePtr first, ListNodePtr *predecessor){
    if (first == NULL){
        *predecessor = NULL;
        return NULL;
    }

    ListNodePtr max_node = first;
    *predecessor = first;

    for(ListNodePtr node = first->next; node != NULL; node = node->next){
        if (max_node->elem < node->elem ){
            max_node = node;
        }
        *predecessor = (*predecessor)->next;
    }

    return max_node;
}

/*
 * Cerca l'elemento minimo nella linked list e lo restituisce
 * insieme al suo predecessore.
 * @param first - Il primo nodo della lista
 * @param *predecessor - Il puntatore al predecessore
 * @returns Il nodo con il valore minimo
*/
ListNodePtr internal_get_min(ListNodePtr first, ListNodePtr *predecessor){
    if (first == NULL){
        *predecessor = NULL;
        return NULL;
    }

    ListNodePtr min_node = first;
    *predecessor = first;

    for(ListNodePtr node = first->next; node != NULL; node = node->next){
        if (node->elem < min_node->elem ){
            min_node = node;
        }
        *predecessor = (*predecessor)->next;
    }

    return min_node;
}

_Bool sset_min(const IntSortedSetADT set, int *min_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set)){
        return false;
    }

    if (sset_size(set) == 1){
        *min_elem = set->first->elem;
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr min_node = internal_get_min(set->first, &predecessor);
    *min_elem = min_node->elem;
    return true;
}

_Bool sset_max(const IntSortedSetADT set, int *max_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set)){
        return false;
    }

    if (sset_size(set) == 1){
        *max_elem = set->first->elem;
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr max_node = internal_get_max(set->first, &predecessor);
    *max_elem = max_node->elem;
    return true;
}

_Bool sset_extractMin(IntSortedSetADT set, int *min_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set)){
        return false;
    }

    if (sset_size(set) == 1){
        *min_elem = set->first->elem;
        sset_remove(set, *min_elem);
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr min_node = internal_get_min(set->first, &predecessor);
    *min_elem = min_node->elem;
    sset_remove(set, *min_elem);
    return true;    
}

_Bool sset_extractMax(IntSortedSetADT set, int *max_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set)){
        return false;
    }

    if (sset_size(set) == 1){
        *max_elem = set->first->elem;
        sset_remove(set, *max_elem);
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr max_node = internal_get_max(set->first, &predecessor);
    *max_elem = max_node->elem;
    sset_remove(set, *max_elem);
    return true;
}