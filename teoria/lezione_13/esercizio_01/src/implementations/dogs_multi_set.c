#include "../interfaces/dogs_multi_set.h"
#include "../interfaces/dogs_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct InnerMultiSet{
    List data;
    int count;
};

bool multi_set_is_empty(MultiSet *p_set){
    return false;
}


void multi_set_insert(MultiSet *p_set) {}
void multi_set_delete_first_by_name(MultiSet *p_set, char* dog_name){}
void multi_set_delete_all_by_name(MultiSet *p_set, char* dog_name){}

void multi_set_print(MultiSet *p_set){
    if(p_set == NULL){
        return;
    }

    printf("\n\tDati Lista dei cani:\n");

    list_print(&((*p_set)->data));
}

MultiSet init(){
    printf("BEGIN: Inizializzazione SET");
    MultiSet p_multi_set = (MultiSet) malloc(sizeof(struct InnerMultiSet));

    if (p_multi_set == NULL){
        return NULL;
    }

    p_multi_set->data = NULL;
    p_multi_set->count = 0;

    printf("END: Inizializzazione SET");
    return p_multi_set;
}

MultiSet multi_set_load_from_file(const char* file_name){
    printf("BEGIN: Inizializzazione SET Da FILE");
    FILE* p_file = fopen(file_name, "r");

    if (p_file == NULL){
        return NULL;
    }

    MultiSet p_multi_set = init();
    MultiSet multi_set = p_multi_set;

    while(!feof(p_file)){
        char nome[100];
        char razza[100];
        char eta[2];
        char genere[1];

        fscanf(p_file, "%s %s %s %s\n", nome, razza, eta, genere);
        List p_node = list_create_node(nome, razza, eta, genere);

        if(multi_set->data == NULL){
            printf("END: Inizializzazione SET Da FILE");
            multi_set->data = p_node;
        } else {
            list_insert_in_head(&(multi_set->data), p_node);
        }
    }

    fclose(p_file);

    printf("END: Inizializzazione SET Da FILE");
    return p_multi_set;

}

MultiSet* multi_set_write_to_file(char* file_name){
    return NULL;
}