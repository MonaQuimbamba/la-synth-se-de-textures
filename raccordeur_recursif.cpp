
#include "raccordeur_recursif.h"

int RaccordeurRecursif::calculerRaccord(MatInt2* distances, int* coupe)
{
  int milieu = distances->nColonnes()/2;
  int hauteur = distances->nLignes();
  int largeur = distances->nColonnes();
  int cout = 0;
  int y, x;
  for (y = 0; y < hauteur; y++)
  {
    for (x = 0; x < largeur; x++)
    {
      cout += distances->get(y, x);
    }
  }

  for (y = 0; y < hauteur; y++)
  {
    coupe[y] = milieu;
  }

  for (y = 0; y < hauteur; y++)
  {
    //coupe[y] = largeur * y / hauteur; // cela ferait une coupe diagonale
  }

  return cout;


}

void RaccordeurRecursif::recursif(MatInt2* distances, int lig , int col)
{
    if(col<distances->nColonnes()-1) // si on'est pas à la dernière colonne
    {

        recursif(distances,lig,col++); // on avance à la prochaine col
    }
    else  // on passe à la prochaine ligne
    {
        if(lig<distances->nLignes()-1) // si on 'est  pas à la fin du tableau on avance
        {
          recursif(distances,lig++,col); // on avance à la prochaine lig
        }
    }

}

RaccordeurRecursif::~raccordeurRecursif()
{
  // pas de ressources a liberer
}
