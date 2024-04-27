Sviluppare un modulo contact.c che implementi la specifica:

contact.h:
```c

/**  Un tipo di dato per i contatti telefonici e cyberspaziali
*/
typedef struct contact {
   char* name;   
   char* surname;
   char* mobile;
   char* url;
} Contact, *ContactPtr;

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEq(Contact c1, Contact c2);


/**  @brief Controlla se due contatti hanno lo stesso nome e cognome∗ 
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEqEff(const Contact const *pc1, const Contact const *pc2);


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2
*/
int contactCmp(Contact c1, Contact c2);


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 maggiore di *pc2
*/
int contactCmpEff(const Contact const *pc1, const Contact const *pc2);

```

In cui si definisce il seguente tipo di dato Contact: 

```c
/**  Un tipo di dato per contatti telefonici e cyberspaziali */

typedef struct contact {

   char* name;   

   char* surname;

   char* mobile;

   char* url;

} Contact, *ContactPtr;
```

e alcune funzioni di utilità che operano su di esso. 
Applicare la metodologia TDD, procedendo in modo iterativo e incrementale.