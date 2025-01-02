#ifndef neuron
#define neuron

#include <stdlib.h>
#include <stdio.h>

// Structure pour une entrée
typedef struct Entrée {
    int valeur;
    struct Entrée* suivant;
} Entrée;


typedef Entrée* listEntrees;  // Liste chaînée d'entrées

typedef struct Poids {
    int valeur;
    struct Poids* suivant;
} Poids;

typedef Poids* listPoids;

typedef struct Neurone {
    listPoids listePoids;
    int biais;
    struct Neurone* suivant;
} Neurone;





// Fonction pour créer une liste chaînée de poids
Poids* creerListePoids(int nombreEntrees) {
    Poids* listePoids = NULL;
    Poids* courant = NULL;

    for (int i = 0; i < nombreEntrees; i++) {
        int poids;
        printf("Entrez le poids %d : ", i + 1);
        scanf("%d", &poids);
        
        Poids* nouveauPoids = (Poids*)malloc(sizeof(Poids));
        nouveauPoids->valeur = poids;  // Utilisation de 'poids' et non de 'valeur'
        nouveauPoids->suivant = NULL;

        if (listePoids == NULL) {
            listePoids = nouveauPoids;  // Si c'est le premier poids, il devient la tête de la liste
        } else {
            courant->suivant = nouveauPoids;  // Sinon, on ajoute à la fin de la liste
        }
        courant = nouveauPoids;  // On avance le pointeur courant
    }

    return listePoids;
}


// Fonction pour initialiser un neurone avec une liste chaînée de poids et un biais
Neurone* InitNeur() {
    int nombreEntrees, biais;
    
    // Demander à l'utilisateur combien de poids il souhaite entrer
    printf("Entrez le nombre d'entrées (poids) : ");
    scanf("%d", &nombreEntrees);
    
    // Créer la liste chaînée des poids via la fonction creerListePoids
    Poids* listePoids = creerListePoids(nombreEntrees);

    // Demander à l'utilisateur le biais
    printf("Entrez le biais : ");
    scanf("%d", &biais);

    // Créer le neurone avec la liste chaînée de poids et le biais
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    neurone->biais = biais;
    neurone->listePoids = listePoids;  // Liste chaînée de poids fournie
    neurone->suivant = NULL;

    return neurone;
}


// Fonction pour créer un noeud d'entrée
Entrée* creerEntree(int valeur) {
    Entrée* nouvelleEntree = (Entrée*)malloc(sizeof(Entrée));
    nouvelleEntree->valeur = valeur;
    nouvelleEntree->suivant = NULL;
    return nouvelleEntree;
}

// Fonction pour créer une liste chaînée d'entrées
Entrée* creerListeEntrees(int nombreEntrees) {
    Entrée* listeEntrees = NULL;
    Entrée* courant = NULL;

    for (int i = 0; i < nombreEntrees; i++) {
        int entree;
        printf("Entrez l'entrée %d : ", i + 1);
        scanf("%d", &entree);
        
        Entrée* nouvelleEntree = creerEntree(entree);

        if (listeEntrees == NULL) {
            listeEntrees = nouvelleEntree;  // Si c'est la première entrée, elle devient la tête de la liste
        } else {
            courant->suivant = nouvelleEntree;  // Sinon, on ajoute à la fin de la liste
        }
        courant = nouvelleEntree;  // On avance le pointeur courant
    }

    return listeEntrees;
}

void afficherNeurone(Neurone* neurone) {
    Poids* courant = neurone->listePoids;
    printf("Poids : ");
    while (courant != NULL) {
        printf("%d ", courant->valeur);
        courant = courant->suivant;
    }
    printf("\nBiais : %d\n", neurone->biais);
}


// Fonction pour calculer la sortie du neurone avec une liste chaînée d'entrées
int Outneurone(Neurone* neurone, Entrée* entrees) {
    int somme = 0;
    Poids* courantPoids = neurone->listePoids;
    Entrée* courantEntree = entrees;

    // Calcul de la somme pondérée des entrées
    while (courantPoids != NULL && courantEntree != NULL) {
        somme += courantPoids->valeur * courantEntree->valeur;  // w_i * e_i
        courantPoids = courantPoids->suivant;
        courantEntree = courantEntree->suivant;
    }

    // Ajouter le biais (seuil) au résultat
    somme += neurone->biais;

    // Appliquer la fonction d'activation
    if (somme >= 0) {
        return 1;  // Sortie activée (1)
    } else {
        return 0;  // Sortie non activée (0)
    }
}

#endif