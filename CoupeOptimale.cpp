#include "CoupeOptimale.h"

/** On construit l'objet en renseignant dans la matrice de distance
 *  de l'objet les valeurs données en l'exemple du sujet.*/
CoupeOptimale::CoupeOptimale() {
    // Création de la matrice de l'exemple du professeur
    this->exampleDistance.set(0,0,1);
    this->exampleDistance.set(0,1,3);
    this->exampleDistance.set(0,2,2);
    this->exampleDistance.set(0,3,1);

    this->exampleDistance.set(1,0,2);
    this->exampleDistance.set(1,1,1);
    this->exampleDistance.set(1,2,2);
    this->exampleDistance.set(1,3,3);

    this->exampleDistance.set(2,0,1);
    this->exampleDistance.set(2,1,3);
    this->exampleDistance.set(2,2,4);
    this->exampleDistance.set(2,3,2);

    this->exampleDistance.set(3,0,2);
    this->exampleDistance.set(3,1,4);
    this->exampleDistance.set(3,2,3);
    this->exampleDistance.set(3,3,1);

    this->exampleDistance.set(4,0,4);
    this->exampleDistance.set(4,1,3);
    this->exampleDistance.set(4,2,1);
    this->exampleDistance.set(4,3,2);
}

/** Cette méthode effectue le calcul des poids, de la coupe ; en affichant les données
 *  à chaque étapes pour faciliter le déboggage.*/
void CoupeOptimale::calculerRaccord() {
    cout << "Départ du test de l'algorithme récursif de calcul de coupe optimal." << endl;
    this->printMatrice(&this->exampleDistance);

    MatInt2 poids = MatInt2(this->exampleDistance.nLignes(), this->exampleDistance.nColonnes());
    for (int ligne = 0; ligne < poids.nLignes(); ligne++) {
        for (int colonne = 0; colonne < poids.nColonnes(); colonne++)
            poids.set(ligne, colonne, -1);
    }

    cout << "Matrice de poids initialisée." << endl;
    this->printMatrice(&poids);

    int colonne_poids_minimal = 0;
    int colonne_courante = 0;
    int ligne_courante = this->exampleDistance.nLignes()-1;
    for (; colonne_courante < this->exampleDistance.nColonnes(); colonne_courante++){
        this->calculPoids(&this->exampleDistance,&poids,ligne_courante,colonne_courante);

        if (poids.get(ligne_courante, colonne_courante) < poids.get(ligne_courante, colonne_poids_minimal)){
            colonne_poids_minimal = colonne_courante;
        }
    }

    cout << "Matrice de poids calculée. Résultat :" << endl;
    this->printMatrice(&poids);

    cout << "Calcul de la coupe..." << endl;
    int *coupe = new int[poids.nLignes()];
    for (int i = 0; i < poids.nLignes(); coupe[i]=0,i++);

    colonne_courante = colonne_poids_minimal;
    ligne_courante = poids.nLignes()-1;
    do {
        coupe[ligne_courante] = colonne_courante;

        colonne_courante = colonneDuPoidsMinimalDesCasesAdjacentes(&poids, ligne_courante, colonne_courante);
        ligne_courante--;
    } while (ligne_courante > 0);
    coupe[0] = colonne_courante;

    cout << "Fin du calcul de la coupe. Affichage " << endl << endl << "[";
    for (int indice = poids.nLignes()-1; indice >=0; indice--){
        if ( indice != 0)
            cout << coupe[indice] << ",";
        else
            cout << coupe[indice] << "]";
    }

    cout << endl << endl << "Fin du test." << endl;
}

/** Cette fonction renvoie la colonne associé au minimum des cases adjacente à celle renseignée
 *  en paramètre.*/
