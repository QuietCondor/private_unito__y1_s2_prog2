#include "mk_queue_tests.h"
#include "../src/char_queue.c"
#include <assert.h>

void mk_queue_should_ok_should_return(){
    char* fun_name = "mk_queue_should_ok_should_return";
    printf("\n\t\tBEGIN TEST [%s]\n",fun_name);
    CharQueueADT queue = mkQueue();
    assert(true == true); // se siamo qui, e' andato tutto bene

    printf("\t\tEND TEST [%s]",fun_name);
    free(queue);
}

void mk_queue_run_tests(){
    char* fun_name = "mk_queue_run_tests";
    printf("\n");
    printf("BEGIN [%s] Tests:\n", fun_name);

    mk_queue_should_ok_should_return();

    printf("END Tests [%s]", fun_name);
}