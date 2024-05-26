#include <stdio.h>

typedef struct tree IntTree, *Tree; 

Tree tree_create();
void tree_breath_first_print(Tree tree);
void tree_depth_first_print_pre_order(Tree tree);
void tree_depth_first_print_in_order(Tree tree);
void tree_depth_first_print_post_order(Tree tree);
void tree_detph_first_with_stack(Tree tree);
void tree_manual_insert(Tree tree, char* path, int data);
void tree_manual_remove(Tree tree, char* path, int data);

void tree_ordered_insert(Tree tree, int data);