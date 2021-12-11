#include "raccordeur_recursif.h"

/** Partie concernant le raccordeur_recursif naïf, il est fait pour le sport, fonctionnel avec comme
 *  entrée : Textureur gravier.tif 3 11 5 300 300 ; mais met 30 minutes à s'éxécuter à cause de
 *  l'explosion combinatoire.
 * */

int RaccordeurRecursifNaif::calculerRaccord(MatInt2 *distances, int *coupe)
{
    int poids_minimal = INT_MAX;

    for (int colonne = 0; colonne < distances->nColonnes(); colonne++)
    {
        int *coupe_temporaire = new int[distances->nLignes()]; // Initialisé à zéro cf. Zero Initialisation C++
        int poids = poidsDuChemin(distances, distances->nLignes()-1, colonne, coupe_temporaire);

        if (poids < poids_minimal) {
            poids_minimal = poids;
            for (int i = 0; i < distances->nLignes(); i++)
                coupe[i] = coupe_temporaire[i];
        }

        delete[]coupe_temporaire;
    }

    return poids_minimal;
};

int RaccordeurRecursifNaif::poidsDuChemin(MatInt2 *distances, int ligne, int colonne, int *coupe)
{
    if (ligne == 0)
    {
        coupe[0] = colonne;
        return distances->get(ligne, colonne);
    } else {
        int *poids_cellules_adjacentes = new int[3];
        int **coupes_temporaires = new int*[3];
        for (int i = 0; i < 3; coupes_temporaires[i] = new int[distances->nLignes()],i++);
        int indice_valeurs_minimales; // poids et chemin
        int poids;

        /** Comme dans l'illustration ci-dessous pour la plupart des cases,
         *  on calcule le poids d'une cellule à l'aide des trois cases
         *  adjacentes représentées par des O.
         *
         *  |O|O|O|
         *    |X|
         *
         *  Il existe cependant deux cas particuliers : ceux ou la cellule dont le
         *  poids est calculé est au bord de la matrice, il faut faire attention
         *  à ne pas faire d'accès en dehors de la matrice donc on modifie légèrement
         *  notre formule de récurrence en conséquence.
         *
         *  |O|O| |
         *  |X| | | (Cas n°1 cellule sur le bord gauche de la matrice.
         *
         *  | |O|O|
         *  | | |X| (Cas n°2 cellule sur le bord droit de la matrice.
         * */
        if (colonne == 0 ){
            poids_cellules_adjacentes[0] = INT_MAX;
            poids_cellules_adjacentes[1] = poidsDuChemin(distances,ligne-1, colonne,coupes_temporaires[1]);
            poids_cellules_adjacentes[2] = poidsDuChemin(distances,ligne-1, colonne+1,coupes_temporaires[2]);
        } else if ( colonne == distances->nColonnes()-1 ){
            poids_cellules_adjacentes[0] = poidsDuChemin(distances,ligne-1,colonne-1,coupes_temporaires[0]);
            poids_cellules_adjacentes[1] = poidsDuChemin(distances,ligne-1, colonne, coupes_temporaires[1]);
            poids_cellules_adjacentes[2] = INT_MAX;
        }  else {
            poids_cellules_adjacentes[0] = poidsDuChemin(distances,ligne-1,colonne-1,coupes_temporaires[0]);
            poids_cellules_adjacentes[1] = poidsDuChemin(distances, ligne-1, colonne, coupes_temporaires[1]);
            poids_cellules_adjacentes[2] = poidsDuChemin(distances,ligne-1, colonne+1, coupes_temporaires[2]);
        }

        /** Il y a une correspondance entre l'indice du tableau contenant les poids des cellules
         *  adjacentes et les tableaux contenants les coupes_temporaires.
         *
         *  On retrouve donc l'indice auquel se trouve notre poids minimal dans notre tableau de
         *  poids des cellules adjacentes et il correspond à l'indice de la coupe optimale de la sous-structure
         *  dont le poids est évalué dans la récursion éffectuée précédemment.
         *
         *  On copie donc la coupe de la sous-structure optimale en y ajoutant la colonne analysée lors de la
         *  récursion présente.
         *
         *  On retourne finalement pour résultat le poids de la récursion présente.
         *  */
        indice_valeurs_minimales = (int)(min_element(poids_cellules_adjacentes, poids_cellules_adjacentes+3) - poids_cellules_adjacentes);

        for (int i =0; i < ligne; i++){
            coupe[i] = coupes_temporaires[indice_valeurs_minimales][i];
        }
        coupe[ligne] = colonne;
        poids = poids_cellules_adjacentes[indice_valeurs_minimales] + distances->get(ligne,colonne);

        delete []poids_cellules_adjacentes;
        for (int i = 0; i < 3; i++)
            delete[]coupes_temporaires[i];
        delete[]coupes_temporaires;
        return poids;
    }
}

RaccordeurRecursifNaif::~RaccordeurRecursifNaif()
{
    // Rien à détruire
}


/** Partie qui code le raccordeur récursif en supprimant le problème d'explosion combinatoire.  **/


 int RaccordeurRecursif::calculerRaccord(MatInt2 *distances, int *coupe)
 {
     int poids_minimal = INT_MAX;

     for (int colonne = 0; colonne < distances->nColonnes(); colonne++)
     {
         int *coupe_temporaire = new int[distances->nLignes()]; // Initialisé à zéro cf. Zero Initialisation C++
         int poids = poidsDuChemin(distances, colonne, 0, coupe_temporaire);
         if (poids < poids_minimal)    //(ind_min_double(poids,poids_minimal) < 0) on pourrait verifier si le plus petit poids est inferieur de zero
         {
             poids_minimal = poids;
             for (int i = 0; i < distances->nLignes(); i++)
                 coupe[i] = coupe_temporaire[i];
         }

         delete[]coupe_temporaire;
     }

     return poids_minimal;
 }
int RaccordeurRecursif::poidsDuChemin(MatInt2 *distances,int ligne,int colonne,int *coupe)
{
    if(colonne>=distances->nLignes() || ligne<0 || ligne>=distances->nColonnes())
    {return 0;}
    int poids_cellules_adjacentes1 = distances->get(colonne,ligne-1);
    int poids_cellules_adjacentes2 = distances->get(colonne,ligne);
    int poids_cellules_adjacentes3 = distances->get(colonne,ligne+1);

    int indice_valeurs_minimales = ind_min_double(poids_cellules_adjacentes1,poids_cellules_adjacentes2,poids_cellules_adjacentes3);
    if(indice_valeurs_minimales< 0)
    {
        coupe[colonne] = ligne-1;
        return (poids_cellules_adjacentes1 + poidsDuChemin(distances, ligne-1, colonne+1, coupe));
    }else if(indice_valeurs_minimales == 0)
    {
        coupe[colonne] = ligne;
        return (poids_cellules_adjacentes2 + poidsDuChemin(distances, ligne, colonne+1, coupe));
    }
    else{
        coupe[colonne] = ligne+1;
        return (poids_cellules_adjacentes3 + poidsDuChemin(distances, ligne+1, colonne+1, coupe));
    }

}
RaccordeurRecursif::~RaccordeurRecursif()
{
     // rien à liberer
 }



