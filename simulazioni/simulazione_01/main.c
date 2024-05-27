
//==================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/**
* @brief  scrivere una funzione di confronto tra due file di testo.
* tale funzione riceve in input i due filename e confronta i file carattere per carattere.
* la funzione restituisce 
    -> -1 se vi sono errori nell’apertura dei file,
    -> 0 (zero) se i due file sono identici, altrimenti
    -> 1  se sono diversi e i due ultimi parametri contengono  numero riga e carattere a cui si trova la differenza
*
* creare anche un main() di richiamo della funzione, che stampa il risultato.
* P_IN(fname1, fname2, line, charpos):
*   - fname1 != NULL AND fname != '\0' AND fname1 punta ad un file esistente
*   - fname2 != NULL AND fname != '\0' AND fname2 punta ad un file esistente
* P_OUT(fname1, fname2, line, charpos, result)
*   - result:
        -> result = 1 <=> fname1 E fname2 hanno contenuto diverso
        -> result = 0 <=> fname1 E fname2 hanno lo stesso contenuto
        -> result = -1 <=> se vi sono problemi di apertura del file su fname1 ed fname2
*   - charpos:
        -> charpos = -1 <=> fname1 E fname2 hanno lo stesso contenuto
        -> charpos = posizione del carattere con 
                     la differenza <=> fname1 E fname2 hanno contenuto diverso 
*   - line:
        -> line = -1 <=> fname1 E fname2 hanno lo stesso contenuto
        -> line = posizione della riga con 
                  la differenza <=> fname1 E fname2 hanno contenuto diverso
*/
int compare(char* fname1, char* fname2, long* line, long* charpos){
    // controlli validita' dei path
    if(fname1 == NULL || *fname1 == '\0'){
        printf("\n\terrore: Il file numero 1 aveva path vuoto!\n");
        return -1;
    }

    // controlli validita' dei path
    if(fname2 == NULL || *fname2 == '\0'){
        printf("\n\terrore: Il file numero 2 aveva path vuoto!\n");
        return -1;
    }

    // apro 2 puntatori
    FILE* file_one = fopen(fname1, "r");
    FILE* file_two = fopen(fname2, "r");

    // controllo se ci sono problemi nell'apertura
    bool are_there_file_probl = file_one == NULL || file_two == NULL;

    if(are_there_file_probl){
        // se ci sono problemi nell'apertura
        // chiudo i file se sono rimasti aperti
        if(file_one != NULL){
            fclose(file_one);
        }

        if(file_two != NULL){
            fclose(file_one);
        }

        return -1;
    }

    // variabili di comodo per tenersi la posizione corrente del file
    int current_line = 0;
    int current_char_pos = 0;

    bool are_chars_equal = true;    // indica se i caratteri correnti sono uguali
    bool has_one_file_ended = !feof(file_one) && !feof(file_two); // indica se uno dei 2 files e' finito
    
    // continuo fin quando i file non sono finiti e i caratteri sono uguali
    while(are_chars_equal && has_one_file_ended){
        /*
            invariante:
            are_chars_equal = true SE current_char_one == current_char_two  (correnti)
                                      && current_char_one' == 'current_char_two (precedenti)

            has_one_file_ended = true SE feof(file_one) == true E feof(file_two) == true (corrente) 
                                      && feof(file_one') == true E feof(file_two') (precedente)                                     
        */

        char current_char_one;
        char current_char_two;

        // lettura del file
        fscanf(file_one, "%c", &current_char_one);
        fscanf(file_two, "%c", &current_char_two);

        are_chars_equal = (current_char_one == current_char_two);
        has_one_file_ended = !feof(file_one) && !feof(file_two);

        // se i caratteri sono uguali aumento i contatori
        // della riga e carattere
        if(are_chars_equal){
            if(current_char_one == '\n'){
                current_line++;
                current_char_pos = 0;
            }else{
                current_char_pos++;
            }
        }
    }

    // terminato il ciclo chiudo per prima cosa l'accesso
    fclose(file_one);
    fclose(file_two);

    // e poi se i file sono diversi mi salvo gli indici
    // sulle varibili
    if(!are_chars_equal || has_one_file_ended){
        *line = current_line;
        *charpos = current_char_pos;
        return 1;
    }

    // altrimenti se tutto e' OK, ritorno 0
    return 0;
}


int main(){
    long line = -1;
    long charpos = -1;
    int result_1 = compare("./files/first_file.dat", "./files/first_file.dat", &line, &charpos);
    printf("compare(diff. files) = %d with line = %ld, charpos = %ld\n", result_1, line, charpos);
    //assert(result_1 == 0 && line == -1 && charpos == -1);

    line = -1;
    charpos = -1;
    int result_2 = compare("./files/first_file.dat", "./files/second_file.dat", &line, &charpos);
    //assert(result_2 == 1 && line != -1 && charpos != -1);

    printf("compare(diff. files) = %d with line = %ld, charpos = %ld\n", result_2, line, charpos);

    return 0;
}