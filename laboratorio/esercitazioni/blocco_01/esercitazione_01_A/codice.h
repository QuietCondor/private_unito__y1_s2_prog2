#ifndef CODICE_IMPORTS
 #define CODICE_IMPORTS
 #include <stdbool.h>
 #include <ctype.h>
 #include <stdio.h>

 #define MAT_LEN 36
 #define BASE_LOWER 2
 #define BASE_UPPER 36
 
 bool is_in_digits(char vet_digits[MAT_LEN], char candidate);
 int get_max_exp(unsigned short base, char *s, char vet_digits[MAT_LEN]);
 int get_conversion(unsigned short base, char *s, int exp_max, char vet_digits[MAT_LEN]);
 int get_int_exp(int base_number, int exponential);
 
 /**
  * @brief Converte una stringa in intero (data la base).
  *
  * Calcola il numero intero rappresentato dalla stringa in argomento nella base
  * (la base deve essere un numero intero nel range 2..36) in argomento:
  * − saltando gli eventuali spazi bianchi iniziali,
  * − riconoscendo l'eventuale (singolo) carattere del segno,
  * − fermandosi al raggiungimento del primo carattere non cifra nella base data (le cifre per la base 36 sono: 0,..,9,A,..,Z).
  *
  * @param s: Una stringa da convertire.
  * @param b: La base.
  * @param r: L'indirizzo dell'intero dove memorizzare il risultato.
  * @return   Restituisce 0 se 'b' non è nell’intervallo ammesso, oppure se non trova nessuna cifra valida
  *           (e in tal caso il valore all'indirizzo r non è significativo).
  *           Altrimenti restituisce 1, e scrive all'indirizzo r il numero intero rappresentato nella stringa nella base data.
  *           Non si accorge dell'eventuale overflow (restituendo in questo caso un risultato scorretto).
  */
 int stoub(char *s, unsigned short b, int*r);
#endif

