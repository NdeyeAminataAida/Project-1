#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
//Q1
void remplirMatrice(matrice_creuse *m,int N, int M) {
    m -> Nlignes = N;
    m ->Ncolonnes = M;
    m -> ptr_ligne = (liste_ligne*)malloc(N * sizeof(liste_ligne));
    if (m -> ptr_ligne == NULL){
        printf("erreur d'allocation mémoire\n");
        exit(1);
    }
    for (int i = 0; i < N; i ++){
        m ->ptr_ligne[i] = NULL; 
    }
    for (int i = 0; i < N; i ++){ 
        int val;
        for (int j = 0; j < M; j ++){ 
            printf("saisir la val de la case [%d][%d]:",i,j);
            scanf("%d",&val); 
            if (val){ 
               liste_ligne nouveau = (liste_ligne)malloc(sizeof(Element));
                 if (nouveau == NULL){  
                    printf("erreur d'allocation mémoire\n");
                    exit(1);
                }
                nouveau -> ind_colonne= j; 
                nouveau -> val = val ; 
                nouveau -> suiv = NULL ; 
                if (m -> ptr_ligne[i] == NULL){ 
                    m -> ptr_ligne[i] = nouveau ; 
                } 
                else{ 
                    liste_ligne actuel = m ->ptr_ligne[i]; 
                    while (actuel -> suiv != NULL ){
                        actuel = actuel -> suiv; 
                    }
                    actuel -> suiv = nouveau;
                }
            }
        }
    }
}
//Q2
void afficherMatrice(matrice_creuse m){
    int i,j;
    for (i = 0; i < m.Nlignes; i ++){
        liste_ligne actuel  = m.ptr_ligne[i]; // on parcourt ligne par ligne la matrice
        for (j = 0; j < m.Ncolonnes; j++){
            if (actuel != NULL && actuel -> ind_colonne== j){ 
                printf("%d ", actuel -> val); 
                actuel = actuel -> suiv ; 
            }
        }
        printf("\n"); 
    }

}
//Q3
void afficherMatriceListes (matrice_creuse m){
    for (int i = 0; i < m.Nlignes; i ++){
       liste_ligne actuel  = m.ptr_ligne[i] ;
        while(actuel != NULL){
            printf("ligne: %d, ind_colonne: %d, la val est: %d\n ",i,actuel -> ind_colonne,actuel -> val); ;
            actuel = actuel -> suiv ;
        }
       printf("\n");
    }
}
// Q4
int rechercherValeur(matrice_creuse m, int i, int j){ 
    liste_ligne actuel  = m.ptr_ligne [i];
    while (actuel != NULL){
        if(actuel -> ind_colonne== j){
            return actuel -> val ; 
        }
        actuel = actuel -> suiv ;
    }
    return 0;
}
// Q5
void affecterValeur(matrice_creuse m, int i, int j, int val) {
    Element *pnt = m.ptr_ligne[i];
    Element *precedent = NULL;

    // Parcours pour trouver l'indice j ou l'emplacement d'insertion
    while (pnt != NULL && pnt->ind_colonne < j) {
        precedent = pnt;  // Mémoriser le précédent
        pnt = pnt->suiv;  // Avancer dans la liste
    }

    // Cas 1 : Suppression (val == 0)
    if (val == 0) {
        if (pnt != NULL && pnt->ind_colonne == j) { // Si l'élément existe
            if (precedent == NULL) {  // Suppression au début
                m.ptr_ligne[i] = pnt->suiv;
            } else {  // Suppression au milieu/fin
                precedent->suiv = pnt->suiv;
            }
            free(pnt);  // Libérer la mémoire
        }
    }
    // Cas 2 : Insertion ou modification (val != 0)
    else {
        if (pnt != NULL && pnt->ind_colonne == j) { // Si l'élément existe déjà
            pnt->val = val;  // Mettre à jour la valeur
        } else { // Si l'élément n'existe pas, insérer un nouveau
            Element* nouveau = (Element*)malloc(sizeof(Element));
            nouveau->ind_colonne = j;
            nouveau->val = val;
            nouveau->suiv = pnt;  // Connecter au suivant (pnt)

            if (precedent == NULL) {  // Insertion au début
                m.ptr_ligne[i] = nouveau;
            } else {  // Insertion au milieu ou à la fin
                precedent->suiv = nouveau;
            }
        }
    }
}

