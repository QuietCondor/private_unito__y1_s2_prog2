#include <stdio.h>
#include "int_arr_stack.h"

int main(){
    Stack stack = int_arr_stack_create();

    int_arr_stack_print(stack);

    int_arr_stack_push(stack, 1);
    int_arr_stack_push(stack, 2);
    int_arr_stack_push(stack, 3);

    int_arr_stack_print(stack);
    int_arr_stack_pop(stack);
    int_arr_stack_pop(stack);

    int_arr_stack_print(stack);

    return 1;
}