#include <stdbool.h>

typedef struct Node* List;


List list_create_node(char* nome, char* razza, char* eta, char* genere);
void list_insert_in_head(List *p_list, List node);
void list_remove_from_head(List *p_list);
void list_print(List* p_list);