//Q6
void additionerMatrices(matrice_creuse m1,matrice_creuse m2){
    // Parcours des lignes des deux matrices m1 et m2
    for (int i = 0; i < m1.Nlignes;i ++){
       liste_ligne actuel1 = m1.ptr_ligne[i];
       liste_ligne actuel2 = m2.ptr_ligne[i];
       liste_ligne dernier = NULL; // pour suivre l'insertion dans m1, mise à jour des nouvelles valeurs de actuel1 
        while(actuel2 != NULL){
            /*cas où la ind_colonnede m2 est vide, soit dans cette ind_colonnela val est 0*/
            while (actuel1 != NULL && actuel1 -> ind_colonne< actuel2 -> ind_colonne){ 
                    dernier = actuel1;
                    actuel1 = actuel1 -> suiv;
            }
                /*cas idéal où les indices des ind_colonnes coicident soit ont des valeurs autres que 0*/
                if(actuel1 != NULL && actuel1 -> ind_colonne == actuel2 -> ind_colonne){
                    actuel1 -> val = actuel1 -> val + actuel2 -> val;
                    // on vérifie que cette valn'est pas 0 cas où addition nombre négatif et nombre positif comme -1+1, on le retire de la matrice1
                    if(actuel1 -> val == 0){
                        if(dernier == NULL){
                            m1.ptr_ligne[i] =  actuel1 -> suiv;
                        }
                        else{
                            dernier -> suiv = actuel1 -> suiv;
                        }
                        /*on crée temp pour conserver l'adresse de actuel1 avant suppression comme ça on garde une trace de actuel1 pour pouvoir le faire avancer dans la liste chainée ou ligne*/
                       liste_ligne temp = actuel1;
                        actuel1 = actuel1 -> suiv;
                        free(temp);
                    }
                    // cas où actuel1 -> val != 0
                    else{
                        dernier = actuel1;
                        actuel1 = actuel1 -> suiv;
                    }
                    actuel2 = actuel2 -> suiv;
                
                }
                // si c l'indice de actuel2 qui est supérieur à celui de actuel1 ou actuel1 == NULL
                else{ 
                   liste_ligne nouveau = (Element*) malloc(sizeof(Element));
                    nouveau -> ind_colonne= actuel2 -> ind_colonne;
                    nouveau -> val = actuel2 -> val;
                    nouveau -> suiv = actuel1;
                    /*insertion en tête de liste chainée ou ligne*/
                    if(dernier == NULL){
                        m1.ptr_ligne[i] = nouveau;
                    }
                    /*Dans ce cas, dernier = actuel1, on insère en fin de ligne*/
                    else{
                        dernier -> suiv = nouveau;
                    }
                    dernier = nouveau;
                    actuel2 = actuel2 -> suiv;
            }
                
        }
    }
}
//Q7
int compter(matrice_creuse m);
int nombreOctetsGagnes(matrice_creuse m){ //que des opérations élémentaires donc en 0(1) et prise en compte complexité compter(m)
    int gain;
    int tailleInt = sizeof(int), taillePointeur = sizeof(void*);
    int tailleElement = 2*sizeof(int) + taillePointeur;
    /*initialisation des deux tailles pour une matrice sans utilisation de structure et une matrice avec notre représentation*/
    int tailleNormale;
    int tailleStructure;
    // Calcul des valeurs de ces tailles
    tailleNormale = m.Ncolonnes * m.Nlignes * tailleInt; 
    tailleStructure = compter(m) * tailleElement ;
    //Calcul du gain
    gain = tailleNormale - tailleStructure;
    return gain;
}
/*fontion utile qui calcule le nombre d'éléments non nuls dans la matrice creuse m*/
int compter(matrice_creuse m){
    int compteur = 0;
    for(int i = 0; i < m.Nlignes; i ++){ 
       liste_ligne actuel = m.ptr_ligne[i];
        while(actuel != NULL){ 
            compteur ++;
            actuel = actuel -> suiv;
        }
    }
    return compteur;
}
// Vider le buffer (utile quand on utlise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
//8 Libération de mémoire
void libererMatrice(matrice_creuse m){
    for(int i = 0; i < m.Nlignes; i ++){
        liste_ligne actuel = m.ptr_ligne[i];
        while(actuel != NULL){
            liste_ligne temp = actuel;
            actuel = actuel ->suiv;
            free(temp);
        }
    }
}























