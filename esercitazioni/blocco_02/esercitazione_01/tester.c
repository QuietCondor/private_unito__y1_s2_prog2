#include "contact.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    Contact input_1;
    Contact input_2;
    int boolean_result;
    int integer_result;
} test_item;

void test_contact_eq(){
    test_item tests[2];

    tests[0].input_1.name = "nome_1";
    tests[0].input_1.surname = "cognome_1";
    tests[0].input_1.mobile = "1231421";
    tests[0].input_1.url = "http://esercizio.discutibile.com";

    tests[0].input_2.name = "nome_1";
    tests[0].input_2.surname = "cognome_1";
    tests[0].input_2.mobile = "1231421";
    tests[0].input_2.url = "http://esercizio.discutibile.com";

    tests[0].boolean_result = 1;

    int shoud_eq = contactEq(tests[0].input_1, tests[0].input_2);

    if(shoud_eq != tests[0].boolean_result){
        printf("[contactEq] - ShouldBeEquals: ERRORE - i due contatti non sono uguali! (dovrebbero)");
    }

    tests[1].input_1.name = "nome_1";
    tests[1].input_1.surname = "cognome_1";
    tests[1].input_1.mobile = "1231421";
    tests[1].input_1.url = "http://esercizio.discutibile.com";

    tests[1].input_2.name = "DIFF_nome_1";
    tests[1].input_2.surname = "DIFF_cognome_1";
    tests[1].input_2.mobile = "1231421";
    tests[1].input_2.url = "http://esercizio.discutibile.com";
    tests[1].boolean_result = 0;
    int shoud_not_eq = contactEq(tests[1].input_1, tests[1].input_2);

    if(shoud_not_eq != tests[1].boolean_result){
        printf("[contactEq] - ShouldNOTBeEquals: ERRORE - i due contatti sono uguali! (non dovrebbero)");
    }
}

void test_contact_eff(){
    test_item tests[3];
    char* test_prefix = "contactEqEff";

    tests[0].input_1.name = "nome_1";
    tests[0].input_1.surname = "cognome_1";
    tests[0].input_1.mobile = "1231421";
    tests[0].input_1.url = "http://esercizio.discutibile.com";

    tests[0].input_2.name = "nome_1";
    tests[0].input_2.surname = "cognome_1";
    tests[0].input_2.mobile = "1231421";
    tests[0].input_2.url = "http://esercizio.discutibile.com";

    tests[0].boolean_result = 1;

    int shoud_eq = contactEqEff(&(tests[0].input_1), &(tests[0].input_2));

    if(shoud_eq != tests[0].boolean_result){
        printf("[%s] - ShouldBeEquals: ERRORE - i due contatti non sono uguali! (dovrebbero)", test_prefix);
    }

    tests[1].input_1.name = "Nome_1";
    tests[1].input_1.surname = "Cognome_1";
    tests[1].input_1.mobile = "1231421";
    tests[1].input_1.url = "http://esercizio.discutibile.com";

    tests[1].input_2.name = "nome_1";
    tests[1].input_2.surname = "cognome_1";
    tests[1].input_2.mobile = "1231421";
    tests[1].input_2.url = "http://esercizio.discutibile.com";
    tests[1].boolean_result = 1;
    int shoud_eq_case = contactEqEff(&(tests[1].input_1), &(tests[1].input_2));

    if(shoud_eq_case != tests[1].boolean_result){
        printf("[%s] - ShouldBeEquals (case sensitive): ERRORE - i due contatti NON sono uguali! (dovrebbero)\n",test_prefix);
    }

    tests[2].input_1.name = "nome_1";
    tests[2].input_1.surname = "cognome_1";
    tests[2].input_1.mobile = "1231421";
    tests[2].input_1.url = "http://esercizio.discutibile.com";

    tests[2].input_2.name = "DIFF_nome_1";
    tests[2].input_2.surname = "DIFF_cognome_1";
    tests[2].input_2.mobile = "1231421";
    tests[2].input_2.url = "http://esercizio.discutibile.com";
    tests[2].boolean_result = 0;
    int shoud_not_eq = contactEqEff(&(tests[1].input_1), &(tests[1].input_2));

    if(shoud_not_eq != tests[1].boolean_result){
        printf("[%s] - ShouldNOTBeEquals: ERRORE - i due contatti sono uguali! (non dovrebbero)\n",test_prefix);
    }
}

