#ifndef _RACCORDEUR_ITERATIF_H
#define	_RACCORDEUR_ITERATIF_H

#include "raccordeur.h"
#include <bits/stdc++.h>
#include "tools.h"

using namespace std;

/*!
 * Raccordeur iteratif :

 Pour le calcul de la coupe optimale, les poids des cellules
sont recalcul ́es suivant une formule recursive qui prends en
compte les poids de trois cellules adjacentes. Mi,j = Ei,j =
ei,j + min(Ei−1,j−1,Ei−1,j ,Ei-1,j+1
 * Cette classe est une classe concrete et derive/implemente le concept de
 * Raccordeur (\see{Raccordeur}).
 */
class RaccordeurIteratif : public Raccordeur
{
public :
    /*!
     * le calcul du raccord (\see{raccordeurIteratif#calculerRaccordIteratif}).
     * Le code effectif se trouve dans raccordeur_iteratif.cpp
     */
    virtual int calculerRaccord(MatInt2* distances, int* coupe);
    virtual ~RaccordeurIteratif();
};



#endif
