#include <stdio.h>
#include <stdlib.h>
#include "fcts.h"

int main() {
    // // Créer une couche avec 3 neurones, chacun ayant 2 entrées
    // Couche* maCouche = InitCouche(2, 1);

    // // Créer une liste chaînée d'entrées
    // Entrée* mesEntrees = creerListeEntrees(1); // Deux entrées, e.g., {1, 0}

    // // Calculer les sorties de la couche
    // Entrée* sorties = Outcouche(maCouche, mesEntrees);

    // // Afficher les sorties
    // printf("Sorties de la couche : ");
    // while (sorties != NULL) {
    //     printf("%d ", sorties->valeur);
    //     sorties = sorties->suivant;
    // }
    // printf("\n");






    // Neurone* Node=InitNeur(2);
    // Entrée* entry=creerListeEntrees(2);
    // afficherNeurone(Node);
    // printf("\n%i",Outneurone(Node,entry));



    int nbCouches = 2;  
    int neuronesParCouche[] = {2, 1};  
    int entreesPremiereCouche = 2;  

    // Créer le réseau
    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    printf("Réseau créé avec succès !\n");



    afficherReseau(reseau);

    Entrée* entreesInitiales = creerListeEntrees(2);  // Initialiser les entrées du réseau
    afficherListeEntrees(entreesInitiales);

    // Calculer la sortie du réseau
    Entrée* sortieReseau = OutReseau(reseau, entreesInitiales);

    // Afficher la sortie du réseau
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);
        
    return 0;
}
