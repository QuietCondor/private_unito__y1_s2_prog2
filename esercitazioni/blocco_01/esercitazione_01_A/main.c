#include "codice.h"

typedef struct{
    char* string;
    unsigned short base;
    int risultato_funzione;
    int risultato_atteso;
} test_item;

void fill_tests(test_item* test_suite){
    int test_counter = 0;

    /* ad esempio: */
    test_suite[0].string = "0";
    test_suite[0].base = 10;
    test_suite[0].risultato_funzione = 1;
    test_suite[0].risultato_atteso = 0;

    //test 1 - con stringa vuota, non funziona
    test_suite[1].string = "";
    test_suite[1].base = 0;
    test_suite[1].risultato_funzione = 0;
    test_suite[1].risultato_atteso = 0;

    //test 4 e 5 - segno all'inizio che viene considerato comunque, funziona
    test_suite[2].string = "+1";
    test_suite[2].base = 10;
    test_suite[2].risultato_funzione = 1;
    test_suite[2].risultato_atteso = 1;

    //test 3 - spazio vuoto all'inizio, funziona
    test_suite[3].string = " 1";
    test_suite[3].base = 10;
    test_suite[3].risultato_funzione = 1;
    test_suite[3].risultato_atteso = 1;

    //test 8 - spazio dopo il segno, non funziona
    test_suite[4].string = "- 10";
    test_suite[4].base = 10;
    test_suite[4].risultato_funzione = 0;
    test_suite[4].risultato_atteso = 0;

    //test 6 - esadecimale, funziona
    test_suite[5].string = "A";
    test_suite[5].base = 16;
    test_suite[5].risultato_funzione = 1;
    test_suite[5].risultato_atteso = 10;

    //test 12 - un risultato_attesoero uguale al risultato_attesoero della base nella stringa, funziona ma si ferma a quel risultato_attesoero
    test_suite[6].string = "11211";
    test_suite[6].base = 2;
    test_suite[6].risultato_funzione = 1;
    test_suite[6].risultato_atteso = 3;

    //test 7 - si va a capo prima del risultato_attesoero, funziona
    test_suite[7].string = "\n11";
    test_suite[7].base = 2;
    test_suite[7].risultato_funzione = 1;
    test_suite[7].risultato_atteso = 3;

    //test 2 - base troppo grande, non funziona
    test_suite[8].string = "111";
    test_suite[8].base = 40;
    test_suite[8].risultato_funzione = 0;
    test_suite[8].risultato_atteso = 0;

    //test 10 - base 36 funziona
    test_suite[9].string = "0";
    test_suite[9].base = 36;
    test_suite[9].risultato_funzione = 1;
    test_suite[9].risultato_atteso = 0;

    //test 9 - l'ultimo risultato_attesoero di una base funziona
    test_suite[10].string = "F";
    test_suite[10].base = 16;
    test_suite[10].risultato_funzione = 1;
    test_suite[10].risultato_atteso = 15;

    //test 11
    test_suite[11].string = "10";
    test_suite[11].base = 16;
    test_suite[11].risultato_funzione = 1;
    test_suite[11].risultato_atteso = 16;
}

int main(){
    int test_len = 12;
    test_item test_suite[test_len];
    fill_tests(test_suite);
    
    for(int i=0; i<test_len; i++){
        test_item curr_suite = test_suite[i];
        int curr_funz_parse_res = 0;
        int funz_result = stoub(curr_suite.string, curr_suite.base, &curr_funz_parse_res);
        
        printf("[TEST - %d]:", i);
        
        if (curr_suite.risultato_funzione != funz_result){
            printf("\nRISULTATO errato - ACTUAL: %d <-> %d : EXP\n", funz_result , curr_suite.risultato_funzione);
            printf("\t\tDATI:\n");
            printf("\t\t- Stringa: %s:\n", curr_suite.string);
            printf("\t\t- Base: %d:\n", curr_suite.base);
            printf("\t\t- Risultato Parsing: %d:\n", curr_suite.risultato_atteso);
            printf("\t\t- Risultato Funzione: %d:\n", curr_suite.risultato_funzione);
        }
        
        if (curr_suite.risultato_funzione != 0 && curr_suite.risultato_atteso != curr_funz_parse_res){
            printf("\nPARSING errato - ACTUAL: %d <-> %d : EXP\n", curr_funz_parse_res, curr_suite.risultato_atteso);
            printf("\t\tDATI:\n");
            printf("\t\t- Stringa: %s:\n", curr_suite.string);
            printf("\t\t- Base: %d:\n", curr_suite.base);
            printf("\t\t- Risultato Parsing: %d:\n", curr_suite.risultato_atteso);
            printf("\t\t- Risultato Funzione: %d:\n", curr_suite.risultato_funzione);
        }
        
        if(curr_suite.risultato_funzione == funz_result && (curr_suite.risultato_funzione == 0 || curr_suite.risultato_atteso == curr_funz_parse_res)){
            printf("OK.\n");
        }
        
        //printf("\nRisultato funzione: %d, Parsing Result: %d\n",funz_result,curr_funz_parse_res);
    }
    
}