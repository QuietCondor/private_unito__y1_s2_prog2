#include "./int_list_manual_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARR_DIM 4

typedef struct treeNode IntTreeNode, *TreeNode;
typedef struct queue IntQueue, *Queue;

struct treeNode{
    int data;
    TreeNode left;
    TreeNode right;
};

struct tree{
    int size;
    TreeNode root;
};

// stack code [BEGIN]
typedef struct stack StaticStack, *Stack;

#define STACK_ARR_MAX_CAPACITY 100

struct stack{
    int size;
    TreeNode* arr;
};

Stack int_arr_stack_create(){
    Stack stack = (Stack) malloc(sizeof(struct stack));

    if(stack == NULL){
        return NULL;
    }

    stack->size = 0;
    stack->arr = (TreeNode*) malloc(sizeof(TreeNode) * STACK_ARR_MAX_CAPACITY);

    return stack;
}

void internal_arr_recursive_print(TreeNode* arr, const int index){
    if(arr == NULL || index < 0){
        return;
    }

    printf("\n\tstack[%d] = %d\n", index, arr[index]->data);

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

TreeNode internal_create_node(int data){
    TreeNode node = (TreeNode) malloc(sizeof(struct treeNode));

    if(node == NULL){
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;
    node->data = data;

    return node;
}

void int_arr_stack_push(Stack stack, TreeNode data){
    if(stack == NULL){
        return;
    }

    if(stack->size >= STACK_ARR_MAX_CAPACITY){
        return;
    }

    stack->arr[stack->size] = data;
    stack->size++;
}

TreeNode int_arr_stack_pop(Stack stack){
    if(stack == NULL){
        return NULL;
    }

    TreeNode value = stack->arr[stack->size-1];
    stack->arr[stack->size-1] = NULL;
    stack->size--;
    
    return value;
}

bool int_arr_stack_is_empty(Stack stack){
    if(stack == NULL){
        return false;
    }

    return stack->size == 0;
}

// stackc code [END]


Tree tree_create(){
    Tree tree = (Tree) malloc(sizeof(struct tree));

    if(tree == NULL){
        return NULL;
    }

    tree->size = 0;
    tree->root = NULL;
}

void internal_tree_depth_first_print_pre_order(TreeNode node){
    if(node == NULL){
        return;
    }
    
    printf("\n\ttree = %d\n", node->data);
    
    if(node->left != NULL){
        internal_tree_depth_first_print_pre_order(node->left);
    }

    if(node->right != NULL){
        internal_tree_depth_first_print_pre_order(node->right);
    }
}

void tree_depth_first_print_pre_order(Tree tree){
    if(tree == NULL || tree->size == 0){
        printf("\nALBERO NULLO!  VUOTO!\n");
    }

    internal_tree_depth_first_print_pre_order(tree->root);
}

void internal_tree_depth_first_print_in_order(TreeNode node){
    if(node == NULL){
        return;
    }
    
    if(node->left != NULL){
        internal_tree_depth_first_print_pre_order(node->left);
    }

    printf("\n\ttree = %d\n", node->data);

    if(node->right != NULL){
        internal_tree_depth_first_print_pre_order(node->right);
    }
}

void tree_depth_first_print_in_order(Tree tree){
    if(tree == NULL || tree->size == 0){
        printf("\nALBERO NULLO!  VUOTO!\n");
        return;
    }

    printf("\nIN ORDER [BEGIN]:\n");

    internal_tree_depth_first_print_in_order(tree->root);

    printf("\nIN ORDER [END]:\n");
}

void internal_tree_depth_first_print_post_order(TreeNode node){
    if(node == NULL){
        return;
    }
    
    if(node->left != NULL){
        internal_tree_depth_first_print_pre_order(node->left);
    }

    if(node->right != NULL){
        internal_tree_depth_first_print_pre_order(node->right);
    }

    printf("\n\ttree = %d\n", node->data);
}

void tree_depth_first_print_post_order(Tree tree){
    if(tree == NULL || tree->size == 0){
        printf("\nALBERO NULLO!  VUOTO!\n");
        return;
    }

    printf("\nPOST ORDER [BEGIN]:\n");

    internal_tree_depth_first_print_post_order(tree->root);

    printf("\nPOST ORDER [END]:\n");
}

void internal_manual_insert(TreeNode* node, char* path, int data){
    if (node == NULL){
        return;
    }

    if (*path == '\0'){
        if(*node != NULL){
            printf("\n\tErrore: Il path punta ad un nodo esistente!\n");
            return;
        }

        TreeNode created_node = internal_create_node(data);

        if(created_node == NULL){
            printf("\n\tErrore: Creazione del nodo in errore!\n");
            return;
        }

        *node = created_node;
        return;
    }

    if(*node == NULL){
        printf("\n\tErrore: Il path punta ad un nodo non esistente!\n");
        return;
    }

    if(*path == 'L'){
        internal_manual_insert(&((*node)->left), path+1, data);
        return;
    }

    if(*path == 'R'){
        internal_manual_insert(&((*node)->right), path+1, data);
        return;
    }

    printf("\n\tErrore: Il ha un carattere non riconosciuto!\n");
}

void tree_manual_insert(Tree tree, char* path, int data){
    if (tree == NULL){
        printf("\nALBERO NULLO!\n");
        return;
    }

    internal_manual_insert(&(tree->root), path, data);
    tree->size++;
}

void tree_manual_remove(Tree tree, char* path, int data);

void tree_detph_first_with_stack(Tree tree){
    if(tree == NULL || tree->size == 0){
        printf("\nErrore: Albero vuoto!\n");
        return;
    }

    Stack stack = int_arr_stack_create();

    int_arr_stack_push(stack, tree->root);

    while(!int_arr_stack_is_empty(stack)){
        TreeNode value = int_arr_stack_pop(stack);
        printf("\n\ttree = %d\n", value->data);

        if(value->left != NULL){
            int_arr_stack_push(stack, value->left);
        }

        if(value->right != NULL){
            int_arr_stack_push(stack, value->right);
        }
    }
}

// QUEUE CODE

struct queue{
    int size;
    TreeNode* arr;
    int head;
    int tail;
};

Queue int_arr_queue_create(){
    Queue queue = (Queue) malloc(sizeof(struct queue));

    if(queue == NULL){
        return NULL;
    }

    TreeNode* arr = (TreeNode*) malloc(sizeof(TreeNode) * ARR_DIM);

    queue->size = 0;
    queue->arr = arr;
    queue->head = 0;
    queue->tail = 0;

    return queue;
}

void int_arr_queue_enqueue(Queue queue, TreeNode data){
    if(queue == NULL || queue->size >= ARR_DIM){
        return;
    }

    

    queue->arr[(queue->tail % ARR_DIM)] = data;
    queue->size++;
    queue->tail = (queue->tail % ARR_DIM) + 1;
}

TreeNode int_arr_queue_dequeue(Queue queue){
    if (queue == NULL || queue->size == 0){
        return NULL;
    }

    queue->size--;

    TreeNode data = queue->arr[queue->head];

    queue->head = (queue->head % ARR_DIM) + 1;

    return data;
}

void tree_breath_first_print(Tree tree){
    if(tree == NULL || tree->size == 0){
        printf("Errore: Il nodo e' NULLO o VUOTO!");
        return;
    }

    printf("\nBREATH FIRST SEARCH: BEGIN");
    Queue queue = int_arr_queue_create();

    int_arr_queue_enqueue(queue, tree->root);

    while(queue->size > 0){
        TreeNode node = int_arr_queue_dequeue(queue);

        printf("\ntree = %d\n", node->data);

        if(node->left != NULL){
            int_arr_queue_enqueue(queue, node->left);
        }

        if(node->right != NULL){
            int_arr_queue_enqueue(queue, node->right);
        }
    }
    printf("\nBREATH FIRST SEARCH: END");
}

void internal_tree_ordered_insert(TreeNode* node, int data){
    if(*node == NULL){
        TreeNode created_node = internal_create_node(data);

        *node = created_node;
        return;
    }

    if((*node)->data < data){
        internal_tree_ordered_insert(&((*node)->right), data);
        return;
    }

    if((*node)->data > data){
        internal_tree_ordered_insert(&((*node)->left), data);
        return;
    }

    printf("\nERRORE: Nodo gia' esistente!\n");
}

void tree_ordered_insert(Tree tree, int data){
    if(tree == NULL){
        return;
    }

    internal_tree_ordered_insert(&(tree->root), data);
}