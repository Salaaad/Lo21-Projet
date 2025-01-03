#include <stdio.h>
#include <stdlib.h>
#include "fcts.h"

int main() {
    // Créer une couche avec 3 neurones, chacun ayant 2 entrées
    Couche* maCouche = InitCouche(2, 1);

    // Créer une liste chaînée d'entrées
    Entrée* mesEntrees = creerListeEntrees(1); // Deux entrées, e.g., {1, 0}

    // Calculer les sorties de la couche
    Entrée* sorties = Outcouche(maCouche, mesEntrees);

    // Afficher les sorties
    printf("Sorties de la couche : ");
    while (sorties != NULL) {
        printf("%d ", sorties->valeur);
        sorties = sorties->suivant;
    }
    printf("\n");



    // Neurone* Node=InitNeur(2);
    // Entrée* entry=creerListeEntrees(2);
    // afficherNeurone(Node);
    // printf("\n%i",Outneurone(Node,entry));
    return 0;
}
