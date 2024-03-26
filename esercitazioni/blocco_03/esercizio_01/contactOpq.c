#include "contactOpq.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

struct contact {
   char* name; 
   char* surname;
   char* mobile;
   char* url;
};

/**
* @brief Crea un nuovo contatto 
*
* @param name La stringa che contiene il nome 
* @param surname La stringa che contiene il cognome 
* @param mobile La stringa che contiene il numero di cellulare 
* @param url La stringa che contiene la home page  
* @return Il puntatore alla struttura che rappresenta il contatto, NULL se ((name == NULL) || (surname == NULL))
*/
ContactPtr mkContact(char* name, char* surname, char* mobile, char* url){
    if (name == NULL || surname == NULL){
        return NULL; // casistica del null
    }

    ContactPtr contact = (ContactPtr) malloc(sizeof(Contact));

    if (contact == NULL){
        return NULL; // per sicurezza
    }

    contact->name = name;
    contact->surname = surname;
    contact->mobile = mobile;
    contact->url = url;

    return contact;
}

/**
* @brief Dealloca una struttura Contact e mette il relativo puntatore (che dunque deve essere passato per riferimento) a NULL
*
* @param cntptr il puntatore al contatto (non può essere NULL). Nota: cntptr è un puntatore a puntatore a Contact
*/
void dsContact(ContactPtr* cntptr){
    if(cntptr == NULL){
        return; // per sicurezza
    }

    if((*cntptr) == NULL){
        return; // per sicurezza
    }

    free((*cntptr));
    *cntptr = NULL;
}

/**
* @brief Aggiorna il telefono di un contatto 
*
* @param cnt Il contatto 
* @param mobile La stringa che contiene il nuovo numero di cellulare  (può essere NULL)
*/
void updateMobile(ContactPtr cnt, char* newMobile){
    if(cnt == NULL){
        return; // per sicurezza
    }

    cnt->mobile = newMobile;
}

/**
* @brief Aggiorna la home page di un contatto 
*
* @param cnt Il contatto 
* @param url La stringa che contiene la nuova home page  (può essere NULL)
*/
void updateUrl(ContactPtr cnt, char* newUrl){
    if(cnt == NULL){
        return; // per sicurezza
    }

    cnt->url = newUrl;
}

/**
* @brief Restituisce il nome di un contatto 
*
* @param cnt Il contatto 
* @return url La stringa che contiene il nome del contatto 
*/
char* getName(const ContactPtr cnt){
    if (cnt == NULL){
        return NULL; // per sicurezza (?)
    }

    return cnt->name;
}

/**
* @brief Restituisce il cognome di un contatto 
*
* @param cnt Il contatto 
* @return url La stringa che contiene il cognome del contatto 
*/
char* getSurname(const ContactPtr cnt){
    if (cnt == NULL){
        return NULL; // per sicurezza (?)
    }

    return cnt->surname;
}

/**
* @brief Restituisce il numero di cellulare di un contatto 
*
* @param cnt Il contatto 
* @return url La stringa che contiene il numero di cellulare  (può essere NULL)
*/
char* getMobile(const ContactPtr cnt){
    if (cnt == NULL){
        return NULL; // per sicurezza (?)
    }

    return cnt->mobile;
}

/**
* @brief Restituisce la home page di un contatto 
*
* @param cnt Il contatto 
* @return url La stringa che contiene la nuova home page  (può essere NULL)
*/
char* getUrl(const ContactPtr cnt){
    if (cnt == NULL){
        return NULL; // per sicurezza (?)
    }

    return cnt->url;
}

/**
* @brief Controlla se due contatti sono uguali rispetto al cognome e al nome
* 
* @param cnt1 Il primo contatto
* @param cnt2 Il secondo contatto 
* @return 1 se i due contatti hanno lo stesso cognome e lo stesso nome, 0 altrimenti 
*/
_Bool equalsContact(const ContactPtr cnt1, const ContactPtr cnt2){
    char* p_contatto_1_surname = cnt1->surname;
    char* p_contatto_2_surname = cnt2->surname;

    bool are_diff = false;
    while(!are_diff && (*p_contatto_1_surname != '\0' && *p_contatto_2_surname != '\0')){
        char surname_1 = tolower(*p_contatto_1_surname);
        char surname_2 = tolower(*p_contatto_2_surname);

        are_diff = surname_1 != surname_2;
        
        p_contatto_1_surname++;
        p_contatto_2_surname++;
    }

    if (are_diff || (*p_contatto_1_surname != '\0' && *p_contatto_2_surname == '\0') || (*p_contatto_1_surname == '\0' && *p_contatto_2_surname != '\0')){
        // sono diversi per caratteri aggiuntivi.
        return 0;
    }

    // controllo nome
    char* p_contatto_1_name = cnt1->name;
    char* p_contatto_2_name = cnt2->name;
    while(!are_diff && (*p_contatto_1_name != '\0' && *p_contatto_2_name != '\0')){
        char name_1 = tolower(*p_contatto_1_name);
        char name_2 = tolower(*p_contatto_2_name);

        are_diff = name_1 != name_2;
        
        p_contatto_1_name++;
        p_contatto_2_name++;
    }

    if (are_diff || (*p_contatto_1_name != '\0' && *p_contatto_2_name == '\0') || (*p_contatto_1_name == '\0' && *p_contatto_2_name != '\0')){
        // sono diversi per caratteri aggiuntivi.
        return 0;
    }

    return 1;
}

/**
* @brief Confronta due contatti in ordine lessicografico in base al cognome e al nome
*
* @param cnt1 Il primo contatto 
* @param cnt2 Il secondo contatto 
* @return -1 se cnt1 minore cnt2, 0 se cnt1 uguale cnt2, 1 se cnt1 maggiore cnt2
*/
int cmpContact(const ContactPtr cnt1, const ContactPtr cnt2){
    char* p_contatto_1_surname = cnt1->surname;
    char* p_contatto_2_surname = cnt2->surname;

    int compare_result = 0;

    while(compare_result == 0 && (*p_contatto_1_surname != '\0' && *p_contatto_2_surname != '\0')){
        char surname_1 = tolower(*p_contatto_1_surname);
        char surname_2 = tolower(*p_contatto_2_surname);

        if(surname_1 !=  surname_2){
            compare_result = surname_1 > surname_2? 1 : -1;
        }
        
        p_contatto_1_surname++;
        p_contatto_2_surname++;
    }

    if (compare_result != 0){
        // sono diversi per caratteri aggiuntivi.
        return compare_result;
    }

    if (*p_contatto_1_surname != '\0' && *p_contatto_2_surname == '\0'){
        return 1;
    }

    if (*p_contatto_1_surname == '\0' && *p_contatto_2_surname != '\0'){
        return -1;
    }

    char* p_contatto_1_name = cnt1->name;
    char* p_contatto_2_name = cnt2->name;

    compare_result = 0;

    while(compare_result == 0 && (*p_contatto_1_name != '\0' && *p_contatto_2_name != '\0')){
        char name_1 = tolower(*p_contatto_1_name);
        char name_2 = tolower(*p_contatto_2_name);

        if(name_1 !=  name_2){
            compare_result = name_1 > name_2? 1 : -1;
        }
        
        p_contatto_1_name++;
        p_contatto_2_name++;
    }

    if (compare_result != 0){
        // sono diversi per caratteri aggiuntivi.
        return compare_result;
    }

    if (*p_contatto_1_name != '\0' && *p_contatto_2_name == '\0'){
        return 1;
    }

    if (*p_contatto_1_name == '\0' && *p_contatto_2_name != '\0'){
        return -1;
    }

    return 0;
}