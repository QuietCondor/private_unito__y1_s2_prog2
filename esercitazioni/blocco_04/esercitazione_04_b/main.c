#include <stdio.h>
#include <stdlib.h>
#include "./test/char_queue_tests.h"

int main(){

    test_mk_queue();
    test_ds_queue();
    test_is_empty();
    test_size();
    test_peek();
    test_enqueue();
    test_dequeue();

    return 0;
}