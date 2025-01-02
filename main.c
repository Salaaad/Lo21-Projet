#include <stdio.h>
#include <stdlib.h>
#include "fcts.h"

int main() {
    // Création du neurone en demandant les poids et le biais via InitNeur
    Neurone* neurone = InitNeur();
    
 // Exemple de liste chaînée d'entrées
    Entrée* entrees = creerListeEntrees(3);  // Demande 3 entrées à l'utilisateur

    // Calcul de la sortie du neurone
    int sortie = Outneurone(neurone, entrees);

    // Affichage de la sortie
    printf("La sortie du neurone est : %d\n", sortie);

    return 0;
}