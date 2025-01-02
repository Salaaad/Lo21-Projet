#include <stdio.h>
#include <stdlib.h>

typedef struct Poids {
    int valeur;
    struct Poids* suivant;
} Poids;

typedef struct Neurone {
    Poids* listePoids;
    int biais;
    struct Neurone* suivant;
} Neurone;

typedef struct Couche {
    Neurone* listeNeurones;
    struct Couche* suivant;
} Couche;

// doute car reseau a une suite ou c'est un seul reseau ?
typedef struct Reseau {
    Couche* listeCouches;
} Reseau;


Poids* CreerListePoids(int* poids, int taille) 
{
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


Neurone* InitNeur(int* poids, int nombreEntrees, int biais) 
{
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    neurone->listePoids = CreerListePoids(poids, nombreEntrees);
    neurone->biais = biais;
    neurone->suivant = NULL;
    return neurone;
}


int OutNeurone(Neurone* neurone, int* entrees, int taille) 
{
    int somme = 0;
    Poids* courant = neurone->listePoids;
    for (int i = 0; i < taille; i++) {
        somme += courant->valeur * entrees[i];
        courant = courant->suivant;
    }
    return (somme >= neurone->biais) ? 1 : 0;
}


Couche* InitCouche(int nbNeurones, int nbEntrees, int** poids, int* biais) 
{
    Couche* couche = (Couche*)malloc(sizeof(Couche));
    couche->listeNeurones = NULL;
    couche->suivant = NULL;

    Neurone* dernier = NULL;
    for (int i = 0; i < nbNeurones; i++) {
        Neurone* nouveauNeurone = InitNeur(poids[i], nbEntrees, biais[i]);
        if (!couche->listeNeurones) {
            couche->listeNeurones = nouveauNeurone;
        } else {
            dernier->suivant = nouveauNeurone;
        }
        dernier = nouveauNeurone;
    }
    return couche;
}


int* OutCouche(Couche* couche, int* entrees, int taille) 
{
    int nbNeurones = 0;
    Neurone* courant = couche->listeNeurones;
    while (courant) {
        nbNeurones++;
        courant = courant->suivant;
    }

    int* sorties = (int*)malloc(nbNeurones * sizeof(int));
    if (!sorties) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    int i = 0;
    courant = couche->listeNeurones;
    while (courant) {
        sorties[i++] = OutNeurone(courant, entrees, taille);
        courant = courant->suivant;
    }
    return sorties;
}


int main() {
    int nbEntrees = 2;
    int nbNeurones = 2;

    int poidsNeurone1[] = {2, -1};
    int poidsNeurone2[] = {-1, 2};
    int* poids[] = {poidsNeurone1, poidsNeurone2};
    int biais[] = {1, 1};

    int entrees[] = {1, 0};

    Couche* couche = InitCouche(nbNeurones, nbEntrees, poids, biais);

    printf("Sorties de la couche :\n");
    int* sorties = OutCouche(couche, entrees, nbEntrees);
    for (int i = 0; i < nbNeurones; i++) {
        printf("Sortie du neurone %d : %d\n", i + 1, sorties[i]);
    }

    free(sorties);

    
    Neurone* courantNeurone = couche->listeNeurones;
    while (courantNeurone) {
        Poids* courantPoids = courantNeurone->listePoids;
        while (courantPoids) {
            Poids* tempPoids = courantPoids;
            courantPoids = courantPoids->suivant;
            free(tempPoids);
        }
        Neurone* tempNeurone = courantNeurone;
        courantNeurone = courantNeurone->suivant;
        free(tempNeurone);
    }
    free(couche);

    return 0;
}
