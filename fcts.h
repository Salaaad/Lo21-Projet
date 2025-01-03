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

typedef struct Neurone* listNeurone;

typedef struct Couche {
    Neurone* listeNeurones; 
    struct Couche* suivant; 
} Couche;

typedef struct Couche* listCouche;


// Fonction pour créer une liste chaînée de poids
listPoids creerListePoids(int nombreEntrees) {
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
Neurone* InitNeur(int nombreEntrees) {
    int biais;

    // Créer la liste chaînée des poids
    Poids* listePoids = creerListePoids(nombreEntrees);

    // Demander à l'utilisateur le biais
    printf("Entrez le biais : ");
    scanf("%d", &biais);

    // Créer le neurone avec la liste chaînée de poids et le biais
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    neurone->biais = biais;
    neurone->listePoids = listePoids; // Liste chaînée de poids fournie
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


// Fonction pour afficher tous les neurones d'une couche
void afficherCouche(Couche* couche) {
    if (couche == NULL || couche->listeNeurones == NULL) {
        printf("La couche est vide.\n");
        return;
    }

    Neurone* courant = couche->listeNeurones;
    int index = 1;

    printf("Affichage des neurones de la couche :\n");
    while (courant != NULL) {
        printf("Neurone %d :\n", index++);
        afficherNeurone(courant); // Réutilisation de la fonction afficherNeurone
        courant = courant->suivant;
    }
}



int Outneurone(Neurone* neurone, Entrée* entrees) {
    if (neurone == NULL || entrees == NULL) {
        printf("Erreur : Neurone ou liste d'entrées invalide.\n");
        return -1; // Code d'erreur
    }

    int somme = 0; // Initialisation de la somme pondérée
    Poids* courantPoids = neurone->listePoids;
    Entrée* courantEntree = entrees;

    // Calcul de x = ∑(w_i * e_i)
    while (courantPoids != NULL && courantEntree != NULL) {
        somme += courantPoids->valeur * courantEntree->valeur; // Ajout pondéré
        courantPoids = courantPoids->suivant;  // Passer au poids suivant
        courantEntree = courantEntree->suivant;  // Passer à l'entrée suivante
    }

    // Comparer avec le seuil (biais)
    if (somme >= neurone->biais) {
        return 1; // Sortie activée (1)
    } else {
        return 0; // Sortie non activée (0)
    }
}



Couche* InitCouche(int nombreNeurones, int nombreEntrees) {
    Couche* nouvelleCouche = (Couche*)malloc(sizeof(Couche));
    nouvelleCouche->listeNeurones = NULL;
    nouvelleCouche->suivant = NULL;

    Neurone* courant = NULL;

    for (int i = 0; i < nombreNeurones; i++) {
        printf("Initialisation du neurone %d de la couche :\n", i + 1);

        // Créer un neurone en passant le nombre d'entrées comme paramètre
        Neurone* nouveauNeurone = InitNeur(nombreEntrees);

        if (nouvelleCouche->listeNeurones == NULL) {
            nouvelleCouche->listeNeurones = nouveauNeurone;
        } else {
            courant->suivant = nouveauNeurone;
        }
        courant = nouveauNeurone;
    }

    return nouvelleCouche;
}


// Fonction pour calculer la liste des sorties d'une couche

Entrée* Outcouche(Couche* couche, Entrée* entrees) {
    if (couche == NULL || couche->listeNeurones == NULL || entrees == NULL) {
        printf("Erreur : Couche ou liste d'entrées invalide.\n");
        return NULL;
    }

    Entrée* listeSorties = NULL; // Tête de la liste des sorties
    Entrée* courantSorties = NULL;

    Neurone* courantNeurone = couche->listeNeurones;

    while (courantNeurone != NULL) {
        // Calculer la sortie du neurone courant
        int sortie = Outneurone(courantNeurone, entrees);

        // Créer une nouvelle entrée pour représenter la sortie
        Entrée* nouvelleSortie = creerEntree(sortie);

        // Ajouter cette sortie à la liste des sorties
        if (listeSorties == NULL) {
            listeSorties = nouvelleSortie; // Première sortie
        } else {
            courantSorties->suivant = nouvelleSortie; // Ajouter à la fin
        }

        courantSorties = nouvelleSortie; // Avancer le pointeur de la liste des sorties
        courantNeurone = courantNeurone->suivant; // Passer au neurone suivant
    }

    return listeSorties; // Retourner la liste des sorties
}




#endif

