#include <stdio.h>
#include <stdlib.h>

#include "./integer_linked_list.h"

int main(){
    List list = int_list_create(1);

    int_list_print(list);

    List node = int_list_create(2);
    int_list_add_head(&list, node);
    int_list_print(list);

    node = int_list_create(3);
    int_list_add_tail(&list, node);
    int_list_print(list);

    printf("delete_list_head() = %d\n", delete_list_head(&list));
    int_list_print(list);

    printf("delete_list_tail() = %d\n", delete_list_tail(&list));
    int_list_print(list);

    return 0;
}