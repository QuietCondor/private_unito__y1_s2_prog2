#include <stdlib.h>

typedef struct stack StaticStack, *Stack;


Stack int_arr_stack_create();

void int_arr_stack_print(Stack stack);
void int_arr_stack_push(Stack stack, int data);
void int_arr_stack_pop(Stack stack);