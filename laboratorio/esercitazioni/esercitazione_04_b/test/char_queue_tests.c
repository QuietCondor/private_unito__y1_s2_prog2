#include "../features/charQueueADT.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void test_mk_queue_should_return_ok(){
    char* method_name = "mk_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();

    assert(queue != NULL);

    free(queue);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_mk_queue(){
    char* method_name = "mk_queue";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);
    
    test_mk_queue_should_return_ok();
    
    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}

void test_ds_queue_should_return_ok(){
    char* method_name = "ds_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_ds_queue(){
    char* method_name = "ds_queue";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);

    test_ds_queue_should_return_ok();

    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}

void test_enqueue_null_queue_should_return_ok(){
    char* method_name = "enqueue_null_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    int result = enqueue(NULL, 'q');

    assert(result == 0);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_enqueue_first_should_return_ok(){
    char* method_name = "enqueue_first_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');

    char char_result = '_';
    int result = peek(queue, 0, &char_result);    

    assert(result == 1);
    assert(char_result == 'A');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_enqueue_n_elements_should_return_ok(){
    char* method_name = "enqueue_n_elements_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    enqueue(queue, 'D');

    char char_result_1 = '_';
    int result_1 = peek(queue, 0, &char_result_1);    
    assert(result_1 == 1);
    assert(char_result_1 == 'A');

    char char_result_2 = '_';
    int result_2 = peek(queue, 1, &char_result_2);    
    assert(result_2 == 1);
    assert(char_result_2 == 'B');

    char char_result_3 = '_';
    int result_3 = peek(queue, 2, &char_result_3);    
    assert(result_3 == 1);
    assert(char_result_3 == 'C');

    char char_result_4 = '_';
    int result_4 = peek(queue, 3, &char_result_4);    
    assert(result_4 == 1);
    assert(char_result_4 == 'D');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_enqueue(){
    char* method_name = "enqueue";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);

    test_enqueue_null_queue_should_return_ok();
    test_enqueue_first_should_return_ok();
    test_enqueue_n_elements_should_return_ok();

    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}

void test_dequeue_null_queue_should_return_ok(){
    char* method_name = "dequeue_null_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    char char_result = '_';
    int result = dequeue(NULL, &char_result);

    assert(result == 0);
    assert(char_result == '_');

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_dequeue_empty_queue_should_return_ok(){
    char* method_name = "dequeue_empty_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();

    char char_result = '_';
    int result = dequeue(queue, &char_result);    

    assert(result == 0);
    assert(char_result == '_');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_dequeue_one_element_queue_should_return_ok(){
    char* method_name = "dequeue_one_element_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');

    char char_result = '_';
    int result = dequeue(queue, &char_result);    

    assert(result == 1);
    assert(char_result == 'A');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_dequeue_one_element_then_none_queue_should_return_ok(){
    char* method_name = "dequeue_one_element_then_none_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');

    char char_result_1 = '_';
    int result_1 = dequeue(queue, &char_result_1);    
    assert(result_1 == 1);
    assert(char_result_1 == 'A');

    char char_result_2 = '_';
    int result_2 = dequeue(queue, &char_result_2);    
    assert(result_2 == 0);
    assert(char_result_2 == '_');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_dequeue_n_elemets_should_return_ok(){
    char* method_name = "dequeue_n_elemets_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    enqueue(queue, 'D');
    enqueue(queue, 'E');
    enqueue(queue, 'F');
    enqueue(queue, 'G');
    enqueue(queue, 'H');
    enqueue(queue, 'I');
    enqueue(queue, 'J');
    enqueue(queue, 'K');
    enqueue(queue, 'L');

    char char_result_1 = '_';
    int result_1 = dequeue(queue, &char_result_1);    
    assert(result_1 == 1);
    assert(char_result_1 == 'A');

    char char_result_2 = '_';
    int result_2 = dequeue(queue, &char_result_2);    
    assert(result_2 == 1);
    assert(char_result_2 == 'B');

    char char_result_3 = '_';
    int result_3 = dequeue(queue, &char_result_3);    
    assert(result_3 == 1);
    assert(char_result_3 == 'C');

    char char_result_4 = '_';
    int result_4 = dequeue(queue, &char_result_4);    
    assert(result_4 == 1);
    assert(char_result_4 == 'D');

    char char_result_5 = '_';
    int result_5 = dequeue(queue, &char_result_5);    
    assert(result_5 == 1);
    assert(char_result_5 == 'E');

    char char_result_6 = '_';
    int result_6 = dequeue(queue, &char_result_6);    
    assert(result_6 == 1);
    assert(char_result_6 == 'F');

    char char_result_7 = '_';
    int result_7 = dequeue(queue, &char_result_7);    
    assert(result_7 == 1);
    assert(char_result_7 == 'G');

    char char_result_8 = '_';
    int result_8 = dequeue(queue, &char_result_8);    
    assert(result_8 == 1);
    assert(char_result_8 == 'H');

    char char_result_9 = '_';
    int result_9 = dequeue(queue, &char_result_9);    
    assert(result_9 == 1);
    assert(char_result_9 == 'I');

    char char_result_10 = '_';
    int result_10 = dequeue(queue, &char_result_10);    
    assert(result_10 == 1);
    assert(char_result_10 == 'J');

    char char_result_11 = '_';
    int result_11 = dequeue(queue, &char_result_11);    
    assert(result_11 == 1);
    assert(char_result_11 == 'K');

    char char_result_12 = '_';
    int result_12 = dequeue(queue, &char_result_12);    
    assert(result_12 == 1);
    assert(char_result_12 == 'L');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_dequeue(){
    char* method_name = "dequeue";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);

    test_dequeue_null_queue_should_return_ok();
    test_dequeue_empty_queue_should_return_ok();
    test_dequeue_one_element_queue_should_return_ok();
    test_dequeue_one_element_then_none_queue_should_return_ok();
    test_dequeue_n_elemets_should_return_ok();

    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}

void test_is_empty_null_queue_should_return_ok(){
    char* method_name = "is_empty_null_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    isEmpty(NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_is_empty_empty_queue_should_return_ok(){
    char* method_name = "is_empty_empty_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();

    int result = isEmpty(queue);

    assert(result == 1);

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_is_empty(){
    char* method_name = "is_empty";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);

    test_is_empty_empty_queue_should_return_ok();
    test_is_empty_null_queue_should_return_ok();

    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}

void test_size_null_queue_should_return_ok(){
    char* method_name = "size_null_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    size(NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_size_empty_queue_should_return_ok(){
    char* method_name = "size_empty_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();

    int result = size(queue);

    assert(result == 0);

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_size(){
    char* method_name = "size";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);

    test_size_null_queue_should_return_ok();
    test_size_empty_queue_should_return_ok();

    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}

void test_peek_null_queue_should_return_ok(){
    char* method_name = "peek_null_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    char char_result = '_';
    int result = peek(NULL, 0, &char_result);

    assert(result == 0);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_peek_empty_queue_should_return_ok(){
    char* method_name = "peek_empty_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();

    char char_result = '_';
    int result = peek(queue, 0, &char_result);

    assert(result == 0);

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_peek_1_element_queue_should_return_ok(){
    char* method_name = "peek_1_element_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');

    char char_result = '_';
    int result = peek(queue, 0, &char_result);

    assert(result == 1);
    assert(char_result == 'A');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_peek_n_element_queue_should_return_ok(){
    char* method_name = "peek_n_element_queue_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    enqueue(queue, 'D');
    enqueue(queue, 'E');
    enqueue(queue, 'F');
    enqueue(queue, 'G');
    enqueue(queue, 'H');

    char char_result_1 = '_';
    int result_1 = peek(queue, 0, &char_result_1);
    assert(result_1 == 1);
    assert(char_result_1 == 'A');

    char char_result_2 = '_';
    int result_2 = peek(queue, 1, &char_result_2);
    assert(result_2 == 1);
    assert(char_result_2 == 'B');

    char char_result_3 = '_';
    int result_3 = peek(queue, 2, &char_result_3);
    assert(result_3 == 1);
    assert(char_result_3 == 'C');

    char char_result_4 = '_';
    int result_4 = peek(queue, 3, &char_result_4);
    assert(result_4 == 1);
    assert(char_result_4 == 'D');

    char char_result_5 = '_';
    int result_5 = peek(queue, 4, &char_result_5);
    assert(result_5 == 1);
    assert(char_result_5 == 'E');

    char char_result_6 = '_';
    int result_6 = peek(queue, 5, &char_result_6);
    assert(result_6 == 1);
    assert(char_result_6 == 'F');

    char char_result_7 = '_';
    int result_7 = peek(queue, 6, &char_result_7);
    assert(result_7 == 1);
    assert(char_result_7 == 'G');

    char char_result_8 = '_';
    int result_8 = peek(queue, 7, &char_result_8);
    assert(result_8 == 1);
    assert(char_result_8 == 'H');

    char dequeue_char_result_1 = '_';
    int dequeue_result_1 = dequeue(queue, &dequeue_char_result_1);    
    assert(dequeue_result_1 == 1);
    assert(dequeue_char_result_1 == 'A');

    char dequeue_char_result_2 = '_';
    int dequeue_result_2 = dequeue(queue, &dequeue_char_result_2);    
    assert(dequeue_result_2 == 1);
    assert(dequeue_char_result_2 == 'B');

    char dequeue_char_result_3 = '_';
    int dequeue_result_3 = dequeue(queue, &dequeue_char_result_3);    
    assert(dequeue_result_3 == 1);
    assert(dequeue_char_result_3 == 'C');

    char dequeue_char_result_4 = '_';
    int dequeue_result_4 = dequeue(queue, &dequeue_char_result_4);    
    assert(dequeue_result_4 == 1);
    assert(dequeue_char_result_4 == 'D');

    char after_char_result_1 = '_';
    int after_result_1 = peek(queue, 0, &after_char_result_1);
    assert(after_result_1 == 1);
    assert(after_char_result_1 == 'E');

    char after_char_result_2 = '_';
    int after_result_2 = peek(queue, 1, &after_char_result_2);
    assert(after_result_2 == 1);
    assert(after_char_result_2 == 'F');

    char after_char_result_3 = '_';
    int after_result_3 = peek(queue, 2, &after_char_result_3);
    assert(after_result_3 == 1);
    assert(after_char_result_3 == 'G');

    dsQueue(&queue);
    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_peek_out_of_bounds_should_return_ok(){
    char* method_name = "peek_out_of_bounds_should_return_ok";

    printf("\tBEGIN TEST: %s\n", method_name);

    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');

    char char_result = '_';
    int result = peek(queue, 2, &char_result);

    assert(result == 0);
    assert(char_result == '_');

    dsQueue(&queue);

    assert(queue == NULL);

    printf("\n\tEND TEST  : %s\n", method_name);
}

void test_peek(){
    char* method_name = "peek";

    printf("\n----------------------------------\n");
    printf("BEGIN - Tests for %s\n", method_name);

    test_peek_empty_queue_should_return_ok();
    test_peek_null_queue_should_return_ok();
    test_peek_1_element_queue_should_return_ok();
    test_peek_out_of_bounds_should_return_ok();
    test_peek_n_element_queue_should_return_ok();

    printf("\nEND - Tests for %s\n", method_name);
    printf("\n----------------------------------\n");
}
