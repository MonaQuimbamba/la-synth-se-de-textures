#include "raccordeur_iteratif.h"

int RaccordeurIteratif::calculerRaccord(MatInt2* distances, int* coupe)
{


    int poids_minimal = INT_MAX;
    for(int colonne=0;colonne<distances->nColonnes();colonne++)
    {
        int* coupe_temporaire = new int[distances->nLignes()];// Initialisé à zéro cf. Zero Initialisation C++
        int poids=0;
        for(int ligne=0;ligne<distances->nLignes();ligne++)
        {
            int poids_cellules_adjacentes1 = (colonne>0)?distances->get(ligne,colonne-1):INT_MAX;
            int poids_cellules_adjacentes2 = distances->get(ligne,colonne);
            int poids_cellules_adjacentes3 = (colonne<distances->nColonnes()-1)?distances->get(ligne,colonne+1):INT_MAX;
            int indice_valeurs_minimales = ind_min_double(poids_cellules_adjacentes1,poids_cellules_adjacentes2,poids_cellules_adjacentes3);

            if(indice_valeurs_minimales<0)
            {
                coupe_temporaire[ligne] = colonne-1;
                poids += poids_cellules_adjacentes1;

            }
            else if(indice_valeurs_minimales==0)
            {
                coupe_temporaire[ligne] = colonne;
                poids += poids_cellules_adjacentes2;
            }
            else
            {
                coupe_temporaire[ligne] = colonne+1;
                poids += poids_cellules_adjacentes3;
            }
        }
       int ind = ind_min_double(poids, poids_minimal);
        if(ind<0){
            poids_minimal = poids;
            //for (int i = 0; i < distances->nLignes(); i++) // prk y'a une difference entre la boucle et l'affectation d'un tableau à un autre tableau
             //   coupe[i] = coupe_temporaire[i];

            coupe = coupe_temporaire;
        }

        delete[]coupe_temporaire;
    }
    return poids_minimal;

}

RaccordeurIteratif::~RaccordeurIteratif()
{
    // rien à liberer
}