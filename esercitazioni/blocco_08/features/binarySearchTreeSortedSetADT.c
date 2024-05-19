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
void internal_tree_delete_recursive(TreeNodePtr* tree_node, int* count_deleted){
    if(tree_node == NULL || *tree_node == NULL){
        return;
    }

    internal_tree_delete_recursive(&(*tree_node)->left, count_deleted);
    internal_tree_delete_recursive(&(*tree_node)->right, count_deleted);

    free(*tree_node);
    *tree_node = NULL;
    (*count_deleted)++;
}

_Bool dsSSet(SortedSetADTptr* ssptr) {
    if (ssptr == NULL || *ssptr == NULL){
        return false;
    }

    int count_deleted = 0;
    internal_tree_delete_recursive(&((*ssptr)->root), &count_deleted);
    free(*ssptr); // manca delete dei nodi ricorsivi
    *ssptr = NULL;

    return true;
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

/*
 * Cerca un dato nell'albero usando una funzione custom di compare
 * @param node - Il nodo corrente in fase di ricerca
 * @param data - Il dato da cercare nell'albero
 * @param compare - La funzione custom di compare
 * @returns Il puntatore al nodo trovato
*/
TreeNodePtr internal_search_in_tree_recursive(TreeNodePtr node, void* data, int (*compare)(void*, void*), TreeNodePtr* parent_node){
    if(node == NULL){
        return NULL;
    }

    int compare_result = (*compare)(data, node->elem);
    if( compare_result == 0){ // elemento trovato
        return node;
    }

    *parent_node = node;
    if(compare_result < 0){ // ricerca a sinistra
        return internal_search_in_tree_recursive(node->left, data, (*compare), parent_node);
    }

    // ricerca a destra
    return internal_search_in_tree_recursive(node->right, data, (*compare), parent_node);
}

// toglie un elemento all'insieme
_Bool sset_remove(SortedSetADTptr sorted_set, void* elem) {
    if (sorted_set == NULL) { // insieme nullo
        return false;
    }

    TreeNodePtr parent_node = NULL;
    TreeNodePtr found_node = internal_search_in_tree_recursive(sorted_set->root, elem, sorted_set->compare, &parent_node);
    if(found_node == NULL) {
        return false;
    }

    int count_deleted = 0;
    if (parent_node != NULL){ // aggiusto nodi figli
        int compare_result = (*(sorted_set->compare))(parent_node->elem, found_node->elem);
        if(compare_result < 0 ){ // parent_node->elem < found_node->elem
            parent_node->right = NULL;
        }

        if(compare_result > 0 ){ // parent_node->elem < found_node->elem
            parent_node->left = NULL;
        }
        internal_tree_delete_recursive(&found_node, &count_deleted);
        sorted_set->size = sorted_set->size - count_deleted;
    } else { // rimosso root
        sorted_set->root = NULL;
        sorted_set->size = 0;
        internal_tree_delete_recursive(&found_node, &count_deleted);
    }

    return true;
}

// controlla se un elemento appartiene all'insieme
int sset_member(const SortedSetADT* sorted_set, void* elem) {
    if(sorted_set == NULL || isEmptySSet(sorted_set)){
        return INT_FALSE;
    }

    return sset_search(sorted_set, elem) != NULL ? INT_TRUE : INT_FALSE;
}

// cerca un elemento nell'insieme che si compara uguale a quello dato, NULL se non trovato
void* sset_search(const SortedSetADT* sorted_set, void* elem) {
    if(sorted_set == NULL){
        return NULL;
    }

    TreeNodePtr partent_node = NULL;
    TreeNodePtr found = internal_search_in_tree_recursive(sorted_set->root, elem, sorted_set->compare, &partent_node);

    return found != NULL ? found->elem : NULL;
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

_Bool sset_extract(SortedSetADTptr sorted_set, void**ptr) { // toglie e restituisce un elemento a caso dall'insieme
    if (sorted_set == NULL){
        return false;
    }

    if(isEmptySSet(sorted_set)){
        return false;
    }

    TreeNodePtr rightiest = get_rightiest_node(sorted_set->root);
    *ptr = rightiest->elem;
    sset_remove(sorted_set, rightiest->elem);

    return true;
} 

// controlla se due insiemi sono uguali
int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    if(s1 == NULL && s2 == NULL){
        return INT_TRUE;
    }

    if(s1 == NULL || s2 == NULL){
        return INT_FALSE;
    }

    if(isEmptySSet(s1) && isEmptySSet(s2)){
        return INT_TRUE;
    }

    if(isEmptySSet(s1) || isEmptySSet(s2)){
        return INT_FALSE;
    }

    int is_s1_subset = sset_subseteq(s1,s2);
    int is_s2_subset = sset_subseteq(s2,s1);

    return is_s1_subset == INT_TRUE && is_s2_subset == INT_TRUE ? INT_TRUE : INT_FALSE;
}

_Bool internal_tree_subset_check_recursive(TreeNodePtr first_node, const SortedSetADT* second_set){
    bool search_result = sset_member(second_set, first_node->elem) == INT_TRUE ? true : false;

    bool is_left_present = first_node->left != NULL ?
        internal_tree_subset_check_recursive(first_node->left, second_set)
        :
        true;

    bool is_right_present = first_node->right != NULL ?
        internal_tree_subset_check_recursive(first_node->right, second_set)
        :
        true;

    return search_result 
        && is_left_present
        && is_right_present
    ;
}

// controlla se il primo insieme e' incluso nel secondo
int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL && s2 == NULL){
        return INT_TRUE;
    }

    if(s1 == NULL || s2 == NULL){
        return INT_FALSE;
    }

    if(isEmptySSet(s1) || isEmptySSet(s2)){
        return INT_TRUE;
    }

    bool is_subset = internal_tree_subset_check_recursive(s1->root, s2);

    return is_subset ? INT_TRUE : INT_FALSE;
}

