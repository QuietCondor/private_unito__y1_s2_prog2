#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../features/intSortedSetADT.h"
#include "../features/intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSetv(int count, ...) {
    IntSortedSetADT set = mkSSet();

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        sset_add(set,num);        
    }
    va_end(args);
    return set;
}

char *toString(IntSortedSetADT set) {
    char *sout = malloc(100*sizeof(char));

    ListNodePtr nptr = set->first;
    sprintf(sout, "{");
    while (nptr) {
        if (nptr == set->first)
            sprintf(sout+strlen(sout), "%d", nptr->elem);
        else
            sprintf(sout+strlen(sout), ",%d", nptr->elem);
        nptr = nptr->next;
    }

    sprintf(sout+strlen(sout), "}");

    return sout;
}

int check_mkSSet() {
    int passed = 1;
    printf("mkSSet()\n");    
    IntSortedSetADT sptr = mkSSet();
    if (!sptr) {
        printf("FAILED");
        printf("EXPECTED: not %d\n", 0);   
    } else
        printf("OK\n");
    printf("RESULT:%ld\n\n", (long)sptr);  
    return passed;
}

int check_dsSSet() {
    int passed = 1;

    if (passed) {
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();
        printf("dsSSet({})\n");    
        rv = dsSSet(&sptr);
        if (!rv || sptr) {
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND PTR %ld\n", 0, (long)NULL); 
            passed=0;  
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d AND PTR %ld\n\n", rv, (long)sptr);
    }  

    if (passed) {
        _Bool rv;
        printf("dsSSet(NULL)\n");    
        rv = dsSSet(NULL);
        if (rv) {
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            passed=0;   
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d\n\n", rv);
    }

    return passed;
}

int check_sset_add() {
    int passed=1;

    if (passed) { // set vuoto
        _Bool rv;
        IntSortedSetADT set = mkSSet();
        printf("sset_add({}, 1)\n");
        bool local_result = sset_add(set, 1); 
        char* set_stringhed = toString(set);
        if (!local_result || set->first == NULL || set->first->elem != 1) {
            printf("FAILED\n");
            printf("EXPECTED: set != {} BUT FOUND = %s\n", toString(set)); 
            passed=0;  
        } else if(set->last == NULL || set->last->elem != 1){
            printf("FAILED\n");
            printf("EXPECTED: set->last == 1 BUT FOUND = %d\n", set->last->elem); 
        } else {
            printf("OK: %s\n", set_stringhed);
        }
        rv = dsSSet(&set);
    }

    if (passed) { // set con elemento gia' presente
        IntSortedSetADT set = mkSSet();
        printf("sset_add({1}, 1)\n");
        sset_add(set, 1); 
        bool local_result = sset_add(set, 1); 

        char* set_stringhed = toString(set);
        if (local_result || set->first == NULL || set->first->next != NULL || set->last == NULL) {
            printf("FAILED\n");
            printf("EXPECTED: set != {1} with FALSE BUT FOUND = %s with TRUE\n", toString(set)); 
            passed=0;  
        } else if(set->last == NULL || set->last->elem != 1){
            printf("FAILED\n");
            printf("EXPECTED: set->last == 1 BUT FOUND = %d\n", set->last->elem); 
        } else {
            printf("OK: %s\n", set_stringhed);
        }
        dsSSet(&set);
    }

    if (passed) { // inserimento alla fine
        IntSortedSetADT set = mkSSet();
        printf("sset_add({1}, 2)\n");
        sset_add(set, 1); 
        bool local_result = sset_add(set, 2); 

        char* set_stringhed = toString(set);
        if (!local_result || set->first == NULL || set->first->next == NULL) {
            printf("FAILED\n");
            printf("EXPECTED: set == {1, 2} with TRUE BUT FOUND = %s with FALSE\n", toString(set)); 
            passed=0;  
        } else if(set->last == NULL || set->last->elem != 2){
            printf("FAILED\n");
            printf("EXPECTED: set == {1, 2} with set->last == 2 BUT FOUND = %d\n", set->last->elem); 
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
        dsSSet(&set);
    }

    if (passed) { // inserimento all'inizio fine
        IntSortedSetADT set = mkSSet();
        printf("sset_add({2}, 1)\n");
        sset_add(set, 2); 
        bool local_result = sset_add(set, 1); 

        char* set_stringhed = toString(set);
        if (!local_result || set->first == NULL || set->first->elem != 1 || set->first->next == NULL) {
            printf("FAILED\n");
            printf("EXPECTED: set == {1, 2} with TRUE BUT FOUND = %s with FALSE\n", toString(set)); 
            passed=0;  
        } else if(set->last == NULL || set->last->elem != 2){
            printf("FAILED\n");
            printf("EXPECTED: set == {1, 2} with set->last == 2 BUT FOUND = %d\n", set->last->elem); 
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
        dsSSet(&set);
    }

    if (passed) { // inserimento in mezzo
        IntSortedSetADT set = mkSSet();
        printf("sset_add({1,3}, 2)\n");
        sset_add(set, 1); 
        sset_add(set, 3);
        bool local_result = sset_add(set, 2); 

        char* set_stringhed = toString(set);

        bool isFirstWrong = set->first == NULL || set->first->elem != 1;
        bool isSecondWrong = set->first->next == NULL || set->first->next->elem != 2;
        bool isThirdWrong = set->first->next->next == NULL || set->first->next->next->elem != 3;

        if(!local_result || isFirstWrong || isSecondWrong || isThirdWrong){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if (!isFirstWrong){
                printf("\tHINT: The first item is wrong\n");
            }
            if (!isSecondWrong){
                printf("\tHINT: The second item is wrong\n");
            }
            if (!isThirdWrong){
                printf("\tHINT: The third item is wrong\n");
            }
            printf("EXPECTED: set == {1, 2, 3} with TRUE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }

        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
        dsSSet(&set);
    }

    if (passed) { // inserimento in mezzo
        printf("sset_add(NULL, 1)\n");
        bool local_result = sset_add(NULL, 1); 

        if(local_result){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            printf("EXPECTED: set == NULL with FALSE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }

        printf("SET RESULT: \n\tset: NULL\n\tfunction result: %d\n", local_result);
    }

    return passed;
}

int check_sset_remove(){
    int passed=1;

    // testare:
    // - NULL => false
    if(passed){
        IntSortedSetADT set = NULL;
        printf("sset_remove(NULL, 1)\n");
        bool local_result = sset_remove(set, 1); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        if(local_result || set != NULL){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if(set != NULL){
                printf("\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            printf("EXPECTED: set == NULL with FALSE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
    }

    // - {} => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_remove({}, 1)\n");
        bool local_result = sset_remove(set, 1); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        if(local_result || set == NULL){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if(set == NULL){
                printf("\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            printf("EXPECTED: set == {} with FALSE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
    }
    // - elemento non esistente => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1); 
        printf("sset_remove({1}, 2)\n");
        bool local_result = sset_remove(set, 2); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL || set->first == NULL || set->first->elem != 1;
        if(local_result || set_is_wrong){
            printf("FAILED\n");
            if (local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            printf("EXPECTED: set == {1} with FALSE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
    }
    // - Rimozione all'inizio => true
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1); 
        sset_add(set, 2); 
        sset_add(set, 3); 
        printf("sset_remove({1,2,3}, 1)\n");
        bool local_result = sset_remove(set, 1); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL 
            || set->first == NULL 
            || set->first->elem != 2
            || set->first->next == NULL || set->first->next->elem != 3
            || set->last == NULL || set->last->elem != 3;
        if(!local_result || set_is_wrong){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            printf("EXPECTED: set == {2,3} with TRUE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
    }
    // - Rimozione in mezzo => true
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1); 
        sset_add(set, 2); 
        sset_add(set, 3); 
        printf("sset_remove({1,2,3}, 2)\n");
        bool local_result = sset_remove(set, 2); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL 
            || set->first == NULL 
            || set->first->elem != 1
            || set->first->next == NULL || set->first->next->elem != 3
            || set->last == NULL || set->last->elem != 3;
        if(!local_result || set_is_wrong){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            printf("EXPECTED: set == {1,3} with TRUE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
    }
    // - Rimozione alla fine => true
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1); 
        sset_add(set, 2); 
        sset_add(set, 3); 
        printf("sset_remove({1,2,3}, 3)\n");
        bool local_result = sset_remove(set, 3); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL 
            || set->first == NULL 
            || set->first->elem != 1
            || set->first->next == NULL || set->first->next->elem != 2
            || set->last == NULL || set->last->elem != 2;
        if(!local_result || set_is_wrong){
            printf("FAILED\n");
            if (!local_result){
                printf("\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            printf("EXPECTED: set == {1,2} with TRUE\n"); 
            passed = 0;
        } else {
            printf("OK:\n");
        }
        printf("SET RESULT: \n\tset:%s\n\tfunction result: %d\n", set_stringhed, local_result);
    }

    return passed;
}

int check_sset_member(){
    int passed=1;
    
    // casi da testare:
    // - NULL => false
    if(passed){
        IntSortedSetADT set = NULL;
        printf("sset_member(NULL, 3)\n");
        bool local_result = sset_member(set, 3); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set != NULL;
        bool result_is_wrong = local_result == true;

        printf("\tEXPECTED: set == NULL with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(result_is_wrong || set_is_wrong){
            printf("\t\tFAILED:\n");
            if (result_is_wrong){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\t\t\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }
    }
    // - {} => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_member({}, 3)\n");
        bool local_result = sset_member(set, 3); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL
            || set->first != NULL
            ;
        bool result_is_wrong = local_result == true;

        printf("\tEXPECTED: set == {} with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(result_is_wrong || set_is_wrong){
            printf("\t\tFAILED:\n");
            if (result_is_wrong){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\t\t\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }
    }
    // - elemento non esiste => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        printf("sset_member({1}, 3)\n");
        bool local_result = sset_member(set, 3); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL
            || set->first == NULL
            || set->first->elem != 1
            || set->last == NULL
            || set->last->elem != 1
            ;
        bool result_is_wrong = local_result != false;

        printf("\tEXPECTED: set == {1} with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(result_is_wrong || set_is_wrong){
            printf("\t\tFAILED:\n");
            if (result_is_wrong){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\t\t\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }
    }
    // - elemento esiste => true
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        printf("sset_member({1}, 1)\n");
        bool local_result = sset_member(set, 1); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_wrong = set == NULL
            || set->first == NULL
            || set->first->elem != 1
            || set->last == NULL
            || set->last->elem != 1
            ;
        bool result_is_wrong = local_result != true;

        printf("\tEXPECTED: set == {1} with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(result_is_wrong || set_is_wrong){
            printf("\t\tFAILED:\n");
            if (result_is_wrong){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(set_is_wrong){
                printf("\t\t\tHINT: The set is wrong\n");
                dsSSet(&set);
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }
    }

    return passed;  
}

int check_isEmptySSet(){
    int passed=1;

    // casi da testare:
    // - NULL => true

    if(passed){
        IntSortedSetADT set = NULL;
        printf("isEmptySSet(NULL)\n");
        bool local_result = isEmptySSet(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set == NULL
            ;
        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set == NULL with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // - {} => true
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("isEmptySSet({})\n");
        bool local_result = isEmptySSet(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first == NULL
            && set->last == NULL
            ;
        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set == {} with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }

    // - {1} => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        printf("isEmptySSet({1})\n");
        bool local_result = isEmptySSet(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->last != NULL && set->last->elem == 1
            ;
        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set == {1} with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // - {1,2} => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        sset_add(set, 2);
        printf("isEmptySSet({1,2})\n");
        bool local_result = isEmptySSet(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->last != NULL && set->last->elem == 2
            ;
        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set == {1,2} with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // - {1,2,3} => false
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        sset_add(set, 2);
        sset_add(set, 3);
        printf("isEmptySSet({1,2,3})\n");
        bool local_result = isEmptySSet(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->first->next != NULL && set->first->next->elem == 2
            && set->last != NULL && set->last->elem == 3
            ;
        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set == {1,2,3} with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }

    return passed;
}

int check_sset_size(){
    int passed=1;

    // casi da testare:
    // NULL     => -1
    if(passed){
        IntSortedSetADT set = NULL;
        printf("sset_size(NULL)\n");
        int local_result = sset_size(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set == NULL
            ;
        bool result_is_good = local_result == -1;

        printf("\tEXPECTED: set == NULL with -1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // {}       => 0
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_size({})\n");
        int local_result = sset_size(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first == NULL
            && set->last == NULL
            ;
        bool result_is_good = local_result == 0;

        printf("\tEXPECTED: set == {} with 0\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // {1}      => 1
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        printf("sset_size({1})\n");
        int local_result = sset_size(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->last != NULL && set->last->elem == 1
            ;
        bool result_is_good = local_result == 1;

        printf("\tEXPECTED: set == {1} with 1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // {1,2}    => 2
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        sset_add(set, 2);
        printf("sset_size({1,2})\n");
        int local_result = sset_size(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->last != NULL && set->last->elem == 2
            ;
        bool result_is_good = local_result == 2;

        printf("\tEXPECTED: set == {1,2} with 2\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // {1,2,3}  => 3
    if(passed){
        IntSortedSetADT set = mkSSet();
        sset_add(set, 1);
        sset_add(set, 2);
        sset_add(set, 3);
        printf("sset_size({1,2,3})\n");
        int local_result = sset_size(set); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->first->next != NULL && set->first->next->elem == 2
            && set->last != NULL && set->last->elem == 3
            ;
        bool result_is_good = local_result == 3;

        printf("\tEXPECTED: set == {1,2,3} with 3\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }


    return passed;
}


int check_sset_extract(){
    int passed=1;
    
    // casi da testare:
    // - NULL => FALSE con *int a -1
    if(passed){
        IntSortedSetADT set = NULL;
        printf("sset_extract(NULL, &(-1))\n");
        int extr_result = -1;
        bool local_result = sset_extract(set, &extr_result); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set == NULL
            ;
        bool result_is_good = local_result == false && extr_result == -1;

        printf("\tEXPECTED: set == NULL with FALSE, -1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // - {}   => FALSE con *int a -1
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_extract({}, &(-1))\n");
        int extr_result = -1;
        bool local_result = sset_extract(set, &extr_result); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first == NULL
            && set->last == NULL
            ;
        bool result_is_good = local_result == false && extr_result == -1;

        printf("\tEXPECTED: set == {} with FALSE, -1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // - {1}, -1 => TRUE con *int a 1
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_extract({1}, &(-1))\n");
        sset_add(set,1);
        int extr_result = -1;
        bool local_result = sset_extract(set, &extr_result); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            ;
        bool result_is_good = local_result == true && extr_result == 1;

        printf("\tEXPECTED: set == {1} with TRUE, 1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    // - {1,2}, -1 => TRUE con *int a 1
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_extract({1,2}, &(-1))\n");
        sset_add(set,1);
        sset_add(set,2);
        int extr_result = -1;
        bool local_result = sset_extract(set, &extr_result); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->last != NULL && set->last->elem == 2
            ;
        bool result_is_good = local_result == true && extr_result == 1;

        printf("\tEXPECTED: set == {1,2} with TRUE, 1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }
    

    // - {1,2,3}, 3 => TRUE con *int a 3
    if(passed){
        IntSortedSetADT set = mkSSet();
        printf("sset_extract({1,2,3}, &(-1))\n");
        sset_add(set,1);
        sset_add(set,2);
        sset_add(set,3);
        int extr_result = -1;
        bool local_result = sset_extract(set, &extr_result); 

        char* set_stringhed = set != NULL ? toString(set) : "NULL";
        bool set_is_good = set != NULL
            && set->first != NULL && set->first->elem == 1
            && set->first->next != NULL && set->first->next->elem == 2
            && set->last != NULL && set->last->elem == 3
            ;
        bool result_is_good = local_result == true && extr_result == 1;

        printf("\tEXPECTED: set == {1,2,3} with TRUE, 1\n"); 
        printf("\tSET RESULT: \n\t\tset:%s\n\t\tfunction result: %d\n", set_stringhed, local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: The set is wrong\n");

                
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set != NULL){
            dsSSet(&set);
        }
    }


    return passed;
}

int check_sset_equals(){
    int passed=1;

    // casi da testare:
    // NULL, NULL => true
    if(passed){
        IntSortedSetADT set_first = NULL;
        IntSortedSetADT set_second = NULL;
        printf("sset_equals(NULL, NULL)\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first == NULL
            ;
        bool set_second_is_good = set_second == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == NULL, set_second == NULL with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {}, {} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        IntSortedSetADT set_second = mkSSet();
        printf("sset_equals({}, {})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first == NULL
            && set_first->last == NULL
            ;
        bool set_second_is_good = set_second != NULL
            && set_first->first == NULL
            && set_first->last == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {}, set_second == {} with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {}, NULL => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        IntSortedSetADT set_second = NULL;
        printf("sset_equals({}, NULL)\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first == NULL
            && set_first->last == NULL
            ;
        bool set_second_is_good = set_second == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {}, set_second == NULL with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // NULL, {} => false
    if(passed){
        IntSortedSetADT set_first = NULL;
        IntSortedSetADT set_second = mkSSet();
        printf("sset_equals(NULL, {})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first == NULL
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first == NULL
            && set_second->last == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == NULL, set_second == {} with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {1,2,3}, NULL => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = NULL;
        printf("sset_equals({1,2,3}, NULL)\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == NULL with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // NULL, {1,2,3} => false
    if(passed){
        IntSortedSetADT set_first = NULL;
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_equals(NULL, {1,2,3})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first == NULL
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
        
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == NULL, set_second == {1,2,3}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {}, {1,2,3} => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_equals({}, {1,2,3})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first == NULL
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {}, set_second == {1,2,3}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {1,2,3}, {} => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = mkSSet();
        printf("sset_equals({1,2,3}, {})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first == NULL 
            && set_second->last == NULL 
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == {}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {1,2,3}, {1} => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        printf("sset_equals({1,2,3}, {1})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->last != NULL && set_second->last->elem == 1
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == {1}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {1,2,3}, {1,2} => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        printf("sset_equals({1,2,3}, {1,2})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->last != NULL && set_second->last->elem == 2
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == {1,2}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // {1,2,3}, {1,2,3} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_equals({1,2,3}, {1,2,3})\n");
        bool local_result = sset_equals(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == {1,2,3}  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }

    return passed;
}

int check_sset_subseteq(){
    int passed=1;

    // casi da testare:
    // - NULL, NULL => true
    if(passed){
        IntSortedSetADT set_first = NULL;
        IntSortedSetADT set_second = NULL;
        printf("sset_subseteq(NULL, NULL)\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first == NULL
            ;
        bool set_second_is_good = set_second == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == NULL, set_second == NULL  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {}, {} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        
        IntSortedSetADT set_second = mkSSet();
        
        printf("sset_subseteq({}, {})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first == NULL 
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first == NULL 
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {}, set_second == {}  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {}, NULL => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        IntSortedSetADT set_second = NULL;
        printf("sset_subseteq({}, NULL)\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first == NULL 
            ;
        bool set_second_is_good = set_second == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {}, set_second == NULL  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - NULL, {} => false
    if(passed){
        IntSortedSetADT set_first = NULL;
        IntSortedSetADT set_second = mkSSet();
        printf("sset_subseteq(NULL, {})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first == NULL
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first == NULL 
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == NULL, set_second == {}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {1,2,3}, NULL => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = NULL;
        printf("sset_subseteq({1,2,3}, NULL)\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == NULL  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - NULL, {1,2,3} => false
    if(passed){
        IntSortedSetADT set_first = NULL;
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_subseteq(NULL, {1,2,3})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first == NULL
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == NULL, set_second == {1,2,3}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {1,2,3}, {} => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = mkSSet();
        printf("sset_subseteq({1,2,3}, {})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first == NULL
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == {}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {}, {1,2,3} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_subseteq({}, {1,2,3})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first == NULL 
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {}, set_second == {1,2,3}  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {1}, {1,2,3} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_subseteq({1}, {1,2,3})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->last != NULL && set_first->last->elem == 1
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {1}, set_second == {1,2,3}  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {1,2}, {1,2,3} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_subseteq({1,2}, {1,2,3})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->last != NULL && set_first->last->elem == 2
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {1,2}, set_second == {1,2,3}  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {1,2,3}, {1,2,3} => true
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_subseteq({1,2,3}, {1,2,3})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->last != NULL && set_first->last->elem == 3
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == true;

        printf("\tEXPECTED: set_first == {1,2,3}, set_second == {1,2,3}  with TRUE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }
    // - {1,2,3,4}, {1,2,3} => false
    if(passed){
        IntSortedSetADT set_first = mkSSet();
        sset_add(set_first, 1);
        sset_add(set_first, 2);
        sset_add(set_first, 3);
        sset_add(set_first, 4);
        IntSortedSetADT set_second = mkSSet();
        sset_add(set_second, 1);
        sset_add(set_second, 2);
        sset_add(set_second, 3);
        printf("sset_subseteq({1,2,3,4}, {1,2,3})\n");
        bool local_result = sset_subseteq(set_first, set_second); 

        char* set_stringhed_first = set_first != NULL ? toString(set_first) : "NULL";
        char* set_stringhed_second = set_second != NULL ? toString(set_second) : "NULL";

        bool set_first_is_good = set_first != NULL
            && set_first->first != NULL && set_first->first->elem == 1
            && set_first->first->next != NULL && set_first->first->next->elem == 2
            && set_first->first->next->next != NULL && set_first->first->next->next->elem == 3
            && set_first->last != NULL && set_first->last->elem == 4
            ;
        bool set_second_is_good = set_second != NULL
            && set_second->first != NULL && set_second->first->elem == 1
            && set_second->first->next != NULL && set_second->first->next->elem == 2
            && set_second->last != NULL && set_second->last->elem == 3
            ;
        
        bool set_is_good = set_first_is_good && set_first_is_good;

        bool result_is_good = local_result == false;

        printf("\tEXPECTED: set_first == {1,2,3,4}, set_second == {1,2,3}  with FALSE\n"); 
        printf("\tSET RESULT: \n\t\tset_first:%s\n\t\tset_second:%s\n\t\tfunction result: %d\n", 
            set_stringhed_first,
            set_stringhed_second,
            local_result);
        printf("\tRESULT:\n");
        if(!result_is_good || !set_is_good){
            printf("\t\tFAILED:\n");
            if (!result_is_good){
                printf("\t\t\tHINT: The result is wrong\n");
            }
            if(!set_is_good){
                printf("\t\t\tHINT: One of the sets are wrong\n");
            }
            passed = 0;
        } else {
            printf("\t\tOK.\n");
        }

        if(set_first != NULL){
            dsSSet(&set_first);
        }

        if(set_second != NULL){
            dsSSet(&set_second);
        }
    }

    return passed;
}

int check_sset_subset() {
    int passed=1;

    return passed;
}


int check_sset_union() {
    int passed=1;

    return passed;
}

int check_sset_intersection() {
    int passed=1;

    return passed;
}

int check_sset_subtraction() {
    int passed=1;

    return passed;
}

int check_sset_min(){
    int passed=1;

    return passed;
}

int check_sset_max(){
    int passed=1;

    return passed;
}

int check_sset_extractMin(){
    int passed=1;

    return passed;
}

int check_sset_extractMax(){
    int passed=1;

    return passed;
}

int main(int argc, char *argv[]) {
  puts("BEGIN TEST intLinkedListSortedSetADT"); 

  {
    printf("TEST mkSSet\n");
    check_mkSSet();
    printf("\n");
  }

  {
    printf("TEST dsSSet\n");
    check_dsSSet();
    printf("\n");
  }

  {
    printf("TEST sset_add\n");
    check_sset_add();
    printf("\n");
  }

  {
    printf("TEST sset_remove\n");    
    check_sset_remove();
    printf("\n");
  }

  {
    printf("TEST sset_member\n");    
    check_sset_member();
    printf("\n");
  }

  {
    printf("TEST isEmptySSet\n");    
    check_isEmptySSet();
    printf("\n");
  }

  {
    printf("TEST sset_size\n");    
    check_sset_size();
    printf("\n");
  }

  {
    printf("TEST sset_extract\n");    
    check_sset_extract();
    printf("\n");
  }

  {
    printf("TEST sset_equals\n");    
    check_sset_equals();
    printf("\n");
  }

  {
    printf("TEST sset_subseteq\n");    
    check_sset_subseteq();
    printf("\n");
  }

  {
    printf("TEST sset_subset\n");    
    check_sset_subset();
    printf("\n");
  }

  {
    printf("TEST sset_union\n");    
    check_sset_union();
    printf("\n");
  }

  {
    printf("TEST sset_intersection\n");    
    check_sset_intersection();
    printf("\n");
  }

  {
    printf("TEST sset_subtraction\n");    
    check_sset_subtraction();
    printf("\n");
  }

  {
    printf("TEST sset_min\n");    
    check_sset_min();
    printf("\n");
  }

  {
    printf("TEST sset_max\n");    
    check_sset_max();
    printf("\n");
  }

  {
    printf("TEST sset_extractMin\n");    
    check_sset_extractMin();
    printf("\n");
  }

  {
    //printf("TEST sset_extractMax\n");    
    //check_sset_extractMax();
    //printf("\n");
  }
}