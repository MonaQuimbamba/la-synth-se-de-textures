#include "permuteur.h"
#include <vector>
#include <iostream>
#include <cstdlib>


/*!
 * Construit un nouveau permuteur qui retournera des nombres entiers dans
 * l'intervalle [0 .. (max-1)].
 */
Permuteur::Permuteur(int max)
{
  max=max;
  perm = (int*)malloc(max*sizeof(int)); // allouer le tableau de permutation
  indices = (int*)malloc(max*sizeof(int)); // alouer le tableu des indices
  for(int i=0 ; i < max ; i++)  // remplir le tableau de permutation
  {
    perm[i]=i;
    indices[i]=i;
  }
  i_perm =indices[0];
}
/**
* Retourne l'entier suivant
**/
  int Permuteur::suivant()
  {
    if(i_perm <max){
      i_perm++;
    }
    else{
      i_perm=indices[0];
    }
    return perm[i_perm];

  }

  Permuteur::~Permuteur()
  {

    free(perm);
    free(indices);
    /*!
     * Libere les ressources utilisees par ce permuteur.
     */
  }
