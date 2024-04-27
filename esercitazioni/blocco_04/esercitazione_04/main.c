#include "./tests/mk_queue_tests.h"

int main(){
    mk_queue_run_tests();
    ds_queue_run_tests();
    size_tests();
    peek_tests();
    return 0;
}