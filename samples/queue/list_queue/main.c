#include <stdio.h>
#include <stdlib.h>

#include "int_list_queue.h"

int main(){
    Queue queue = int_list_queue_create();

    printf("\nint_list_queue_print(queue) = \n");
    int_list_queue_print(queue);

    printf("\nnt_list_queue_enqueue(queue, 1) = \n");
    int_list_queue_enqueue(queue, 1);

    printf("\nit_list_queue_enqueue(queue, 2) = \n");
    int_list_queue_enqueue(queue, 2);

    printf("\nint_list_queue_enqueue(queue, 3) = \n");
    int_list_queue_enqueue(queue, 3);

    printf("\nint_list_queue_print(queue) = \n");
    int_list_queue_print(queue);

    printf("\nint_list_queue_dequeue(queue) = %d ", int_list_queue_dequeue(queue) );

    printf("\nint_list_queue_print(queue) = \n");
    int_list_queue_print(queue);

    printf("\nint_list_queue_dequeue(queue) = %d ", int_list_queue_dequeue(queue) );

    printf("\nint_list_queue_print(queue) = \n");
    int_list_queue_print(queue);


    printf("\nint_list_queue_dequeue(queue) = %d ", int_list_queue_dequeue(queue) );

    printf("\nint_list_queue_print(queue) = \n");
    int_list_queue_print(queue);

    printf("\nint_list_queue_dequeue(queue) = %d ", int_list_queue_dequeue(queue) );

    printf("\nint_list_queue_print(queue) = \n");
    int_list_queue_print(queue);

    return 0;
}