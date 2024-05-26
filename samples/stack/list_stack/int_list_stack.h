#include <stdlib.h>

typedef struct stack StaticStack, *Stack;


Stack int_list_stack_create();

void int_list_stack_print(Stack stack);
void int_list_stack_push(Stack stack, int data);
void int_list_stack_pop(Stack stack);