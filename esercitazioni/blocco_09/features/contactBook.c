#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "contactBook.h"
#include "../../blocco_08/features/sortedSetADT.h"
#define CONTACT_TRUE 1
#define CONTACT_FALSE 0
#define CONTACT_EMPTY -1
#define CONTACT_NULL -1
#define CONTACT_READ_FILE_PATH "../temp.csv"


/**
 Un tipo di dato per una rubrica di contatti
*/
struct contactBookADT {
    SortedSetADTptr contacts; // Tutto quello che serve è già in questa struttura
};

void stampaContact(void* elem) {
    ContactPtr contact = (ContactPtr)elem;
    printf("%s %s: %s (%s)", getName(contact), getSurname(contact), getMobile(contact), getUrl(contact));
}

int contact_cmp(void* c1, void* c2) {
    return cmpContact((ContactPtr)c1, (ContactPtr)c2);
}

// restituisce una rubrica vuota, NULL se errore
ContactBookADTptr mkCBook() {
    ContactBookADTptr rubrica = (ContactBookADTptr) malloc(sizeof(struct contactBookADT));
    if(rubrica == NULL){
        return NULL;
    }

    SortedSetADTptr generic_tree = mkSSet(contact_cmp);
    rubrica->contacts = generic_tree;

    return rubrica;
}

// distrugge la rubrica, recuperando la memoria, false se errore
_Bool dsCBook(ContactBookADTptr* book) {
    if(book == NULL || *book == NULL){
        return false;
    }

    dsSSet(&((*book)->contacts)); //elimino insieme

    free(*book);

    *book = NULL;

    return true;
}

// controlla se la rubrica e' vuota, -1 se NULL
int isEmptyCBook(const ContactBookADT* book) {
    if(book == NULL){
        return CONTACT_NULL;
    }

    int is_empty_set = isEmptySSet(book->contacts);

    return is_empty_set;
}

// restituisce il numero di contatti presenti nella rubrica, -1 se NULL
int cbook_size(const ContactBookADT* book) {
    if(book == NULL){
        return CONTACT_NULL;
    }

    int set_size = sset_size(book->contacts);

    return set_size;
}

// aggiunge un contatto alla rubrica (restituisce false se l'elemento era gia' presente, true altrimenti)
_Bool cbook_add(ContactBookADTptr book, ContactPtr cnt) {
    if (book == NULL){
        return false;
    }

    char* contact_name = getName(cnt);
    char* contact_surname = getSurname(cnt);

    if(isEmptyCBook(book) != CONTACT_TRUE && cbook_search(book, contact_name, contact_surname)){
        return false; // elemento gia' presente
    }

    bool insert_result = sset_add(book->contacts, cnt);

    return insert_result;
}

// toglie un elemento all'insieme (restituisce false se l'elemento non era presente, true altrimenti)
_Bool cbook_remove(ContactBookADTptr book, char* name, char* surname) {
    if(book == NULL){
        return false;
    }

    ContactPtr contact = cbook_search(book, name, surname);

    if(contact == NULL){
        return false;
    }

    bool set_remove = sset_remove(book->contacts, contact);

    return set_remove;
}

// restituisce un puntatore al contatto con dato nome e cognome (può essere usata per accedere o modificare il numero e url del contatto), NULL se non presente
ContactPtr cbook_search(const ContactBookADT* book, char* name, char* surname) {
    if(book == NULL || isEmptyCBook(book) == CONTACT_TRUE){
        return NULL;
    }

    ContactPtr search_contact = mkContact(name, surname, NULL, NULL);

    ContactPtr found_contact = sset_search(book->contacts, search_contact);

    dsContact(&search_contact);
    if(found_contact == NULL){
        return NULL; // not found
    }

    return found_contact;
}

// carica una rubrica da file, NULL se errore
ContactBookADTptr cbook_load(FILE* fin) {
    if(fin == NULL){
        return NULL;
    }

    ContactBookADTptr rubrica = mkCBook();

    if(rubrica == NULL){
        return NULL;
    }

    while(!feof(fin)){
        char* name = (char*) malloc(sizeof(char) * 100);
        char* surname = (char*) malloc(sizeof(char) * 100);
        char* mobile = (char*) malloc(sizeof(char) * 100);
        char* url = (char*) malloc(sizeof(char) * 100);
        
        int scan_result = fscanf(fin, " %99[^,], %99[^,], %99[^,], %99[^\n]", name, surname, mobile, url);
        //printf("Name: '%s' Surname: '%s' Mobile: '%s' URL: '%s'\n", name, surname, mobile, url);

        if(scan_result){
            ContactPtr read_contact = mkContact(name, surname, mobile, url);

            cbook_add(rubrica, read_contact);
        }
    }

    if (cbook_size(rubrica) == 0){
        dsCBook(&rubrica);
        return NULL;
    }

    return rubrica;
}

// salva una rubrica su file, false se errore
_Bool cbook_dump(const ContactBookADT* book, FILE* fout) {
    if(book == NULL || fout == NULL){
        return false;
    }

    if(isEmptyCBook(book) == CONTACT_TRUE){
        return false; // tecnicamente non ci sono stati errori, e' solo vuota la rubrica
    }

    ContactPtr* arr_set = (ContactPtr*)sset_toArray(book->contacts);

    if(arr_set == NULL){
        return false;
    }

    for(int i=0; i < sset_size(book->contacts); i++){
        ContactPtr contact = arr_set[i];
        fprintf(fout, "%s,%s,%s,%s\n", getName(contact), getSurname(contact), getMobile(contact), getUrl(contact));
    }

    return true;
}