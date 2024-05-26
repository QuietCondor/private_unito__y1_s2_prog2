#include <stdlib.h>

typedef struct queue IntQueue, *Queue;

Queue int_arr_queue_create();

void int_arr_queue_print(Queue queue);

void int_arr_queue_enqueue(Queue queue, int data);
int int_arr_queue_dequeue(Queue queue);