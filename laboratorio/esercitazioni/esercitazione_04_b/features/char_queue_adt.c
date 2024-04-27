#include "./charQueueADT.h"
#include <stdlib.h>
#include <string.h>

/* il valore 8 può essere cambiato */
#define INITIAL_CAPACITY 2
#define EXPAND_CAPACITY_PARAM 2
#define REDUCE_CAPACITY_PARAM 2

struct charQueue {
    int capacity; /* capacity == INITIAL CAPACITY^n, per qualche numero naturale n >= 1 */
    char* a; /* array, di dimensione capacity, che memorizza gli elementi presenti nella coda */
    int size; /* numero di elementi presenti nella coda (0 <= size <= capacity) */
    int rear; /* prima posizione libera in a (dove sarà memorizzato il prossimo elemento della coda (0 <= rear <= capacity-1) */
    int front; /* posizione in a dove (se size > 0) è memorizzato il primo elemento della coda (0 <= front <= capacity-1) */
    /* (front==rear) se e solo se ((size == 0) || (size == capacity)) */
    /* Gli elementi della coda sono in: a[front..rear-1] se rear > front, e in a[front..capacity-1],a[0..rear-1], se rear <= front */
    /* L'array si espande di un fattore due quando si riempie, e si dimezza (se capacity > INITIAL_CAPACITY) */
    /* quando size scende a capacity/4 (parametri personalizzabili) */      
    /* Se capacity > INITIAL_CAPACITY, allora il numero di elementi in coda è >= capacity/4 */
};


/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    CharQueueADT queue = (CharQueueADT) malloc(sizeof(struct charQueue));
    
    if (queue == NULL) {
        return NULL;
    }

    // inizializzo coda
    queue->capacity = INITIAL_CAPACITY;
    queue->a = malloc(sizeof(char) * queue->capacity);
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;

    return queue;
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    if(pq == NULL || *pq == NULL){
        return;
    }

    if((*pq)->a != NULL){
        free((*pq)->a);
    }

    free(*pq);

    *pq = NULL;
}

int get_next_position(int size, int current_pointier){
    return ( current_pointier + 1 ) % size;
}

int get_previous_position(int size, int current_pointer) {
    return (current_pointer - 1 + size) % size;
}

char* reallocate_array(char* arr, int old_size, int new_size, int front, int rear) {
    char* new_arr = (char*) calloc(new_size, sizeof(char)); // Utilizza calloc per inizializzare a zero.
    if (new_arr == NULL) {
        return NULL;
    }
    
    if (rear > front) {
        // Copia direttamente se non circolare.
        memcpy(new_arr, arr + front, (rear - front) * sizeof(char));
    } else if (rear <= front && old_size > 0) { // Aggiunta di controllo per old_size
        // Copia in due passi se circolare.
        int size_first_part = old_size - front;
        memcpy(new_arr, arr + front, size_first_part * sizeof(char));
        memcpy(new_arr + size_first_part, arr, rear * sizeof(char));
    }

    return new_arr;
}

char* extend_array(char* arr, int current_dimension, int desired_dimension){
    if (arr == NULL){
        return NULL;
    }

    char* extended_arr = (char*) malloc(sizeof(char)*desired_dimension);

    if (extended_arr == NULL){
        return NULL;
    }

    for(int i = 0; i < current_dimension; i++){
        extended_arr[i] = arr[i];
    }

    return extended_arr;
}

char* reduce_array(char* arr, int current_dimension, int desired_dimension, int* start_index, int* end_index){
    if (arr == NULL){
        return NULL;
    }

    char* extended_arr = (char*) malloc(sizeof(char)*desired_dimension);

    if (extended_arr == NULL){
        return NULL;
    }

    for(int i = *start_index; i <= *end_index; i++){
        extended_arr[i % desired_dimension ] = arr[i];
    }

    *start_index = *start_index % desired_dimension;
    *end_index = *end_index % desired_dimension;

    return extended_arr;
}

/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    if(q == NULL){
        return 0;
    }

    if(q->size == q->capacity){
        int new_capacity = q->capacity * EXPAND_CAPACITY_PARAM;
        char* new_arr = reallocate_array(q->a, q->capacity, new_capacity, q->front, q->rear);
        if (!new_arr) {
            return 0;
        }
        free(q->a);
        q->a = new_arr;
        // Realign front and rear
        q->rear = q->size; // rear ora è la prima posizione libera dopo tutti gli elementi.
        q->front = 0; // front ora è 0 poiché tutti gli elementi sono allineati dall'inizio.
        q->capacity = new_capacity;
    }

    q->a[q->rear] = e;
    q->rear = get_next_position(q->capacity, q->rear);
    q->size++;

    return 1;
}

/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
    if (q == NULL){
        return 0;
    }

    if (isEmpty(q)){
        return 0;
    }

    *res = q->a[q->front];
    q->front = get_next_position(q->capacity, q->front);
    q->size--;

    if (q->capacity > INITIAL_CAPACITY && q->size <= q->capacity / REDUCE_CAPACITY_PARAM) {
        int new_capacity = q->capacity / EXPAND_CAPACITY_PARAM;
        char* new_arr = reallocate_array(q->a, q->capacity, new_capacity, q->front, q->rear);
        if (!new_arr) {
            return 0;
        }
        free(q->a);
        q->a = new_arr;
        // Realign front and rear
        q->rear = q->size;
        q->front = 0;
        q->capacity = new_capacity;
    }

    return 1;
}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if (q == NULL){
        return 1;
    }

    return q->size == 0; 
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    if (q == NULL){
        return -1; // non esiste
    }

    return q->size;
}

/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res) {
    if (q == NULL){
        return 0;
    }

    if (isEmpty(q)){
        return 0;
    }

    if (position >= q->size){
        return 0;
    }

    int module_position = (q->front + position) % q->capacity;

    *res = q->a[module_position];

    return 1;
}