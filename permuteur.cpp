#include "permuteur.h"
#include <cstdlib>
#include <ctime>

/*!
 * Construit un nouveau permuteur qui retournera des nombres entiers dans
 * l'intervalle [0 .. (max-1)].
 */
Permuteur::Permuteur(int max)
{
    this->max=max;
    this->perm = (int*)malloc(this->max*sizeof(int)); // allouer le tableau de permutation
    this->indices = (int*)malloc(this->max*sizeof(int)); // alouer le tableu des indices
    for(int i=0 ; i < this->max ; i++)  // remplir le tableau de permutation
    {
        this->perm[i]=i;
    }

    this->permuter();
}

/**
*   Générer le prochain indice de bloc à lire.
**/
  int Permuteur::suivant()
  {
      if (this->i_perm == this->max){
          this->permuter();
      }

      int indice_next = this->indices[this->i_perm];
      int next = this->perm[indice_next];

      this->i_perm++;
      return next;
  }

  /**   Générer un ordre dans lequel parcourir notre tableau d'indices de
   *    blocs.
   */
  void Permuteur::permuter()
  {
      // Nettoyer le tableau d'indices
      for(int i=0 ; i < this->max ; i++)
      {
          this->indices[i]=-1;
      }

      // Créer une nouvelle permutation
      for (int i = 0; i < this->max; i++){
          int value = rand()%this->max;
          while (count(this->indices, this->indices+this->max, value) > 0)
              value = rand()%this->max;

          this->indices[i] = value;
      }

      // Mise à jour de l'indice à lire au début du nouveau tableau généré.
      this->i_perm=0;
  }

  Permuteur::~Permuteur()
  {
    free(this->perm);
    free(this->indices);
  }
