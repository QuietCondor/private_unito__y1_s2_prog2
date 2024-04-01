#include "char_queue_adt.h"
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
    
    /* aggiungere eventuali altre variabili per ottenere una implementazione più efficiente */
};

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue(){
    CharQueueADT queue = (*charQueue) malloc(sizeof(charQueue));

    if (queue == NULL){ // malloc non ce l'ha fatta F
        return NULL;
    }

    return queue;
}