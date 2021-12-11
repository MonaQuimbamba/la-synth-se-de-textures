#ifndef _RACCORDEUR_RECURSIF_H
#define	_RACCORDEUR_RECURSIF_H

#include "raccordeur.h"
#include <bits/stdc++.h>
#include "tools.h"

using namespace std;

/*!
 * Raccordeur recursif :

 Pour le calcul de la coupe optimale, les poids des cellules
sont recalcul ́es suivant une formule recursive qui prends en
compte les poids de trois cellules adjacentes. Mi,j = Ei,j =
ei,j + min(Ei−1,j−1,Ei−1,j ,Ei-1,j+1
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class RaccordeurRecursifNaif : public Raccordeur
{
public :
  /*!
   * le calcul du raccord (\see{raccordeurRecursif#calculerRaccordRecursif}).
   * Le code effectif se trouve dans raccordeur_recursif.cpp
   */
  virtual int calculerRaccord(MatInt2* distances, int* coupe);
  int poidsDuChemin(MatInt2 *distances,
                    int ligne,
                    int colonne,
                    int *coupe);
  virtual ~RaccordeurRecursifNaif();
};


class RaccordeurRecursif : public Raccordeur
{
public:

    virtual int calculerRaccord(MatInt2 *distances, int *coupe);
    int poidsDuChemin(MatInt2 *distances,
                      int ligne,
                      int colonne,
                      int *coupe);
    virtual ~RaccordeurRecursif();
};

#endif
