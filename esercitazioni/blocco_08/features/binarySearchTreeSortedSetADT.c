#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedSetADT.h"

#define INT_TRUE 1
#define INT_FALSE 0

typedef struct treeNode TreeNode, *TreeNodePtr;

struct treeNode {
    void* elem;
    TreeNodePtr left, right;
};

struct sortedSetADT {
    TreeNodePtr root; /* Punta alla radice dell'albero, se l'insieme e' vuoto vale NULL */
    int (*compare)(void*, void*); /* confronto tra due elementi: -1,0,1 se primo precede, uguale o segue il secondo */
    int size; /* Numero di elementi presenti nell'insieme */
};

void stampaSet_rec(TreeNodePtr cur, void (*stampaelem)(void*)) {
    #ifdef DEBUG
    printf("( ");
    #endif
    if (cur) {
        stampaSet_rec(cur->left, stampaelem);
        (*stampaelem)(cur->elem);
        stampaSet_rec(cur->right, stampaelem);
    }
    #ifdef DEBUG
    printf(") ");
    #endif
}

// stampa i contenuti dell'insieme, data la funzione di stampa di un elemento
void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*)) {
    if(!ss) printf("Insieme non esiste\n");
    else if(sset_size(ss) == 0) printf("Insieme vuoto\n");
    else {
        printf("Insieme: (size %d) ",ss->size);
        stampaSet_rec(ss->root, stampaelem);
        printf("\n");
    }
}

// restituisce un insieme vuoto impostando funzione di confronto, NULL se errore
SortedSetADTptr mkSSet(int (*compare)(void*, void*)) {
    SortedSetADTptr tree = (SortedSetADTptr) malloc(sizeof(struct sortedSetADT));

    if (tree == NULL){
        return NULL;
    }

    tree->root = NULL;
    tree->size = 0;
    tree->compare = (*compare);

    return tree;
}

// distrugge l'insieme, recuperando la memoria
void internal_tree_delete_recursive(TreeNodePtr tree_node){
    internal_tree_delete_recursive(tree_node->left);
    internal_tree_delete_recursive(tree_node->right);
    free(tree_node);
}

_Bool dsSSet(SortedSetADTptr* ssptr) {
    if (ssptr == NULL || *ssptr == NULL){
        return false;
    }

    free(ssptr); // manca delete dei nodi ricorsivi
    internal_tree_delete_recursive((*ssptr)->root);
    *ssptr = NULL;

    return false;
}

TreeNodePtr create_node(void* data){
    TreeNodePtr tree_node_pointier = (TreeNodePtr) malloc(sizeof(struct treeNode));
    if(tree_node_pointier == NULL){
        return NULL;
    }

    tree_node_pointier->elem = data;
    tree_node_pointier->left = NULL;
    tree_node_pointier->right = NULL;
    return tree_node_pointier;
}

void internal_recursive_tree_insert(TreeNodePtr* tree_node, void* data, int (*compare)(void*, void*)){
    if(tree_node == NULL || *tree_node == NULL){ // fine del nodo raggiunta.
        *tree_node = create_node(data);
        return;
    }

    if((*compare)(data, (*tree_node)->elem) > 0 ){
        internal_recursive_tree_insert(&((*tree_node)->right), data, (*compare));
        return;
    }

    internal_recursive_tree_insert(&((*tree_node)->left), data, (*compare));
}

// aggiunge un elemento all'insieme 
_Bool sset_add(SortedSetADTptr sorted_set, void* elem) { 
    if (sorted_set == NULL){
        return false;
    }

    if(sset_member(sorted_set, elem) == INT_TRUE){
        return false;
    }

    internal_recursive_tree_insert(&(sorted_set->root), elem, sorted_set->compare);
    sorted_set->size++;
    return true;
}  

void sset_extractMin_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*));
void sset_extractMax_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*));

// funzione ausiliaria che toglie un elemento da un sottoalbero
_Bool sset_remove_rec(TreeNodePtr* cur, void* elem, int (*compare)(void*, void*)) {
    //if (*cur == NULL) return false;
    //int r = compare(elem, (*cur)->elem);
    //if (r < 0) return sset_remove_rec(&((*cur)->left), elem, compare);
    //if (r > 0) return sset_remove_rec(&((*cur)->right), elem, compare);
    //void* ptr;
    //if ((*cur)->left == NULL) {
    //    sset_extractMin_rec(cur, &ptr, compare);
    //} else if ((*cur)->right == NULL) {
    //    sset_extractMax_rec(cur, &ptr, compare);
    //} else {
    //    sset_extractMax_rec(&((*cur)->left), &ptr, compare);
    //    (*cur)->elem = ptr;
    //}
    return true;
}

