#ifndef _RACCORDEUR_RecursifNaif_H
#define	_RACCORDEUR_RecursifNaif_H

#include "raccordeur.h"

/*!
 * Raccordeur Recursif Naif  : 
 *
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class RaccordeurRecursifNaif : public Raccordeur
        {

  /*!
   * le calcul du raccord (\see{RaccordeurRecursifNaif#calculerRaccord}).
   * Le code effectif se trouve dans RaccordeurRecursifNaif.cpp
   */
  virtual int calculerRaccord(MatInt2* distances, int* coupe);

  virtual ~RaccordeurRecursifNaif(); // destructeur

};

#endif	/* _RACCORDEUR_RecursifNaif_H */