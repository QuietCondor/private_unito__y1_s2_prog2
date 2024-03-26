#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_LEN 5

// #define MAXSQUARE 46340

/*
* scrivete una funzione trovamax() che a tentativi  trovi l’ int piu’ grande che al quadrato non da overflow (pseudocodice):

curr =1
while not overflow :
      res = curr*curr
      if checkoverflow(res):
overflow = true
      else:
            curr = curr + 1
return curr-1
* 
* */

// funzione errata in alcuni casi...

bool is_in_overflow(int number){
  int quad = number * number;
  
  bool result = number > 0 && quad < 0;
  printf("Il quadrato di %d, e' %d. Il risultato e' %s", number, quad, result ? "OVERFLOW\n": "CORRETTO\n");
  
  return result; // allora va' in overflow
}

int trova_max()
{
  int number = 0;
  bool is_correct = true;
  while(is_correct) {
    is_correct = !is_in_overflow(number);
    number++;
  }

  return number;
}

int quadrato(int x) {
  int ret = 0;
  for (int i = 0; i < x; i++) {
    ret += x;
  }
  return ret < 0 ? -1 : ret;
}

int main(int argc, char *argv[]) {
  int max_quad = trova_max();
  printf("Il numero massimo senza overflow per gli interi e': %d", max_quad);
}