// toglie un elemento all'insieme
_Bool sset_remove(SortedSetADTptr ss, void* elem) {
    if (ss && sset_remove_rec(&(ss->root), elem, ss->compare)) {
        ss->size--;
        return true;
    }
    return false;
}

// controlla se un elemento appartiene all'insieme
int sset_member(const SortedSetADT* sorted_set, void* elem) {
    if(sorted_set == NULL){
        return INT_FALSE;
    }

    return sset_search(sorted_set, elem) != NULL ? INT_TRUE : INT_FALSE;
}

void* internal_search_in_tree_recursive(TreeNodePtr node, void* data, int (*compare)(void*, void*)){
    if(node == NULL){
        return NULL;
    }

    int compare_result = (*compare)(data, node->elem);
    if( compare_result == 0){ // elemento trovato
        return node;
    }

    if(compare_result < 0){ // ricerca a sinistra
        return internal_search_in_tree_recursive(node->left, data, (*compare));
    }

    // ricerca a destra
    return internal_search_in_tree_recursive(node->right, data, (*compare));
}

// cerca un elemento nell'insieme che si compara uguale a quello dato, NULL se non trovato
void* sset_search(const SortedSetADT* sorted_set, void* elem) {
    if(sorted_set == NULL){
        return NULL;
    }

    void* found = internal_search_in_tree_recursive(sorted_set->root, elem, sorted_set->compare);

    return found;
}

// controlla se l'insieme e' vuoto
int isEmptySSet(const SortedSetADT* sorted_set) {
    int size = sset_size(sorted_set);
    return size <= 0 ? INT_TRUE : INT_FALSE;
} 

// restituisce il numero di elementi presenti nell'insieme
int sset_size(const SortedSetADT* sorted_set) {
    if (sorted_set == NULL){
        return -1;
    }

    return sorted_set->size;
} 

_Bool sset_extract(SortedSetADTptr ss, void**ptr) { // toglie e restituisce un elemento a caso dall'insieme
    return false;
} 

// controlla se due insiemi sono uguali
int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    return -1;
}

// controlla se il primo insieme e' incluso nel secondo
int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    return -1;
}

// controlla se il primo insieme e' incluso strettamente nel secondo
int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    return -1;
} 

// restituisce la sottrazione primo insieme meno il secondo, NULL se errore
SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
    return NULL;   
} 

// restituisce l'unione di due insiemi, NULL se errore
SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    return NULL; 
} 

// restituisce l'intersezione di due insiemi, NULL se errore
SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    return NULL;
}

TreeNodePtr get_leftiest_node(TreeNodePtr tree_node){
    if(tree_node == NULL){
        return NULL;
    }

    if(tree_node->left == NULL){
        return tree_node;
    }

    return get_leftiest_node(tree_node->left);
}

TreeNodePtr get_rightiest_node(TreeNodePtr tree_node){
    if(tree_node == NULL){
        return NULL;
    }

    if(tree_node->right == NULL){
        return tree_node;
    }

    return get_rightiest_node(tree_node->right);
}

// restituisce il primo elemento 
_Bool sset_min(const SortedSetADT* sorted_set, void**ptr) {
    if(sorted_set == NULL || sorted_set->root == NULL){
        return false;
    }

    // se e' ordinato e' quello sempre a sinistra
    TreeNodePtr leftiest = get_leftiest_node(sorted_set->root);
    if(leftiest == NULL){
        return false;
    }

    *ptr = leftiest->elem;

    return true;
}

// restituisce l'ultimo elemento 
_Bool sset_max(const SortedSetADT* sorted_set, void**ptr) {
    if(sorted_set == NULL || sorted_set->root == NULL){
        return false;
    }

    // se e' ordinato e' quello sempre a sinistra
    TreeNodePtr rightiest = get_rightiest_node(sorted_set->root);
    if(rightiest == NULL){
        return false;
    }

    *ptr = rightiest->elem;

    return true;
}

// toglie e restituisce il primo elemento 
_Bool sset_extractMin(SortedSetADTptr ss, void**ptr) {
    return false;    
}

// toglie e restituisce l'ultimo elemento (0 se lista vuota, -1 se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr ss, void**ptr) {
    return false;       
}

// crea un array con i contenuti del set in ordine di visita pre-order, NULL se errore
void** sset_toArray(const SortedSetADT* ss) {
    return NULL;
}