// controlla se il primo insieme e' incluso strettamente nel secondo
int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL && s2 == NULL){
        return INT_FALSE;
    }

    if(s1 == NULL || s2 == NULL){
        return INT_FALSE;
    }

    if(isEmptySSet(s1) || isEmptySSet(s2)){
        return INT_FALSE;
    }

    int is_s1_subset = sset_subseteq(s1, s2);
    int are_subset_equals = sset_equals(s1, s2);

    return is_s1_subset == INT_TRUE && are_subset_equals == INT_FALSE ? INT_TRUE : INT_FALSE;
} 

void internal_subtraction_set_recursive(SortedSetADTptr target_set, const SortedSetADT* second_set, TreeNodePtr first_node){
    if(target_set == NULL || second_set == NULL){
        return;
    }

    int exists_result = sset_member(second_set, first_node->elem);

    if(exists_result == INT_FALSE){
        sset_add(target_set, first_node->elem);
    }

    if(first_node->left != NULL){
        internal_subtraction_set_recursive(target_set, second_set, first_node->left);
    }

    if(first_node->right != NULL){
        internal_subtraction_set_recursive(target_set, second_set, first_node->right);
    }
}

// restituisce la sottrazione primo insieme meno il secondo, NULL se errore
SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL || s2 == NULL){
        return NULL;
    }

    if(!isEmptySSet(s1) && isEmptySSet(s2)){
        SortedSetADTptr new_set = sset_union(s1, s2);
        return new_set;
    }

    SortedSetADTptr new_set = mkSSet(s1->compare);
    if(isEmptySSet(s1)){
        return new_set;
    }

    internal_subtraction_set_recursive(new_set, s2, s1->root);

    return new_set;   
} 

/*
 * Aggiunge tutti i nodi del sotto albero in un dato albero
 * @param set - Il dato albero in cui inserire i nodi
 * @param node - Il sotto albero in cui inserire i nodi
*/
void internal_union_set_recursive(SortedSetADTptr set, TreeNodePtr node){
    if(set == NULL){
        return;
    }

    sset_add(set, node->elem);
    if(node->left != NULL){
        internal_union_set_recursive(set, node->left);
    }

    if(node->right != NULL){
        internal_union_set_recursive(set, node->right);
    }
}

void internal_intersection_set_recursive(SortedSetADTptr target_set, const SortedSetADT* second_set, TreeNodePtr first_node){
    if(target_set == NULL || second_set == NULL){
        return;
    }

    int exists_result = sset_member(second_set, first_node->elem);

    if(exists_result == INT_TRUE){
        sset_add(target_set, first_node->elem);
    }

    if(first_node->left != NULL){
        internal_intersection_set_recursive(target_set, second_set, first_node->left);
    }

    if(first_node->right != NULL){
        internal_intersection_set_recursive(target_set, second_set, first_node->right);
    }
}

// restituisce l'unione di due insiemi, NULL se errore
SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL || s2 == NULL){
        return NULL;
    }

    SortedSetADTptr new_set = mkSSet(s1->compare);
    internal_union_set_recursive(new_set, s1->root);
    internal_union_set_recursive(new_set, s2->root);

    return new_set; 
} 

// restituisce l'intersezione di due insiemi, NULL se errore
SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 == NULL || s2 == NULL){
        return NULL;
    }

    SortedSetADTptr new_set = mkSSet(s1->compare);
    if(isEmptySSet(s1) || isEmptySSet(s2)){
        return new_set;
    }

    internal_intersection_set_recursive(new_set, s2, s1->root);

    return new_set; 
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
_Bool sset_extractMin(SortedSetADTptr sorted_set, void**ptr) {
    if(sorted_set == NULL || isEmptySSet(sorted_set)){
        return false;
    }

    TreeNodePtr leftiest = get_leftiest_node(sorted_set->root);
    *ptr = leftiest->elem;
    sset_remove(sorted_set, leftiest->elem);
    return true;    
}

// toglie e restituisce l'ultimo elemento (0 se lista vuota, -1 se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr sorted_set, void**ptr) {
    if(sorted_set == NULL || isEmptySSet(sorted_set)){
        return false;
    }

    TreeNodePtr rightiest = get_rightiest_node(sorted_set->root);
    *ptr = rightiest->elem;
    sset_remove(sorted_set, rightiest->elem);
    return true;    
}

void internal_tree_append_to_array(TreeNodePtr node, void** arr, int* current_index){
    if(node == NULL || node->elem == NULL){
        return;
    }

    arr[*current_index] = node->elem;
    (*current_index)++;

    if(node->left != NULL){
        internal_tree_append_to_array(node->left, arr, current_index);
    }

    if(node->right != NULL){
        internal_tree_append_to_array(node->right, arr, current_index);
    }
}
// crea un array con i contenuti del set in ordine di visita pre-order, NULL se errore
void** sset_toArray(const SortedSetADT* sorted_set) {
    if(sorted_set == NULL){
        return NULL;
    }

    int size = sset_size(sorted_set);
    void** allocated_array = (void**) malloc(sizeof(void*) * size);
    int index = 0;
    internal_tree_append_to_array(sorted_set->root, allocated_array, &index);

    //int* arr = (int*) malloc(sizeof(int) * 5);
    //void** arr = (void**) malloc(sizeof(void*) * 5);

    return allocated_array;
}