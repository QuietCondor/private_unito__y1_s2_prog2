#include <stdlib.h>

typedef struct node Node, *List;

struct node{
    int data;
    List next;
};

List int_sorted_list_create(int data);

void int_sorted_list_add(List* p_current, int data);
int int_sorted_list_delete(List* list, int data);

void int_list_print(List list);