#include <stdio.h>
#include <stdlib.h>
#include "reseau.h"

int main() {
    // // Créer une couche avec 3 neurones, chacun ayant 2 entrées                                                  TEST AVEC JUSTE LES COUCHES
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






    // Neurone* Node=InitNeur(2);                           TEST AVEC JUSTE LES NEURONES
    // Entrée* entry=creerListeEntrees(2);
    // afficherNeurone(Node);
    // printf("\n%i",Outneurone(Node,entry));



    int nbCouches = 2;  
    int neuronesParCouche[] = {3,2};  
    int entreesPremiereCouche = 3;  

    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    afficherReseau(reseau);

    Entrée* entreesInitiales = creerListeEntrees(entreesPremiereCouche);  
    printf("Entrée du réseau : ");
    afficherListeEntrees(entreesInitiales);

    Entrée* sortieReseau = OutReseau(reseau, entreesInitiales);
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);
        
    return 0;
}
