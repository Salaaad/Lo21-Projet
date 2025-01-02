#include <stdio.h>
#include <stdlib.h>

typedef struct Poids {
    int valeur;
    struct Poids* suivant;
} Poids;


typedef struct Neurone {
    Poids* listePoids;
    int biais;
} Neurone;


typedef struct Couche {
    Neurone** listeNeurones;
    int nbNeurones;
    struct Couche* suivant;
} Couche;


typedef struct Reseau {
    Couche* listeCouches;
    int nbCouches;
} Reseau;


Poids* CreerListePoids(int* poids, int taille) {
    Poids* tete = NULL;
    Poids* courant = NULL;
    for (int i = 0; i < taille; i++) {
        Poids* nouveau = (Poids*)malloc(sizeof(Poids));
        nouveau->valeur = poids[i];
        nouveau->suivant = NULL;
        if (!tete) {
            tete = nouveau;
        } else {
            courant->suivant = nouveau;
        }
        courant = nouveau;
    }
    return tete;
}



Neurone* InitNeur(int* poids, int nombreEntrees, int biais) {
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    neurone->listePoids = CreerListePoids(poids, nombreEntrees);
    neurone->biais = biais;
    return neurone;
}

/* 
Opérateur Ternaire :
? et :
Syntaxe : condition ? valeur_si_vrai : valeur_si_faux
Si la condition est vraie (somme ≥ neurone->biais ), retourne 1.
Sinon, retourne 0
*/
int OutNeurone(Neurone* neurone, int* entrees, int taille) {
    int somme = 0;
    Poids* courant = neurone->listePoids;
    for (int i = 0; i < taille; i++) {
        somme += courant->valeur * entrees[i];
        courant = courant->suivant;
    }

    return (somme >= neurone->biais) ? 1 : 0;
}


// On va initialiser une couche donc on prend les élements des neuronnes //
Couche InitCouche(int nbNeurones, int nbEntrees, int **poids, int *seuils) {
    Couche c;
    c.nbNeurones = nbNeurones;
    c.listeNeurones= (Neurone *)malloc(nbNeurones * sizeof(Neurone));
    for (int i = 0; i < nbNeurones; i++) 
    {
        c.listeNeurones[i] = InitNeur(nbEntrees, poids[i], seuils[i]);
    }

    return c;
}


int OutCouche(Couche couche, int *entrees) {
    int *sorties = (int *)malloc(couche.nbNeurones * sizeof(int));
    if (sorties == NULL) 
    {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    for (int i = 0; i < couche.nbNeurones; i++) 
    {
        sorties[i] = OutNeurone(couche.neurones[i], entrees);
    }

    return sorties;
}