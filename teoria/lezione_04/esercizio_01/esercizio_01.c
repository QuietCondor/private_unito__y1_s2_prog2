#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./esercizio_01_typedef_support.c"
/*
    CONSEGNA:
    Scrivere un programma che:
    
    1.  Tramite typedef dichiara il nuovo tipo canzone: una struct adatta a contenere
        informazioni su un brano musicale (es. titolo, autore, durata in minuti)
    2.  Definisce tramite #define una costante MAX
    3.  Alloca dinamicamente un array di MAX elementi di tipo canzone (non esagerate
        con MAX, bastano 3 elementi)
    4.  Esegue un ciclo in cui chiede all’utente le info sulle canzoni e man mano li
        inserisce nell’array
    5.  Visualizza a terminale i contenuti dell’array
    6.  Dealloca l’array e termina
 */

canzone* crea_canzone(char titolo[MAX_NAME], char autore[MAX_AUTORE], short durata)
{
    // creo l'oggetto
    canzone* p_canzone = (canzone*) malloc(sizeof(canzone*));
    
    if(p_canzone == NULL){
        // escaping del null
        return NULL;
    }
    
    // le stringhe si copiano con strcpy (ricordarsi di importare string.h)
    strcpy(p_canzone->titolo, titolo);
    strcpy(p_canzone->autore, autore);
    p_canzone->durata = durata;
    
    return p_canzone;
}
    
void print_canzone(canzone canzone){
    printf("\n\n--------------------- STAMPA DATI CANZONE ---------------------\n");
    printf("\t\tTITOLO: %s\n", canzone.titolo);
    printf("\t\tAUTORE: %s\n", canzone.autore);
    printf("\t\tDURATA: %d\n", canzone.durata);
    printf("\n--------------------- FINE DATI CANZONE ---------------------\n\n");
}

int main()
{
    // definisco un'array
    
    canzone canzoni[2];
    
    canzone* p_canzone = crea_canzone("Danger Zone", "Sorry non mi ricordo chi la canta", 3);
    canzoni[0] = *p_canzone;
    
    p_canzone = crea_canzone("Bipolare", "Medy cartier baby XD", 3);
    canzoni[1] = *p_canzone;
    
    print_canzone(canzoni[0]);
    print_canzone(canzoni[1]);
    // la parte di inserimento dei dati dall'utente si fa con una scanf dai.

    return 0;
}