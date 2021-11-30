#include "permuteur.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdlib.h> 

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
    this->indices[i]=i;
  }
    this->i_perm =this->indices[0];
}
/**
* Retourne l'entier suivant
**/
  int Permuteur::suivant()
  {
      if(this->i_perm <this->max )
      {
          this->i_perm++;
      }
      else{

          this->permuteur();

          this->i_perm=this->indices[0];
      }
    return this->perm[this->i_perm];
  }


  void Permuteur::permuteur()
  {
      for(int i=0 ; i< this->max ; i++) // on rempli le tableau des indeces avec que de -1
      { this->indices[i]=-1;}

      int i=0;
      bool arreter=false;
      while ( arreter==false && i < this->max) // tant qu'on a pas fini les -1 par les nouveaux indices on boucle
      {

          bool plusDeM1 = find(this->indices, this->indices+ this->max,-1) != this->indices+ this->max;
          if(plusDeM1==0){ // si il y'a plus des -1 dans le tableau , on arrete la boucle
              arreter=true;
              cout<<" in \n";
          }

          int val = rand() % this->max;
          bool existValInIndeces = find(this->indices, this->indices+this->max,val) != this->indices+this->max;
          if(existValInIndeces==1) // si le val existe déjà dans indices on increment le i++
          { i++;}
          else{ // s'il n'existe pas encore on l'ajoute dans le tableu indices , c-à-d on remplace le -1 par un vrai index
              this->indices[i]=val;
          }


      }



  }

  Permuteur::~Permuteur()
  {

    free(this->perm);
    free(this->indices);
    /*!
     * Libere les ressources utilisees par ce permuteur.
     */
  }
