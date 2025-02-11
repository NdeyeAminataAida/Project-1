 #include <stdio.h>
#include "tp3.c"

int main() {
    matrice_creuse m1, m2, matrice;
    int N, M, N1, M1;
    int i, j, k, l, val, gain;

    // ============= MENU UTILISATEUR =============
    char choix = '0';
    printf("Bienvenue dans le programme des matrices creuses\n");

    while (choix != '8') {
        printf("\n======================================");
        printf("\n1. Remplir une matrice creuse");
        printf("\n2. Afficher une matrice creuse sous forme de tableau");
        printf("\n3. Afficher une matrice creuse sous forme de listes");
        printf("\n4. Donner la valeur d’un élément d’une matrice creuse");
        printf("\n5. Affecter une valeur à un élément d’une matrice creuse");
        printf("\n6. Additionner deux matrices creuses");
        printf("\n7. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée");
        printf("\n8. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");

        choix = getchar();
        getchar(); // Pour éviter de lire le retour à la ligne après getchar()

        switch (choix) {
            case '1':
            
                printf("Saisir le nombre de lignes et de colonnes : ");
                scanf("%d %d", &N1, &M1);
                getchar(); 
                remplirMatrice(&matrice, N1, M1);
             
                printf("Saisir le nombre de lignes et de colonnes : ");
                scanf("%d %d", &N, &M);
                remplirMatrice(&m1, N, M);
               
                printf("Saisir le nombre de lignes et de colonnes : ");
                scanf("%d %d", &N, &M);
                remplirMatrice(&m2, N, M);
               
                break;

            case '2':
                afficherMatrice(matrice);
                afficherMatrice(m1);
                afficherMatrice(m2);
                break;

            case '3':
                afficherMatriceListes(matrice);
                afficherMatriceListes(m1);
                afficherMatriceListes(m2);

                break;

            case '4':
                printf("Donner les indices de l'élément (ligne, colonne) : ");
                scanf("%d %d", &i, &j);
                getchar();
                val = rechercherValeur(m1, i, j);
                printf("La valeur à la position [%d][%d] est : %d\n", i, j, val);
                break;

            case '5':
                printf("Entrez les indices de l'élément (ligne, colonne) et la valeur : ");
                scanf("%d %d %d", &k, &l, &val);
                getchar();
                afficherMatriceListes(matrice);
                affecterValeur(m1, k, l, val);
                break;

            case '6':
                printf("Saisir le nombre de lignes et de colonnes : ");
                scanf("%d %d", &N, &M);
                getchar();
                remplirMatrice(&m1, N, M);
                remplirMatrice(&m2, N, M);
                additionerMatrices(m1, m2);
                printf("Affichage de la matrice après addition :\n");
                afficherMatrice(m1);
                break;

            case '7':
                remplirMatrice(&matrice,N,M);
                gain = nombreOctetsGagnes(matrice);
                printf("Le gain en espace est : %d octets\n", gain);
                break;
            

            case '8':
                printf("\n======== PROGRAMME TERMINE ========\n");
                libererMatrice(matrice);
                libererMatrice(m2);
                libererMatrice(m1);
                
                break;

            default:
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }

        printf("\n");
        viderBuffer(); // Supprime les caractères résiduels de l'entrée standard
    }

    return 0;
}
