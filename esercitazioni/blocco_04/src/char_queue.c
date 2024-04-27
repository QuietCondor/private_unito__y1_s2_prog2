#include "char_queue_adt.h"
#include <stdlib.h>
// quello dell'esercizio e'
// #include "charQueueADT.h"
// io ho messo l'altro in locale
// per lasciare lo snake case

typedef struct listNode ListNode, *ListNodePtr;
struct listNode {
   char data;
   ListNodePtr next;
};

struct charQueue {
    ListNodePtr front; /* Punta al primo nodo della lista, che contiene l'elemento in testa alla coda, se la coda è vuota vale NULL */
    ListNodePtr rear; /* Punta all'ultimo nodo della lista, che contiene l'elemento in fondo alla coda, se la coda è vuota vale NULL */
    int size;
    /* aggiungere eventuali altre variabili per ottenere una implementazione più efficiente */
};

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue(){
    CharQueueADT queue = (CharQueueADT) malloc(sizeof(struct charQueue));

    if (queue == NULL){ // malloc non ce l'ha fatta F
        return NULL;
    }

    queue->front = NULL;
    queue->rear = NULL;

    return queue;
}

void free_nodes_recursive(ListNodePtr *node){
    if(node == NULL){
        return;
    }

    if(*node == NULL){
        return;
    }

    free_nodes_recursive(&((*node)->next));
    free(*node);
}


/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq){
    if(pq == NULL){
        return; //  non fare niente se qualcuno manda NULL
    }

    if(*pq == NULL){
        return; // stesso comportamento di sopra nel caso di lista vuota
    }

    free_nodes_recursive(&((*pq)->front));
    free(*pq); // libero memoria da pq
    *pq = NULL; // aggiorno il puntatore
}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q){
    if(q == NULL){
        return 0; //non definita
    }

    return q->front == NULL && q->rear == NULL ? 1 : 0;
}

/* @brief Aggiunge un elemento in fondo alla coda, restituisce esito 0/1 */
_Bool enqueue(CharQueueADT q, const char e){
    short ok = 1;

    if(q == NULL){
        return 0; // Coda non definita. FALSE.
    }

    if (isEmpty(q)){ // caso base: queue vuota
        ListNodePtr node = (ListNodePtr) malloc(sizeof(ListNode));
        if(node != NULL){
            q->front = node;
            q->rear = node;
            q->size = 1;

            node->data = e;
            node->next = NULL;
            
            return ok;
        } else {
            return 0;
        }
    }


    // queue non vuota

    ListNodePtr node = (ListNodePtr) malloc(sizeof(ListNode));

    if(node == NULL){
        return 0;
    }
    node->next = NULL;
    node->data = e;

    ListNodePtr currentRear = q->rear;
    currentRear->next = node;
    q->rear = node; // assegno come prossimo nodo all'ex penultimo il nuovo elemento
    q->size = q->size + 1;
    return 1;
}


/* @brief Toglie e restituisce l'elemento in testa alla coda, restituisce esito 0/1 */
_Bool dequeue(CharQueueADT q, char*res){
    short okResult = 1;
    short badResult = 1-okResult;

    if(q == NULL){
        return badResult; // NULL check
    }

    // devo rimuovere il front. Ma devo gestire piu' casi

    // caso base: la lista e' vuota
    if (isEmpty(q)){
        return badResult; // no changes
    }
    // da qui in poi la lista non e' vuota

    // caso base 2: la lista ha solo 1 elemento
    *res = q->front->data; // assegno il valore
    if(q->front == q->rear){
        free_nodes_recursive(&(q->front)); // elimino il nodo
        q->front = NULL;
        q->rear = NULL;
        q->size = 0;
        return okResult;
    }

    // caso 3: la lista non e' vuota
    // il valore l'ho gia' assegnato prima
    ListNodePtr currentFront = q->front;
    q->front = q->front->next;
    q->size = q->size - 1;
    free(currentFront);
    
    return okResult;
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q){
    // caso 1: lista non esiste
    if(q == NULL){
        return 0; // lista non esistente
    }

    // caso 2: lista vuota
    if (isEmpty(q)){
        return 0;
    }

    return q->size;

    //if (q->front == q->rear){
    //    return 1;
    //}
//
    //// caso 3: c'è almeno 1 elemento
    //int counter = 0;
//
    //for(ListNodePtr i = q->front; i != NULL; i= i->next){
    //    counter++;
    //}
//
    //return counter;
}

/* @brief Restituisce l'elemento nella posizione data (a partire dalla testa con indice zero) (senza toglierlo), restituisce esito 0/1 */
_Bool peek(CharQueueADT q, int position, char* res){
    short okResult = 1;
    short badResult = 1 - okResult;

    // caso base: lista non esiste
    if(q == NULL){
        return badResult;
    }

    // caso base: lista vuota
    if(isEmpty(q)){
        return badResult;
    }

    // ha 1 solo elemento
    if(q->front  == q->rear){
        *res = q->front->data;
        return okResult;
    }

    // ha almeno 1 elemento
    int counter = 0;
    ListNodePtr i;
    for(i = q->front; i != NULL && counter < position; i= i->next){
        counter++;
    }

    if (counter == position && i != NULL){ // trovato
        *res = i->data;
    } else {
        return badResult;
    }

    return okResult;
}