void test_contact_cmp(){
    test_item tests[3];
    char* test_prefix = "contactCmp";
    int result;

    // test 1: uguali (0)
    int test_counter = 0;
    tests[test_counter].input_1.name = "aaaaaaaa";
    tests[test_counter].input_1.surname = "aaaaaaa";
    tests[test_counter].input_1.mobile = "1231421";
    tests[test_counter].input_1.url = "http://esercizio.discutibile.com";

    tests[test_counter].input_2.name = "aaaaaaaa";
    tests[test_counter].input_2.surname = "aaaaaaa";
    tests[test_counter].input_2.mobile = "1231421";
    tests[test_counter].input_2.url = "http://esercizio.discutibile.com";

    tests[test_counter].integer_result = 0;
    result = contactCmp(tests[test_counter].input_1, tests[test_counter].input_2);

    if (result != tests[test_counter].integer_result){
        printf("[%s] - EQUALS: Got %d - %d Expected\n",test_prefix, result , tests[test_counter].integer_result);
    }

    // test 2: c1 < c2 (-1)
    test_counter = 1;
    tests[test_counter].input_1.name = "aaaaaaaa";
    tests[test_counter].input_1.surname = "aaaaaaa";
    tests[test_counter].input_1.mobile = "1231421";
    tests[test_counter].input_1.url = "http://esercizio.discutibile.com";

    tests[test_counter].input_2.name = "aaaaaaaa";
    tests[test_counter].input_2.surname = "bbbbbbbb";
    tests[test_counter].input_2.mobile = "1231421";
    tests[test_counter].input_2.url = "http://esercizio.discutibile.com";

    tests[test_counter].integer_result = -1;
    result = contactCmp(tests[test_counter].input_1, tests[test_counter].input_2);

    if (result != tests[test_counter].integer_result){
        printf("[%s] - LESS: Got %d - %d Expected\n",test_prefix, result , tests[test_counter].integer_result);
    }

    // test 3: c1 > c2 (1)
    test_counter = 2;
    tests[test_counter].input_1.name = "aaaaaaaa";
    tests[test_counter].input_1.surname = "bbbbb";
    tests[test_counter].input_1.mobile = "1231421";
    tests[test_counter].input_1.url = "http://esercizio.discutibile.com";

    tests[test_counter].input_2.name = "aaaaaaaa";
    tests[test_counter].input_2.surname = "aaaaaaaa";
    tests[test_counter].input_2.mobile = "1231421";
    tests[test_counter].input_2.url = "http://esercizio.discutibile.com";

    tests[test_counter].integer_result = 1;
    result = contactCmp(tests[test_counter].input_1, tests[test_counter].input_2);

    if (result != tests[test_counter].integer_result){
        printf("[%s] - GREATER: Got %d - %d Expected\n",test_prefix, result , tests[test_counter].integer_result);
    }
}

void test_contact_cmp_eff(){
    test_item tests[3];
    char* test_prefix = "contactCmpEff";
    int result;

    // test 1: uguali (0)
    int test_counter = 0;
    tests[test_counter].input_1.name = "aaaaaaaa";
    tests[test_counter].input_1.surname = "aaaaaaa";
    tests[test_counter].input_1.mobile = "1231421";
    tests[test_counter].input_1.url = "http://esercizio.discutibile.com";

    tests[test_counter].input_2.name = "aaaaaaaa";
    tests[test_counter].input_2.surname = "aaaaaaa";
    tests[test_counter].input_2.mobile = "1231421";
    tests[test_counter].input_2.url = "http://esercizio.discutibile.com";

    tests[test_counter].integer_result = 0;
    result = contactCmpEff(&(tests[test_counter].input_1), &(tests[test_counter].input_2));

    if (result != tests[test_counter].integer_result){
        printf("[%s] - EQUALS: Got %d - %d Expected\n",test_prefix, result , tests[test_counter].integer_result);
    }

    // test 2: c1 < c2 (-1)
    test_counter = 1;
    tests[test_counter].input_1.name = "aaaaaaaa";
    tests[test_counter].input_1.surname = "aaaaaaa";
    tests[test_counter].input_1.mobile = "1231421";
    tests[test_counter].input_1.url = "http://esercizio.discutibile.com";

    tests[test_counter].input_2.name = "aaaaaaaa";
    tests[test_counter].input_2.surname = "bbbbbbbb";
    tests[test_counter].input_2.mobile = "1231421";
    tests[test_counter].input_2.url = "http://esercizio.discutibile.com";

    tests[test_counter].integer_result = -1;
    result = contactCmpEff(&(tests[test_counter].input_1), &(tests[test_counter].input_2));

    if (result != tests[test_counter].integer_result){
        printf("[%s] - LESS: Got %d - %d Expected\n",test_prefix, result , tests[test_counter].integer_result);
    }

    // test 3: c1 > c2 (1)
    test_counter = 2;
    tests[test_counter].input_1.name = "aaaaaaaa";
    tests[test_counter].input_1.surname = "bbbbb";
    tests[test_counter].input_1.mobile = "1231421";
    tests[test_counter].input_1.url = "http://esercizio.discutibile.com";

    tests[test_counter].input_2.name = "aaaaaaaa";
    tests[test_counter].input_2.surname = "aaaaaaaa";
    tests[test_counter].input_2.mobile = "1231421";
    tests[test_counter].input_2.url = "http://esercizio.discutibile.com";

    tests[test_counter].integer_result = 1;
    result = contactCmpEff(&(tests[test_counter].input_1), &(tests[test_counter].input_2));

    if (result != tests[test_counter].integer_result){
        printf("[%s] - GREATER: Got %d - %d Expected\n",test_prefix, result , tests[test_counter].integer_result);
    }
}

int main(){
    test_contact_eq();
    test_contact_eff();
    test_contact_cmp();
    test_contact_cmp_eff();
    return 0;
}