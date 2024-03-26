#include "contact.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEq(Contact c1, Contact c2){
    int equals = 1;

    // controllo prima il nome
    while(equals == 1 && *(c1.name) != '\0' && *(c2.name) != '\0'){
        equals = tolower(*(c1.name)) == tolower(*(c2.name));
        
        c1.name++;
        c2.name++;
    }

    if ((*(c1.name) == '\0' && *(c2.name) != '\0') || (*(c1.name) != '\0' && *(c2.name) == '\0')){
        return 0;
    }

    if (equals == 0){
        return 0; // non ha senso proseguire
    }

    // poi il cognome
    while(equals == 1 && *(c1.surname) != '\0' && *(c2.surname) != '\0'){
        equals = tolower(*(c1.surname)) == tolower(*(c2.surname));
        
        c1.surname++;
        c2.surname++;
    }

    if ((*(c1.surname) == '\0' && *(c2.surname) != '\0') || (*(c1.surname) != '\0' && *(c2.surname) == '\0')){
        return 0;
    }

    return equals;
}

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome∗ 
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEqEff(const Contact const *pc1, const Contact const *pc2){
    // Commento per chi corregge (se si correggono a mano anche XD)
    // non ho capito se il 'non puo essere NULL' si riferisce al fatto
    // che devo testare io se e' NULL oppure se la specifica dice che
    // il chiamante deve accertarsi che non sia NULL.
    //
    // Io nel dubbbio non mi fido e controllo lo stesso

    if(pc1 == NULL || pc2 == NULL){
        return 0; // default
    }

    int equals = 1;
    char* pc1_name = pc1->name;
    char* pc2_name = pc2->name;

    while(equals == 1 && *(pc1_name) != '\0' && *(pc2_name) != '\0'){
        equals = tolower(*(pc1_name)) == tolower(*(pc2_name));
        
        pc1_name++;
        pc2_name++;
    }

    if ((*(pc1_name) == '\0' && *(pc2_name) != '\0') || (*(pc1_name) != '\0' && *(pc2_name) == '\0')){
        return 0;
    }

    if (equals == 0){
        return 0; // non ha senso proseguire
    }

    // poi il cognome

    char* pc1_surname = pc1->surname;
    char* pc2_surname = pc2->surname;

    while(equals == 1 && *(pc1_surname) != '\0' && *(pc2_surname) != '\0'){
        equals = tolower(*(pc1_surname)) == tolower(*(pc2_surname));
        
        pc1_surname++;
        pc2_surname++;
    }

    if ((*(pc1_surname) == '\0' && *(pc2_surname) != '\0') || (*(pc1_surname) != '\0' && *(pc2_surname) == '\0')){
        return 0;
    }

    return equals;
}

int compare_ignore_case(char* str_1, char* str_2){
    char* p_str_1 = str_1;
    char* p_str_2 = str_2;

    int result = 0;
    int counter = 0;
    while(result == 0 && *p_str_1 != '\0' && *p_str_2 != '\0'){
        char curr_1 = tolower(*p_str_1);
        char curr_2 = tolower(*p_str_2);

        if (curr_1 != curr_2){ // curr_1 viene dopo
            result = curr_1 > curr_2 ? 1 : -1;
        }

        p_str_1++;
        p_str_2++;
        counter++;
    }

    if (*p_str_1 != '\0' && *p_str_2 == '\0' && counter > 0){
        p_str_2--;

        char curr_1 = tolower(*p_str_1);
        char curr_2 = tolower(*p_str_2);

        result = curr_1 > curr_2 ? 1 : -1;

        return result;
    }

    if (*p_str_1 == '\0' && *p_str_2 != '\0' && counter > 0){
        p_str_1--;

        char curr_1 = tolower(*p_str_1);
        char curr_2 = tolower(*p_str_2);

        result = curr_1 > curr_2 ? 1 : -1;

        return -1;
    }

    return result;
}

/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2
*/
int contactCmp(Contact c1, Contact c2){
    int lexic_order = compare_ignore_case(c1.surname, c2.surname);

    if(lexic_order > 0){
        return 1;
    }

    if(lexic_order < 0){
        return -1;
    }

    // confronto nome
    
    lexic_order = compare_ignore_case(c1.name, c2.name);

    if(lexic_order > 0){
        return 1;
    }

    if(lexic_order < 0){
        return -1;
    }

    return 0;
}

/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 maggiore di *pc2
*/
int contactCmpEff(const Contact const *pc1, const Contact const *pc2){
    // Commento per chi corregge (se si correggono a mano anche XD)
    // non ho capito se il 'non puo essere NULL' si riferisce al fatto
    // che devo testare io se e' NULL oppure se la specifica dice che
    // il chiamante deve accertarsi che non sia NULL.
    //
    // Io nel dubbbio non mi fido e controllo lo stesso

    if(pc1 == NULL || pc2 == NULL){
        return 0; // default
    }

    int lexic_order = compare_ignore_case(pc1->surname, pc2->surname);

    if(lexic_order > 0){
        return 1;
    }

    if(lexic_order < 0){
        return -1;
    }

    // confronto nome
    
    lexic_order = compare_ignore_case(pc1->name, pc2->name);

    if(lexic_order > 0){
        return 1;
    }

    if(lexic_order < 0){
        return -1;
    }

    return 0;
}