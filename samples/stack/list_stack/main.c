#include <stdio.h>
#include "int_list_stack.h"

int main(){
    Stack stack = int_list_stack_create();

    int_list_stack_print(stack);

    int_list_stack_push(stack, 1);
    int_list_stack_push(stack, 2);
    int_list_stack_push(stack, 3);

    int_list_stack_print(stack);
    int_list_stack_pop(stack);
    int_list_stack_pop(stack);

    int_list_stack_print(stack);

    return 1;
}