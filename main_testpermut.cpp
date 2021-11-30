#include <stdio.h> // printf
#include "permuteur.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv)
{
  Permuteur * p = new Permuteur (12);
  int j=0;
  while(j<5){
      for (int i=0; i<12; i++)
          printf("%d  ",p->suivant());
      j++;
  }



  

  return 0;
}

