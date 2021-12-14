#include "raccordeur_iteratif.h"

/** Fonction principale de calcul de la coupe et du coût de raccords des blocs.
 *  Voir CoupeOptimale.cpp pour le même algorithme tournant sur la matrice donnée
 *  en exemple dans le TP ;
 *
 *  Textureur gravier.tif 6 <-- pour avoir un affichage de l'algorithme
 *  en action sur la matrice donnée en TP.
 *  */
int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int* coupe)
{
    /** Initialisation de notre matrice de poids **/
    MatInt2 poids = MatInt2(distances->nLignes(), distances->nColonnes());
    for (int colonne = 0; colonne < distances->nColonnes(); colonne++){
        poids.set(0,colonne,distances->get(0,colonne));
    }

    /** On calcule la matrice de poids M (tel que décrite dans notre rapport, c-a-d les E_{i,j}).*/
    for (int ligne = 1; ligne < distances->nLignes(); ligne++){
        for (int colonne = 0; colonne < distances->nColonnes(); colonne++){
            int poids_adjacent_0 = colonne > 0 ? distances->get(ligne,colonne) + poids.get(ligne-1,colonne-1) : INT_MAX;
            int poids_adjacent_1 = distances->get(ligne, colonne) + poids.get(ligne-1,colonne);
            int poids_adjacent_2 = colonne < distances->nColonnes()-1 ? distances->get(ligne,colonne) + poids.get(ligne-1,colonne+1) : INT_MAX;

            if (poids_adjacent_0 < poids_adjacent_1){
                if (poids_adjacent_0 < poids_adjacent_2) {
                    poids.set(ligne, colonne, poids_adjacent_0);
                } else {
                    poids.set(ligne, colonne, poids_adjacent_2);
                }
            } else if (poids_adjacent_1 < poids_adjacent_2){
                poids.set(ligne, colonne, poids_adjacent_1);
            } else {
                poids.set(ligne, colonne, poids_adjacent_2);
            }
        }
    }

    /** On commence à partir d'ici le calcul de la coupe. */

    /** On détermine le plus petit poids de la derière ligne. */
    int colonne_courante = -1; // La colonne par laquelle commencer pour retrouver notre coupe
    int poids_courant = INT_MAX; // A la fin le plus petit poids se retrouve ici
    for (int colonne = 0; colonne < poids.nColonnes(); colonne++){
        if (poids.get(poids.nLignes()-1, colonne) < poids_courant) {
            colonne_courante = colonne; // Pour déterminer le point de départ de la coupe optimale.
            poids_courant = poids.get(poids.nLignes()-1, colonne);
        }
    }

    int ligne_courante = poids.nLignes()-1; // À partir de la dernière ligne
    do {
        coupe[ligne_courante] = colonne_courante; // Placer la colonne du poids minimal des cases adjacentes dans la coupe

        colonne_courante = colonneDuPoidsMinimalDesCasesAdjacentes(&poids, ligne_courante, colonne_courante); // Recalculer pour n-1
        ligne_courante--;
    } while (ligne_courante > 0);
    coupe[0] = colonne_courante;

    return poids_courant;
}

/** Regardes les 3 cases adjacentes (au sens de notre TP) à une colonne et renvoie la colonne où la valeur
 *  est la plus petite. Utilisé pour retrouver la coupe optimale.*/
int RaccordeurIteratif::colonneDuPoidsMinimalDesCasesAdjacentes(MatInt2 *poids, int ligne, int colonne) {
    int colonne_minimum = 0;
    int poids_adjacent_0 = INT_MAX;
    int poids_adjacent_1 = INT_MAX;
    int poids_adjacent_2 = INT_MAX;

    if (colonne == 0){
        poids_adjacent_1 = poids->get(ligne-1,colonne);
        poids_adjacent_2 = poids->get(ligne-1, colonne+1);
    } else if (colonne == poids->nColonnes()-1){
        poids_adjacent_0 = poids->get(ligne-1,colonne-1);
        poids_adjacent_1 = poids->get(ligne-1,colonne);
    } else {
        poids_adjacent_0 = poids->get(ligne-1,colonne-1);
        poids_adjacent_1 = poids->get(ligne-1,colonne);
        poids_adjacent_2 = poids->get(ligne-1, colonne+1);
    }


    if (poids_adjacent_0 < poids_adjacent_1){
        if (poids_adjacent_0 < poids_adjacent_2) {
            colonne_minimum = colonne-1;
        } else {
            colonne_minimum = colonne+1;
        }
    } else if (poids_adjacent_1 < poids_adjacent_2){
        colonne_minimum = colonne;
    } else {
        colonne_minimum = colonne+1;
    }

    return colonne_minimum;
}

RaccordeurIteratif::~RaccordeurIteratif()
{
    // rien à liberer
}