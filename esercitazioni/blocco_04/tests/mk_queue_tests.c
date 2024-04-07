#include "mk_queue_tests.h"
#include "../src/char_queue_adt.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void mk_queue_should_ok_should_return(){
    char* fun_name = "mk_queue_should_ok_should_return";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    CharQueueADT queue = mkQueue();
    assert(true == true); // se siamo qui, e' andato tutto bene

    printf("\t\tEND TEST \t[%s]",fun_name);
    free(queue);
}

void ds_queue_null_pointier_should_return_ok(){
    char* fun_name = "ds_queue_null_pointier_should_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    dsQueue(NULL);

    assert(true == true); // se siamo arrivati qui va tutto bene
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void ds_queue_empty_queue_should_return_ok(){
    char* fun_name = "ds_queue_empty_queue_should_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT* empty_pointier = NULL;
    dsQueue(empty_pointier);

    assert(true == true); // se siamo arrivati qui va tutto bene
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void ds_queue_not_empty_should_return_ok(){
    char* fun_name = "ds_queue_not_empty_should_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    dsQueue(&queue);

    assert(queue == NULL); // dovrebbe aver messo tutto a null incluso questo
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void size_should_return_ok(){
    char* fun_name = "size_should_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, '1');

    int size_queue = size(queue);

    assert(size_queue == 1);
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void size_more_than_1_should_return_ok(){
    char* fun_name = "size_more_than_1_should_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, '1');
    enqueue(queue, '2');

    int size_queue = size(queue);

    assert(size_queue == 2);
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void size_empty_should_return_ok(){
    char* fun_name = "size_empty_should_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();

    int size_queue = size(queue);

    assert(size_queue == 0);
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_empty_return_ok(){
    char* fun_name = "peek_empty_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    char res = 'E';
    int peek_res = peek(queue, 0, &res);

    assert(res == 'E');
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_1_element_return_ok(){
    char* fun_name = "peek_1_element_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    char res = 'E';
    int peek_res = peek(queue, 0, &res);

    assert(res == 'A');
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_multiple_first_element_return_ok(){
    char* fun_name = "peek_multiple_first_element_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    char res = 'E';
    int peek_res = peek(queue, 0, &res);

    assert(res == 'A');
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_multiple_last_element_return_ok(){
    char* fun_name = "peek_multiple_last_element_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    char res = 'E';
    int peek_res = peek(queue, 1, &res);

    assert(res == 'B');
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_multiple_middle_element_return_ok(){
    char* fun_name = "peek_multiple_middle_element_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    enqueue(queue, 'D');
    char res = 'E';
    int peek_res = peek(queue, 1, &res);

    assert(res == 'B');
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_multiple_middle_last_element_return_ok(){
    char* fun_name = "peek_multiple_middle_last_element_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    enqueue(queue, 'D');
    char res = 'E';
    int peek_res = peek(queue, 2, &res);

    assert(res == 'C');
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void peek_out_of_list_element_return_ok(){
    char* fun_name = "peek_multiple_middle_last_element_return_ok";
    printf("\n\t\tBEGIN TEST \t[%s]\n",fun_name);
    
    CharQueueADT queue = mkQueue();
    enqueue(queue, 'A');
    enqueue(queue, 'B');
    enqueue(queue, 'C');
    enqueue(queue, 'D');
    char res = 'E';
    int peek_res = peek(queue, 4, &res);

    assert(res == 'E');
    assert(peek_res == 0);
    dsQueue(&queue);
    printf("\t\tEND TEST \t[%s]",fun_name);
}

void mk_queue_run_tests(){
    char* fun_name = "mk_queue_run_tests";
    printf("\n");
    printf("BEGIN [%s] Tests:\n", fun_name);

    mk_queue_should_ok_should_return(); // test mk_queue();

    // test ds_queue
    

    printf("\nEND Tests [%s]\n", fun_name);
}


void ds_queue_run_tests(){
    char* fun_name = "ds_queue_run_tests";
    printf("\n");
    printf("BEGIN [%s] Tests:\n", fun_name);

    ds_queue_null_pointier_should_return_ok();
    ds_queue_empty_queue_should_return_ok();
    ds_queue_not_empty_should_return_ok();

    printf("\nEND Tests [%s]\n", fun_name);
}

void size_tests(){
    char* fun_name = "size";
    printf("\n");
    printf("BEGIN [%s] Tests:\n", fun_name);

    size_should_return_ok();
    size_more_than_1_should_return_ok();
    size_empty_should_return_ok();

    printf("\nEND Tests [%s]\n", fun_name);
}

void peek_tests(){
    char* fun_name = "peek";
    printf("\n");
    printf("BEGIN [%s] Tests:\n", fun_name);

    peek_empty_return_ok();
    peek_1_element_return_ok();
    peek_multiple_first_element_return_ok();
    peek_multiple_last_element_return_ok();
    peek_multiple_middle_element_return_ok();
    peek_multiple_middle_last_element_return_ok();
    peek_out_of_list_element_return_ok();
    printf("\nEND Tests [%s]\n", fun_name);
}