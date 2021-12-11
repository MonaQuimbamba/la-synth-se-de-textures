#include <stdio.h> // printf
#include <ctime>
#include "permuteur.h"
using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));
    Permuteur * p = new Permuteur (9);
    int j=0;
    while (j < 5) {

      for (int i = 0; i < 9; i++)
          printf("%d  ", p->suivant());
      printf("\n");
      j++;
  }

  return 0;
}

