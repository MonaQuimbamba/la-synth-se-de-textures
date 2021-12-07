#ifndef _RACCORDEUR_SIMPLE_H
#define	_RACCORDEUR_SIMPLE_H

#include "raccordeur.h"

/*!
 * Raccordeur recursif :

 Pour le calcul de la coupe optimale, les poids des cellules
sont recalcul ́es suivant une formule recursive qui prends en
compte les poids de trois cellules adjacentes. Mi,j = Ei,j =
ei,j + min(Ei−1,j−1,Ei−1,j ,Ei-1,j+1
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class raccordeurRecursif : public RaccordeurRecursif
{

  /*!
   * le calcul du raccord (\see{raccordeurRecursif#calculerRaccordRecursif}).
   * Le code effectif se trouve dans raccordeur_recursif.cpp
   */
  virtual int calculerRaccord(MatInt2* distances, int* coupe);
   virtual void recursif(MatInt2* distances, int lig , int col );

  virtual ~raccordeurRecursif(); // destructeur

};

#endif
