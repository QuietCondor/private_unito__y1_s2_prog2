#include <stdio.h>
#include <stdlib.h>

#include "int_arr_queue.h"

int main(){
    Queue queue = int_arr_queue_create();

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);

    printf("\nint_arr_queue_enqueue(queue, 1) = \n");
    int_arr_queue_enqueue(queue, 1);

    printf("\nint_arr_queue_enqueue(queue, 2) = \n");
    int_arr_queue_enqueue(queue, 2);

    printf("\nint_arr_queue_enqueue(queue, 3) = \n");
    int_arr_queue_enqueue(queue, 3);

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);

    printf("\nint_arr_queue_dequeue(queue) = %d ", int_arr_queue_dequeue(queue) );

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);

    printf("\nint_arr_queue_dequeue(queue) = %d ", int_arr_queue_dequeue(queue) );

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);


    printf("\nint_arr_queue_dequeue(queue) = %d ", int_arr_queue_dequeue(queue) );

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);

    printf("\nint_arr_queue_dequeue(queue) = %d ", int_arr_queue_dequeue(queue) );

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);

    printf("\nint_arr_queue_enqueue(queue, 1) = \n");
    int_arr_queue_enqueue(queue, 1);

    printf("\nint_arr_queue_enqueue(queue, 2) = \n");
    int_arr_queue_enqueue(queue, 2);

    printf("\nint_arr_queue_enqueue(queue, 3) = \n");
    int_arr_queue_enqueue(queue, 3);

    printf("\nint_arr_queue_print(queue) = \n");
    int_arr_queue_print(queue);

    return 0;
}