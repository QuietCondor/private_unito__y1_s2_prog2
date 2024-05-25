#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedSetADT.h"
#define INTERNAL_TRUE 1
#define INTERNAL_FALSE 0
#define INTERNAL_EMPTY_SET -1
#define INTERNAL_NULL_SET -1

typedef struct listNode ListNode, *ListNodePtr;

struct listNode {
   void* elem;
   ListNodePtr next;
};

struct sortedSetADT {
    ListNodePtr first; /* Punta al primo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    ListNodePtr last; /* Punta all'ultimo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    int (*compare)(void*, void*); /* confronto tra due elementi: -1,0,1 se primo precede, uguale o segue il secondo */
    int size; /* Numero di elementi presenti nell'insieme */
};

// for debug: stampa un insieme
void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*)) {
    ListNodePtr cur;
    if(!ss) printf("Insieme non esiste\n");
    else if(sset_size(ss) == 0) printf("Insieme vuoto\n");
    else {
        printf("Insieme: (size %d) ",ss->size);
        for(cur = ss->first; cur; cur=cur->next) (*stampaelem)(cur->elem);
        printf("\n");
    }
}    

// restituisce un insieme vuoto impostando funzione di confronto, NULL se errore
SortedSetADTptr mkSSet(int (*compare)(void*, void*)) {
    SortedSetADTptr sorted_set = (SortedSetADTptr) malloc(sizeof(SortedSetADT));

    if(sorted_set == NULL){
        return NULL;
    }

    sorted_set->first = NULL;
    sorted_set->last = NULL;
    sorted_set->compare = (*compare);
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

// distrugge l'insieme, recuperando la memoria
_Bool dsSSet(SortedSetADTptr *set_pointier) {
    if(set_pointier == NULL){
        return false;
    }

    SortedSetADTptr set = *set_pointier;
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
ListNodePtr add_node_recursive(int (*compare_function)(void*, void*), ListNodePtr first, ListNodePtr node_to_add, ListNodePtr* new_end){
    if(first == NULL) {  // Lista vuota. Il nodo da inserire diventa la testa
        node_to_add->next = NULL;
        *new_end = node_to_add;
        return node_to_add;
    }

    if ((*compare_function)(node_to_add->elem, first->elem) == -1){ // Il nodo deve stare prima della lista
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

    if ((*compare_function)(node_to_add->elem, first->next->elem) == -1 ){ // Il nodo da inserire si trova in mezzo
        node_to_add->next = first->next;
        first->next = node_to_add;
        return first;
    }

    first->next = add_node_recursive((*compare_function), first->next, node_to_add, new_end); // richiamo ricorsivo

    return first;
}

// aggiunge un elemento all'insieme 
_Bool sset_add(SortedSetADTptr set, void* elem) { 
    if (set == NULL){
        return false;
    }
    
    if(sset_member(set, elem) == INTERNAL_TRUE){
        return false; // Il set e' vuoto o L'elemento esiste gia'
    }

    // va aggiunto nel set
    ListNodePtr new_end = NULL;
    ListNodePtr node_to_add = (ListNodePtr) malloc(sizeof(struct listNode));
    node_to_add->elem = elem;
    
    ListNodePtr updated_first = add_node_recursive(set->compare, set->first, node_to_add, &new_end);
    set->first = updated_first;
    if(new_end != NULL){
        set->last = new_end;
        set->last->next = NULL;
    }

    set->size++;

    return true;
}  

// toglie un elemento all'insieme 
_Bool sset_remove(const SortedSetADTptr set, void* elem) {
    if (set == NULL){
        return false;
    }

    if(isEmptySSet(set) == INTERNAL_TRUE){
        return false;
    }

    if(sset_member(set, elem) != INTERNAL_TRUE){
        return false;
    }

    // rimozione
    ListNodePtr prev = set->first;

    if((*(set->compare))(prev->elem, elem) == 0){ // rimozione all'inizio
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
    for(; node != NULL && (*(set->compare))(node->elem, elem) != 0; node = node->next){   
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

// controlla se un elemento appartiene all'insieme
int sset_member(const SortedSetADT* set, void* elem) {
    if(set == NULL){
        return INTERNAL_NULL_SET;
    }

    if(isEmptySSet(set) == INTERNAL_TRUE){
        return INTERNAL_EMPTY_SET;
    }

    // ricerca dell'elemento
    ListNodePtr node = set->first;
    for(; node != NULL && set->compare(node->elem, elem) != 0; node = node->next){
    }

    return node != NULL ? INTERNAL_TRUE : INTERNAL_FALSE;
}
    
// controlla se l'insieme e' vuoto    
int isEmptySSet(const SortedSetADT* set) {
    if(set == NULL){
        return INTERNAL_NULL_SET;
    }

    return sset_size(set) == 0 ? INTERNAL_TRUE : INTERNAL_FALSE;
} 

// restituisce il numero di elementi presenti nell'insieme
int sset_size(const SortedSetADT* set) {
    if (set == NULL){
        return INTERNAL_NULL_SET;
    }

    return set->size;
} 

_Bool sset_extract(SortedSetADTptr set, void**ptr) { // toglie e restituisce un elemento a caso dall'insieme
    if(set == NULL || isEmptySSet(set) == INTERNAL_TRUE){
        return false;
    }

    *ptr = set->last->elem;
    sset_remove(set, *ptr);

    return true;
} 

// controlla se due insiemi sono uguali
int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    if (s1 == NULL && s2 == NULL){
        return INTERNAL_TRUE; 
    }
    
    if(s1 == NULL || s2 == NULL){
        return INTERNAL_NULL_SET;
    }

    if (isEmptySSet(s1) == INTERNAL_TRUE && isEmptySSet(s2) == INTERNAL_TRUE){
        return INTERNAL_TRUE;
    }


    if(sset_size(s1) != sset_size(s2)){
        return INTERNAL_FALSE;
    }

    ListNodePtr node_first = s1->first;
    ListNodePtr node_second = s2->first;

    bool are_equal = true;

    for(int i =0 ; i < sset_size(s1) && are_equal; i++){
        
        bool equality_check_set_one = s1->compare(node_first->elem, node_second->elem) == 0;
        bool equality_check_set_two = s2->compare(node_first->elem, node_second->elem) == 0;
        
        //are_equal = node_first->elem == node_second->elem;
        are_equal = equality_check_set_one && equality_check_set_two;

        node_first = node_first->next;
        node_second = node_second->next;
    }

    return are_equal ? INTERNAL_TRUE : INTERNAL_FALSE;
}

// controlla se il primo insieme e' incluso nel secondo
int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    if (s1 == NULL && s2 == NULL){
        return INTERNAL_TRUE;
    }
    if (s1 == NULL || s2 == NULL){
        return INTERNAL_NULL_SET;
    }

    if (isEmptySSet(s1) == INTERNAL_TRUE && isEmptySSet(s2) == INTERNAL_TRUE){
        return INTERNAL_TRUE;
    }

    if(isEmptySSet(s1) == INTERNAL_TRUE){
        return INTERNAL_TRUE;
    }

    if(sset_size(s1) > sset_size(s2)){
        return INTERNAL_FALSE;
    }

    if (sset_equals(s1,s2)){
        return INTERNAL_TRUE;
    }

    bool is_first_subset = true;

    ListNodePtr node_one = s1->first;
    ListNodePtr node_two = s2->first;

    for(int i=0; i<sset_size(s1) && is_first_subset && node_two != NULL ; i++){
        bool equality_check_set_one = s1->compare(node_one->elem, node_two->elem) == 0;
        bool equality_check_set_two = s2->compare(node_one->elem, node_two->elem) == 0;
        //is_first_subset = node_one->elem == node_two->elem;

        is_first_subset = equality_check_set_one && equality_check_set_two;

        node_one = node_one->next;
        node_two = node_two->next;
    }

    return is_first_subset;
}

// controlla se il primo insieme e' incluso strettamente nel secondo
int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL && s2 == NULL){
        return INTERNAL_FALSE;
    }

    if(s1 == NULL || s2 == NULL){
        return INTERNAL_NULL_SET;
    }

    if(isEmptySSet(s1) == INTERNAL_TRUE && isEmptySSet(s2) == INTERNAL_TRUE){
        return INTERNAL_FALSE;
    }

    if(isEmptySSet(s2) == INTERNAL_TRUE){
        return INTERNAL_FALSE;
    }

    if(isEmptySSet(s1) == INTERNAL_TRUE){
        return INTERNAL_TRUE;
    }

    if(sset_equals(s1,s2)){
        return INTERNAL_FALSE;
    }

    return sset_subseteq(s1,s2);
} 

// restituisce la sottrazione primo insieme meno il secondo, NULL se errore
SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
    if (s1 == NULL || s2 == NULL){
        return NULL;
    }

    SortedSetADTptr new_set = mkSSet(s1->compare);

    if (isEmptySSet(s1) == INTERNAL_TRUE){
        return new_set;
    }


    ListNodePtr first_node = s1->first;

    for(; first_node != NULL ; first_node = first_node->next){
        if(sset_member(s2, first_node->elem) != INTERNAL_TRUE){
            sset_add(new_set, first_node->elem);
        }
    }

    return new_set;   
} 

// restituisce l'unione di due insiemi, NULL se errore
SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL || s2 == NULL){
        return NULL;
    }

    // prendo la function del primo insieme
    SortedSetADTptr new_set = mkSSet(*s1->compare);
    if(new_set == NULL){
        return NULL;
    }

    if(isEmptySSet(s1) == INTERNAL_TRUE && isEmptySSet(s2)  == INTERNAL_TRUE){ // vuoto
        return new_set;
    }

    if(isEmptySSet(s1) == INTERNAL_TRUE || isEmptySSet(s2) == INTERNAL_TRUE){ // solo 1 e' vuoto

        ListNodePtr first_node = isEmptySSet(s1) == INTERNAL_TRUE ?
        s2->first
        :
        s1->first
        ;

        for(ListNodePtr node = first_node; node != NULL; node = node->next){
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

// restituisce l'intersezione di due insiemi, NULL se errore
SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    // FIXME: bug su 2 test
    if (s1 == NULL || s2 == NULL){
        return NULL;
    }

    SortedSetADTptr new_set = mkSSet(s1->compare);

    if (isEmptySSet(s1) == INTERNAL_TRUE || isEmptySSet(s2) == INTERNAL_TRUE){
        return new_set;
    }

    int bigger_size = sset_size(s1) > sset_size(s2) ? sset_size(s1) : sset_size(s2);

    ListNodePtr first_node = s1->first;
    ListNodePtr second_node = s2->first;

    for(int i=0; i<bigger_size; i++){
        if(first_node != NULL && sset_member(s2, first_node->elem) == INTERNAL_TRUE){
            sset_add(new_set, first_node->elem);
        }

        if(first_node != NULL){
            first_node = first_node->next;
        }

        if(second_node != NULL && sset_member(s1, second_node->elem) == INTERNAL_TRUE){
            sset_add(new_set, second_node->elem);
        }

        if(second_node != NULL){
            second_node = second_node->next;
        }
    }

    return new_set;
}

/*
 * Cerca l'elemento minimo nella linked list e lo restituisce
 * insieme al suo predecessore.
 * @param first - Il primo nodo della lista
 * @param *predecessor - Il puntatore al predecessore
 * @returns Il nodo con il valore minimo
*/
ListNodePtr internal_get_min(int (*compare_function)(void*, void*), ListNodePtr first, ListNodePtr *predecessor){
    if (first == NULL){
        *predecessor = NULL;
        return NULL;
    }

    ListNodePtr min_node = first;
    *predecessor = first;

    for(ListNodePtr node = first->next; node != NULL; node = node->next){
        //if (node->elem < min_node->elem ){
        if ((*compare_function)(node->elem, min_node->elem) < 0){
            min_node = node;
        }
        *predecessor = (*predecessor)->next;
    }

    return min_node;
}

// restituisce il primo elemento 
_Bool sset_min(const SortedSetADT* set, void**min_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set) == INTERNAL_TRUE){
        return false;
    }

    if (sset_size(set) == 1){
        *min_elem = set->first->elem;
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr min_node = internal_get_min(set->compare, set->first, &predecessor);
    *min_elem = min_node->elem;
    return true;
}

