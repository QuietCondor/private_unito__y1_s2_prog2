#include <stdlib.h>

typedef struct queue IntQueue, *Queue;

Queue int_list_queue_create();

void int_list_queue_print(Queue queue);

void int_list_queue_enqueue(Queue queue, int data);
int int_list_queue_dequeue(Queue queue);