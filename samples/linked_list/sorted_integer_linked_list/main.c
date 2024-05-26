#include <stdio.h>
#include <stdlib.h>
#include "sorted_int_linked_list.h"

int main(){
    List list = int_sorted_list_create(10);
    int_sorted_list_add(&list, 5);
    int_sorted_list_add(&list, 11);
    int_sorted_list_add(&list, 7);

    int_list_print(list);

    printf("int_sorted_list_delete(11) = %d", int_sorted_list_delete(&list, 11));

    int_list_print(list);

    return 0;
}