/*
 * Cerca l'elemento massimo nella linked list e lo restituisce
 * insieme al suo predecessore.
 * @param first - Il primo nodo della lista
 * @param *predecessor - Il puntatore al predecessore
 * @returns Il nodo con il valore massimo
*/
ListNodePtr internal_get_max(int (*compare_function)(void*, void*), ListNodePtr first, ListNodePtr *predecessor){
    if (first == NULL){
        *predecessor = NULL;
        return NULL;
    }

    ListNodePtr max_node = first;
    *predecessor = first;

    for(ListNodePtr node = first->next; node != NULL; node = node->next){
        //if (max_node->elem < node->elem ){
        if((*compare_function)(max_node->elem, node->elem) < 0){
            max_node = node;
        }
        *predecessor = (*predecessor)->next;
    }

    return max_node;
}

// restituisce l'ultimo elemento 
_Bool sset_max(const SortedSetADT* set, void**max_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set) == INTERNAL_TRUE){
        return false;
    }

    if (sset_size(set) == 1){
        *max_elem = set->first->elem;
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr max_node = internal_get_max(set->compare, set->first, &predecessor);
    *max_elem = max_node->elem;
    return true;
}

// toglie e restituisce il primo elemento 
_Bool sset_extractMin(SortedSetADTptr set, void**min_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set) == INTERNAL_TRUE){
        return false;
    }

    if (sset_size(set) == 1){
        *min_elem = set->first->elem;
        sset_remove(set, *min_elem);
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr min_node = internal_get_min(set->compare, set->first, &predecessor);
    *min_elem = min_node->elem;
    sset_remove(set, *min_elem);
    return true;    
}

// toglie e restituisce l'ultimo elemento (0 se lista vuota, INTERNAL_TRUE se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr set, void**max_elem) {
    if (set == NULL){
        return false;
    }

    if (isEmptySSet(set) == INTERNAL_TRUE){
        return false;
    }

    if (sset_size(set) == 1){
        *max_elem = set->first->elem;
        sset_remove(set, *max_elem);
        return true;
    }

    ListNodePtr predecessor = NULL;
    ListNodePtr max_node = internal_get_max(set->compare, set->first, &predecessor);
    *max_elem = max_node->elem;
    sset_remove(set, *max_elem);
    return true;     
}
