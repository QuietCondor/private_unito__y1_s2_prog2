#include "int_arr_stack.h"
#include <stdio.h>

#define STACK_ARR_MAX_CAPACITY 100

struct stack{
    int size;
    int* arr;
};

Stack int_arr_stack_create(){
    Stack stack = (Stack) malloc(sizeof(struct stack));

    if(stack == NULL){
        return NULL;
    }

    stack->size = 0;
    stack->arr = (int*) malloc(sizeof(int) * STACK_ARR_MAX_CAPACITY);

    return stack;
}

void internal_arr_recursive_print(int* arr, const int index){
    if(arr == NULL || index < 0){
        return;
    }

    printf("\n\tstack[%d] = %d\n", index, arr[index]);

    internal_arr_recursive_print(arr, index - 1);
}

void int_arr_stack_print(Stack stack){
    if(stack == NULL){
        return;
    }

    if(stack->size == 0){
        return;
    }

    internal_arr_recursive_print(stack->arr, (stack->size)-1);
}

void int_arr_stack_push(Stack stack, int data){
    if(stack == NULL){
        return;
    }

    if(stack->size >= STACK_ARR_MAX_CAPACITY){
        return;
    }

    stack->arr[stack->size] = data;
    stack->size++;
}

void int_arr_stack_pop(Stack stack){
    if(stack == NULL){
        return;
    }

    stack->arr[stack->size-1] = -1;
    stack->size--;
    
}