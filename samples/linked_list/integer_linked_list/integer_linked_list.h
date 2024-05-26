typedef struct node Node, *List;

struct node {
    int data;
    List next;
};

List int_list_create();

void int_list_print(List list);

void int_list_add_head(List* list, List node);
void int_list_add_tail(List* list, List node);

int delete_list_head(List* list);
int delete_list_tail(List* list);