#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED
//Structures et types
typedef struct element {
    int ind_colonne ;
    int val ;
    struct element *suiv ;
} Element ;

typedef Element* liste_ligne ; // pour avoir accès à une ligne de ma matrice

typedef struct matrice_creuse {
    int Nlignes;
    int Ncolonnes; 
    liste_ligne *ptr_ligne ; // pointeur de type liste_ligne
}matrice_creuse ;

    // 1. Remplissage matrice :
void remplirMatrice(matrice_creuse *m,int N, int M);

    // 2. Affichage matrice :
void afficherMatrice(matrice_creuse m);

    // 3. Affichage listes chaînées de la matrice :
void afficherMatriceListes(matrice_creuse m);

    // 4. Recherche d'une valeur dans la matrice :
int rechercherValeur(matrice_creuse m, int i, int j);
    //5. Affectation d'une valeur à un élément de la matrice :
void affecterValeur (matrice_creuse m, int i, int j, int val);

    // 6. Addition de deux matrices creuses (ou plus) :
void additionerMatrices(matrice_creuse m1,matrice_creuse m2);

    // 7. Calcul du gain en octets :
int nombreOctetsGagnes(matrice_creuse m);

    // 8. Fonctions utiles
int compter(matrice_creuse m);
void viderBuffer() ;

    // 9. Libérer matrice
void libererMatrice(matrice_creuse m);

#endif // TP3_H_INCLUDED