int CoupeOptimale::colonneDuPoidsMinimalDesCasesAdjacentes(MatInt2 *poids, int ligne, int colonne) {
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
/** Une méthode d'aide à l'affichage. */
void CoupeOptimale::printMatrice(MatInt2 *matrice) {
    cout << "Affichage de la Matrice : " << endl << endl;
    for (int ligne = 0 ; ligne < matrice->nLignes(); ligne++) {
        for (int colonne = 0; colonne < matrice->nColonnes(); colonne++){
            cout << "[" << matrice->get(ligne, colonne) << "]";
        }
        cout << endl;
    }
    cout << "Fin Affichage de la Matrice." << endl << endl;
}

/** La méthode principale récursive qui calcule le poids d'une cellule. */
void CoupeOptimale::calculPoids(MatInt2 *distances, MatInt2 *poids, int ligne_courante, int colonne_courante) {
    if (ligne_courante == 0){
        poids->set(ligne_courante, colonne_courante, distances->get(ligne_courante,colonne_courante));
    } else {
        int poids_minimal = -1;
        int poids_adjacent_0 = INT_MAX;
        int poids_adjacent_1 = INT_MAX;
        int poids_adjacent_2 = INT_MAX;

        if (colonne_courante == 0){
            poids_adjacent_0 = INT_MAX;

            if (poids->get(ligne_courante-1,colonne_courante) == -1) {
                calculPoids(distances, poids, ligne_courante-1, colonne_courante);
            }
            poids_adjacent_1 = poids->get(ligne_courante-1,colonne_courante);

            if(poids->get(ligne_courante-1,colonne_courante+1) == -1) {
                calculPoids(distances, poids, ligne_courante-1, colonne_courante+1);
            }
            poids_adjacent_2 = poids->get(ligne_courante-1, colonne_courante+1);
        } else if (colonne_courante == distances->nColonnes()-1){
            if (poids->get(ligne_courante-1,colonne_courante-1) == -1){
                calculPoids(distances, poids, ligne_courante-1, colonne_courante-1);
            }
            poids_adjacent_0 = poids->get(ligne_courante-1,colonne_courante-1);

            if (poids->get(ligne_courante-1,colonne_courante) == -1) {
                calculPoids(distances, poids, ligne_courante-1, colonne_courante);
            }
            poids_adjacent_1 = poids->get(ligne_courante-1,colonne_courante);

            poids_adjacent_2 = INT_MAX;
        } else {
            if (poids->get(ligne_courante-1,colonne_courante-1) == -1){
                calculPoids(distances, poids, ligne_courante-1, colonne_courante-1);
            }
            poids_adjacent_0 = poids->get(ligne_courante-1,colonne_courante-1);

            if (poids->get(ligne_courante-1,colonne_courante) == -1) {
                calculPoids(distances, poids, ligne_courante-1, colonne_courante);
            }
            poids_adjacent_1 = poids->get(ligne_courante-1,colonne_courante);

            if(poids->get(ligne_courante-1,colonne_courante+1) == -1) {
                calculPoids(distances, poids, ligne_courante-1, colonne_courante+1);
            }
            poids_adjacent_2 = poids->get(ligne_courante-1, colonne_courante+1);
        }

        if (poids_adjacent_0 < poids_adjacent_1){
            if (poids_adjacent_0 < poids_adjacent_2) {
                poids_minimal = poids_adjacent_0;
            } else {
                poids_minimal = poids_adjacent_2;
            }
        } else if (poids_adjacent_1 < poids_adjacent_2){
            poids_minimal = poids_adjacent_1;
        } else {
            poids_minimal = poids_adjacent_2;
        }

        poids->set(ligne_courante, colonne_courante, distances->get(ligne_courante,colonne_courante) + poids_minimal);
    }
}

/** Code du test unitaire pour l'algorithme iteratif */

CoupeOptimaleIteratif::CoupeOptimaleIteratif() {
    // Création de la matrice de l'exemple du professeur
    this->exampleDistance.set(0,0,1);
    this->exampleDistance.set(0,1,3);
    this->exampleDistance.set(0,2,2);
    this->exampleDistance.set(0,3,1);

    this->exampleDistance.set(1,0,2);
    this->exampleDistance.set(1,1,1);
    this->exampleDistance.set(1,2,2);
    this->exampleDistance.set(1,3,3);

    this->exampleDistance.set(2,0,1);
    this->exampleDistance.set(2,1,3);
    this->exampleDistance.set(2,2,4);
    this->exampleDistance.set(2,3,2);

    this->exampleDistance.set(3,0,2);
    this->exampleDistance.set(3,1,4);
    this->exampleDistance.set(3,2,3);
    this->exampleDistance.set(3,3,1);

    this->exampleDistance.set(4,0,4);
    this->exampleDistance.set(4,1,3);
    this->exampleDistance.set(4,2,1);
    this->exampleDistance.set(4,3,2);
}

void CoupeOptimaleIteratif::calculerRaccord() {
    cout << "Test de la coupe optimale façon itérative." << endl << endl;
    this->printMatrice(&this->exampleDistance);
    MatInt2 poids = MatInt2(this->exampleDistance.nLignes(), this->exampleDistance.nColonnes());
    for (int colonne = 0; colonne < this->exampleDistance.nColonnes(); colonne++){
        poids.set(0,colonne,this->exampleDistance.get(0,colonne));
    }

    for (int ligne = 1; ligne < this->exampleDistance.nLignes(); ligne++){
        for (int colonne = 0; colonne < this->exampleDistance.nColonnes(); colonne++){
            int poids_adjacent_0 = colonne > 0 ? this->exampleDistance.get(ligne,colonne) + poids.get(ligne-1,colonne-1) : INT_MAX;
            int poids_adjacent_1 = this->exampleDistance.get(ligne, colonne) + poids.get(ligne-1,colonne);
            int poids_adjacent_2 = colonne < this->exampleDistance.nColonnes()-1 ? this->exampleDistance.get(ligne,colonne) + poids.get(ligne-1,colonne+1) : INT_MAX;

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

    cout << "Matrice des poids calculée. Affichage : " << endl << endl;
    this->printMatrice(&poids);

    cout << "Calcul de la coupe..." << endl;
    int *coupe = new int[poids.nLignes()];
    for (int i = 0; i < poids.nLignes(); coupe[i]=0,i++);

    int colonne_courante = -1;
    int poids_courant = INT_MAX;
    for (int colonne = 0; colonne < poids.nColonnes(); colonne++){
        if (poids.get(poids.nLignes()-1, colonne) < poids_courant) {
            colonne_courante = colonne; // Pour déterminer le point de départ de la coupe optimale.
            poids_courant = poids.get(poids.nLignes()-1, colonne);
        }
    }

    int ligne_courante = poids.nLignes()-1;
    do {
        coupe[ligne_courante] = colonne_courante;

        colonne_courante = colonneDuPoidsMinimalDesCasesAdjacentes(&poids, ligne_courante, colonne_courante);
        ligne_courante--;
    } while (ligne_courante > 0);
    coupe[0] = colonne_courante;

    cout << "Fin du calcul de la coupe. Affichage " << endl << endl << "[";
    for (int indice = poids.nLignes()-1; indice >=0; indice--){
        if ( indice != 0)
            cout << coupe[indice] << ",";
        else
            cout << coupe[indice] << "]";
    }

    cout << endl << endl << "Fin du test." << endl;
}
/** Cette fonction renvoie la colonne associé au minimum des cases adjacente à celle renseignée
 *  en paramètre.*/
int CoupeOptimaleIteratif::colonneDuPoidsMinimalDesCasesAdjacentes(MatInt2 *poids, int ligne, int colonne) {
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

    /** Une méthode d'aide à l'affichage. */

    void CoupeOptimaleIteratif::printMatrice(MatInt2 *matrice) {
        cout << "Affichage de la Matrice : " << endl << endl;
        for (int ligne = 0 ; ligne < matrice->nLignes(); ligne++) {
            for (int colonne = 0; colonne < matrice->nColonnes(); colonne++){
                cout << "[" << matrice->get(ligne, colonne) << "]";
            }
            cout << endl;
        }
        cout << "Fin Affichage de la Matrice." << endl << endl;
    }

CoupeOptimaleIteratif::~CoupeOptimaleIteratif() {

}