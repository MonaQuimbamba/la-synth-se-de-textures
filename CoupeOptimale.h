//
// Created by sfaisal on 14/12/2021.
//

#ifndef TEXTURES_COUPEOPTIMALE_H
#define TEXTURES_COUPEOPTIMALE_H


#include <iostream>
#include <bits/stdc++.h>
#include "matrix2d.h"

using namespace std;

/** \brief  Je suis une classe qui effectue un test de l'algorithme récursif
 *          sur la matrice de distance donnée en exemple dans le sujet.
 */
class CoupeOptimale {
private:
    MatInt2 exampleDistance = MatInt2(5,4);
public:
    CoupeOptimale();
    void calculerRaccord();
    ~CoupeOptimale();
    void printMatrice(MatInt2 *matrice);
    void calculPoids(MatInt2 *distances, MatInt2 *poids, int ligne_courante, int colonne_courante);
    int colonneDuPoidsMinimalDesCasesAdjacentes(MatInt2 *poids, int ligne, int colonne);

};


#endif //TEXTURES_COUPEOPTIMALE_H
