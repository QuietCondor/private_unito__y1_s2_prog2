#include <stdio.h>
#include "./interfaces/dogs_multi_set.h"

int main(){
    printf("Starting program..\n");

    MultiSet p_set = multi_set_load_from_file("../data/dogs_data.txt");
    if (p_set == NULL){
        printf("Caricamento dei dati fallito!");
        return 1;
    }


    int user_choiche;
    do{
        printf("Menu principale di gestione del canile.\n");
        printf("Scegli un'opzione (da 0 a 2):\n");
        printf("\t0. Esci e salva.\n");
        printf("\t1. Aggiungi un cane.\n");
        printf("\t2. Rimuovi un cane.\n");
        printf("\t3. Visualizza tutti i cani.\n");

        scanf("%d", &user_choiche);

        switch(user_choiche){
            case 0:
                // Salva sul file.
                printf("\nShutting down the program..\n");
                break;
            case 1:
                // Aggiungi un cane
                //multi_set_insert(p_set);
                break;
            case 2:
                // Rimuovi un cane
                //multi_set_delete_first_by_name(p_set, char* dog_name);
                break;
            case 3:
                // Visualizza tutti i cani
                multi_set_print(&p_set);
                break;
            default:
                printf("\nScelta non valida!\n");
                break;
        }
    } while(user_choiche != 0);

    
    return 0;
}