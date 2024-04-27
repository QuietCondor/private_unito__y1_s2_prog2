#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#define MAT_LEN 36
#define BASE_LOWER 2
#define BASE_UPPER 36

/**
 * @brief Controlla se la base e' valida
 * 
 * @param s: la base dell'elemento
 * @return  TRUE: Se la base e' valida. FALSE altrimenti
 */
bool check_base(unsigned short base){
    return base<BASE_LOWER || base > BASE_UPPER;
}

/**
 * @brief Controlla che un carattere sia dentro il vettore
 *
 * @param vet_digits    : Il vettore con i caratteri accettati
 * @param candidate     : Il carattere da controllare
 * @returns TRUE se e' dentro il vettore. FALSE altrimenti
 * */
bool is_in_digits(char vet_digits[MAT_LEN], char candidate){
    int i;
    for(i=0; i<MAT_LEN && candidate != vet_digits[i]; i++){}
    
    if(i<MAT_LEN){
        // trovato
        return true;
    }
    
    // non trovato
    return false;
}

/**
 * @brief Restituisce l'esponenziale di un dato numero (non controlla esponenziali negativi)
 *
 * @param base_number:  Il numero di base
 * @param exponential:  L'esponente
 *
 * @return L'esponenziale del numero    
 * */
int get_int_exp(int base_number, int exponential){
    if (exponential == 0){
        return 1; // n^0 = 1 per ogni n
    }
    int result = base_number;
    for(int i=1; i<exponential; i++){
        result = result * base_number;
    }
    
    return result;
}

/**
 * @brief   Calcola l'esponente massimo di una stringa di una data base partendo
 *          da sinistra.
 * 
 * @param base:     La data base
 * @param s:        La stringa
 * @param vet_digits:       Il vettore con le cifre possibili
 * @returns     L'esponente massimo del valore numerico rappresentato dalla stringa (se e' convertibile)
 *              -1 altrimenti.
*/
int get_max_exp(unsigned short base, char *s, char vet_digits[MAT_LEN]){
    
    int result = 0;
    bool all_in_base = true;
    while(*s != '\0' && all_in_base){
        bool found  = false;
        int i=0;
        while(!found && i < MAT_LEN && i < base){
            if(vet_digits[i] == *s){
                found = true;
            }
            
            i++;
        }
        
        all_in_base = all_in_base && found;
        if (all_in_base){
            result++;
        }
        s++;
    }
    
    
    
    return result-1;
}

/**
 * @brief   Calcola il dato numero nella data base in base 10.
 * 
 * @param base:             La data base di partenza
 * @param s:                La stringa
 * @param exp_max:          L'esponente massimo dell'elemento
 * @param vet_digits:       Il vettore con le cifre possibili
 * @returns     Il valore convertito
*/
int get_conversion(unsigned short base, char *s, int exp_max, char vet_digits[MAT_LEN]){
    int sum = 0;
    int exp_position = exp_max;
    
    while(*s != '\0' && exp_position >=0){
        int current_digit = 0;
        int i=0;
        for(; i< MAT_LEN && vet_digits[i] != *s; i++){
        }
        
        if (i<MAT_LEN){ // la stringa e' nella matrice
            current_digit = i * get_int_exp(base, exp_position);
            sum+=current_digit;
        }
        
        exp_position--;
        s++;
    }

    return sum;
}

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
int stoub(char *s, unsigned short b, int*r) {
    bool check_base_res = check_base(b);


    if(check_base_res){
        return 0; // base errata
    }

    // skippo gli spazi iniziali
    while((*s == ' ' || iscntrl(*s)) && *s != '\0'){
        s++;
    }

    if(*s == '\0'){
        return 0; // stringa vuota
    }

    bool is_negative = false;
    char vet[MAT_LEN] = {
        '0','1','2','3','4','5','6','7','8','9',
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };
    
    if(!isdigit(*s)){ // se la prima cifra da sinistra non e' un numero
        if(*s == '-'){
            is_negative = true;
        }

        bool is_sign = *s == '+' || *s == '-';
        if(!is_sign && !is_in_digits(vet, *s)){
            return 0;
        }
        
        if (is_sign){
            s++; // "+1" -> "1" oppure "-1" -> "1"
        }

    }

    

    int max_exp = get_max_exp(b, s, vet);

    if(max_exp == -1){
        return 0; // Non ci sono numeri da convertire.
    }

    int converted_unsigned = get_conversion(b, s, max_exp,vet);

    converted_unsigned = is_negative ? -1 * converted_unsigned : converted_unsigned;

    *r = converted_unsigned;

    return 1;
}