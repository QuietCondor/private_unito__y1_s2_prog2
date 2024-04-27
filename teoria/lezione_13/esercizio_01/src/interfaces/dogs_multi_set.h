#include <stdbool.h>


typedef struct InnerMultiSet* MultiSet;

bool multi_set_is_empty(MultiSet *p_set);
void multi_set_insert(MultiSet *p_set);
void multi_set_delete_first_by_name(MultiSet *p_set, char* dog_name);
void multi_set_delete_all_by_name(MultiSet *p_set, char* dog_name);
void multi_set_print(MultiSet *p_set);
MultiSet multi_set_load_from_file(const char* file_name);
//MultiSet* multi_set_write_to_file(const char* file_name);