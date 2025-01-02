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
Couche InitCouche(int nbNeurones, int nbEntrees, int **poids, int *seuils) 
{
    Couche c;
    c.nbNeurones = nbNeurones;
    c.listeNeurones = (Neurone **)malloc(nbNeurones * sizeof(Neurone *));
    for (int i = 0; i < nbNeurones; i++) {
        c.listeNeurones[i] = InitNeur(poids[i], nbEntrees, seuils[i]);
    }
    return c;
}

int* OutCouche(Couche couche, int *entrees, int taille) 
{
    int *sorties = (int *)malloc(couche.nbNeurones * sizeof(int));
    if (sorties == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(1);
    }

    for (int i = 0; i < couche.nbNeurones; i++) {
        sorties[i] = OutNeurone(couche.listeNeurones[i], entrees, taille);
    }

    return sorties;
}












int main() 
{
    int nbEntrees = 2; 
    int nbNeurones = 2;

    int poidsNeurone1[] = {2, -1};
    int poidsNeurone2[] = {-1, 2};
    int* poids[] = {poidsNeurone1, poidsNeurone2}; 
    int biais[] = {1, 1}; 

    
    int entrees[] = {1, 0};

    
    Couche couche = InitCouche(nbNeurones, nbEntrees, poids, biais);

    
    printf("Sorties de la couche :\n");
    for (int i = 0; i < nbNeurones; i++) 
    {
        int sortie = OutNeurone(couche.listeNeurones[i], entrees, nbEntrees);
        printf("Sortie du neurone %d : %d\n", i + 1, sortie);
    }

    
    for (int i = 0; i < nbNeurones; i++) {
        Poids* courant = couche.listeNeurones[i]->listePoids;
        while (courant != NULL) {
            Poids* temp = courant;
            courant = courant->suivant;
            free(temp);
        }
        free(couche.listeNeurones[i]);
    }
    free(couche.listeNeurones);

    return 0;
}
