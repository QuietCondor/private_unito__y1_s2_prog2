#include <stdio.h>
#include "test.h"
#include <assert.h>
#include <stdbool.h>

#define MAX_LEN 5

// #define MAXSQUARE 46340

// funzione errata in alcuni casi...

int quadrato(int x) {
  int ret = 0;
  for (int i = 0; i < x; i++) {
    ret += x;
  }
  return ret < 0 ? -1 : ret;
}

int main(int argc, char *argv[]) {
  int inputs[MAX_LEN] =   {1, 2,  -1,   -2, 123456};
  int outputs[MAX_LEN] =  {1, 4,   1,    4, -1};
  
  for(int i=0; i<MAX_LEN; i++){
    int result = quadrato(inputs[i]);
    bool is_correct = result == outputs[i];
    printf("Il risultato e' %s. Per %d \n\t- Risultato: %d \n\t- Expected: %d\n\n", is_correct? "CORRETTO" : "NON CORRETTO", inputs[i], result, outputs[i]);
  }
  
  //printf("%d\n", quadrato(4)); 
  //printf("%d\n", quadrato(-4));
}
