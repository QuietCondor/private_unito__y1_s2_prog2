#include <stdio.h>
#include "./int_list_manual_tree.h"

int main(){

    Tree tree = tree_create();

    printf("\ntree_depth_first_print_pre_order(tree)\n");
    tree_depth_first_print_pre_order(tree);

    printf("\ntree_manual_insert(tree, '0', 10)\n");
    tree_manual_insert(tree, "\0", 10);

    printf("\ntree_manual_insert(tree, 'R', 20)\n");
    tree_manual_insert(tree, "R", 20);

    printf("\ntree_manual_insert(tree, 'RR', 5)\n");
    tree_manual_insert(tree, "RR", 5);

    printf("\ntree_manual_insert(tree, 'L', 1)\n");
    tree_manual_insert(tree, "L", 1);

    printf("\ntree_depth_first_print_pre_order(tree)\n");
    tree_depth_first_print_pre_order(tree);

    printf("\ntree_depth_first_print_in_order(tree)\n");
    tree_depth_first_print_in_order(tree);

    printf("\ntree_depth_first_print_post_order(tree)\n");
    tree_depth_first_print_post_order(tree);

    printf("\ntree_detph_first_with_stack(Tree tree)\n");
    tree_detph_first_with_stack(tree);

    printf("\ntree_breath_first_print(Tree tree)\n");
    tree_breath_first_print(tree);

    Tree tree_ordered = tree_create();

    printf("\ntree_ordered_insert(Tree tree, 10)\n");
    tree_ordered_insert(tree_ordered, 10);

    printf("\ntree_ordered_insert(Tree tree, 5)\n");
    tree_ordered_insert(tree_ordered, 5);

    printf("\ntree_ordered_insert(Tree tree, 7)\n");
    tree_ordered_insert(tree_ordered, 7);

    printf("\ntree_ordered_insert(Tree tree, 4)\n");
    tree_ordered_insert(tree_ordered, 4);

    printf("\ntree_ordered_insert(Tree tree, 20)\n");
    tree_ordered_insert(tree_ordered, 20);

    printf("\ntree_ordered_insert(Tree tree, 30)\n");
    tree_ordered_insert(tree_ordered, 30);

    printf("\ntree_ordered_insert(Tree tree, 15)\n");
    tree_ordered_insert(tree_ordered, 15);

    printf("\ntree_depth_first_print_pre_order(tree)\n");
    tree_depth_first_print_pre_order(tree_ordered);

    return 0;
}