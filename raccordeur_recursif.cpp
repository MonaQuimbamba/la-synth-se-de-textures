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

/** On modifie légèrement notre fonction de calcul de raccord par créer notre matrice M
 *  (on suit les notations indiquées dans notre rapport) qui contient les poids des cellules.
 *  Pour rappel nous appelons poids des cellules, les E_{i,j} donnés en appliquant la formule de récurence
 *  sur les différences de couleur des pixels notés e_{i,j}. C'est cette matrice M qui va nous permettre
 *  de stocker les poids lorsqu'ils ne sont pas encore calculés et de les retrouver lorsqu'ils ont
 *  déjà été calculé.
 *
 *  */

 int RaccordeurRecursif::calculerRaccord(MatInt2 *distances, int *coupe)
 {
     int poids_minimal = INT_MAX;
     /** Initialisation de la Matrice M */
     this->M = MatInt2(distances->nLignes(), distances->nColonnes());
     for(int i = 0; i < M.nLignes(); i++)
         for(int j = 0; j < M.nColonnes(); j++)
             this->M.set(i,j,-1); // -1 représente l'état non-calculé du poids d'une cellule.
    /** Fin Initialisation */
/*
    for (int i =0; i < distances->nLignes();i++){
        printf("coupe[%d] = %d\t", i , coupe[i]);
    }
*/
     int colonne_poids_min = 0;

     for (int colonne = 0; colonne < distances->nColonnes(); colonne++)
     {

         int poids = poidsDuChemin(distances, distances->nLignes()-1, colonne);
         this->M.set(distances->nLignes()-1,colonne, poids);
         if (poids < this->M.get(distances->nLignes()-1,colonne_poids_min)){
             colonne_poids_min = colonne;
         }
     }

     int ligne_courante = distances->nLignes()-1;
     do {
        coupe[ligne_courante] = colonne_poids_min;

        if (colonne_poids_min == 0){
            if (this->M.get(ligne_courante-1, colonne_poids_min) < this->M.get(ligne_courante-1, colonne_poids_min+1)){
                colonne_poids_min = colonne_poids_min;
            } else {
                colonne_poids_min = colonne_poids_min+1;
            }
        } else if (colonne_poids_min == distances->nColonnes()-1){
            if (this->M.get(ligne_courante-1, colonne_poids_min-1) < this->M.get(ligne_courante-1, colonne_poids_min)){
                colonne_poids_min = colonne_poids_min-1;
            } else {
                colonne_poids_min = colonne_poids_min;
            }
        } else {
            if (this->M.get(ligne_courante-1, colonne_poids_min-1) < this->M.get(ligne_courante-1, colonne_poids_min)){
                if (this->M.get(ligne_courante-1, colonne_poids_min-1) < this->M.get(ligne_courante-1, colonne_poids_min+1)){
                    colonne_poids_min = colonne_poids_min-1;
                }
            } else if (this->M.get(ligne_courante-1, colonne_poids_min) < this->M.get(ligne_courante-1, colonne_poids_min+1)) {
                colonne_poids_min = colonne_poids_min;
            } else {
                colonne_poids_min = colonne_poids_min+1;
            }
        }
        ligne_courante--;
     } while (ligne_courante > 0);
        coupe[ligne_courante] = colonne_poids_min;
    return poids_minimal;
 }

 /**    On reprends simplement le code naïf de notre raccordeur récursif, cependant, on utilise M afin
  *     de vérifier si l'on a déjà calculé un chemin, auquel cas on récupère le poids dans M sinon
  *     on le calcule et on le place dans M.*/
int RaccordeurRecursif::poidsDuChemin(MatInt2 *distances,int ligne,int colonne)
{
    if (ligne == 0)
    {
        this->M.set(ligne,colonne, distances->get(ligne,colonne)); /// Ajout du poids dans M
        return distances->get(ligne, colonne);
    } else {
        int poids_cellule_adjacente_0, poids_cellule_adjacente_1, poids_cellule_adjacente_2;
        int indice_valeurs_minimales; // poids et chemin
        int poids;

        /** On modifie cet appel récusif pour prendre en compte le calcul éffectué possiblement
         *  précédemment. On utilise une condition ternaire pour éviter les if() {} qui ralongerait
         *  beaucoup trop notre code au risque de réduire la lisibilité du code.
         *  On précise donc la forme de ces conditions ternaires :
         *      Cellule non calculée ?
         *          effectuer la récursion
         *      :   récupérer le résultat dans M
         *  */
        if (colonne == 0 ){
            poids_cellule_adjacente_0 = INT_MAX;
            poids_cellule_adjacente_1 = this->M.get(ligne-1,colonne) == -1 ?
                        poidsDuChemin(distances,ligne-1, colonne)
                    :   this->M.get(ligne-1, colonne);
            poids_cellule_adjacente_2 = this->M.get(ligne-1,colonne+1) == -1 ?
                        poidsDuChemin(distances,ligne-1, colonne+1)
                    :   this->M.get(ligne-1, colonne+1);
        } else if ( colonne == distances->nColonnes()-1 ){
            poids_cellule_adjacente_0 = this->M.get(ligne-1, colonne-1) == -1 ?
                        poidsDuChemin(distances,ligne-1,colonne-1)
                    :   this->M.get(ligne-1, colonne-1);
            poids_cellule_adjacente_1 = this->M.get(ligne-1, colonne) == -1 ?
                    poidsDuChemin(distances,ligne-1, colonne)
                    :   this->M.get(ligne-1, colonne);
            poids_cellule_adjacente_2 = INT_MAX;
        }  else {
            poids_cellule_adjacente_0 = this->M.get(ligne-1, colonne-1) == -1 ?
                        poidsDuChemin(distances,ligne-1,colonne-1)
                    :   this->M.get(ligne-1, colonne-1);
            poids_cellule_adjacente_1 = this->M.get(ligne-1, colonne) == -1 ?
                        poidsDuChemin(distances, ligne-1, colonne)
                    :   this->M.get(ligne-1, colonne);
            poids_cellule_adjacente_2 = this->M.get(ligne-1, colonne+1) == -1 ?
                    poidsDuChemin(distances,ligne-1, colonne+1)
                    :   this->M.get(ligne-1, colonne+1);
        }

        if (poids_cellule_adjacente_0 < poids_cellule_adjacente_1) {
            if (poids_cellule_adjacente_0 < poids_cellule_adjacente_2) {
                poids = poids_cellule_adjacente_0;
            }
        } else if (poids_cellule_adjacente_1 < poids_cellule_adjacente_2) {
            poids = poids_cellule_adjacente_1;
        } else {
            poids = poids_cellule_adjacente_2;
        }

        this->M.set(ligne,colonne, poids); /// On ajoute le poids de la cellule dans M.

        return poids;
    }
}
RaccordeurRecursif::~RaccordeurRecursif()
{
}



