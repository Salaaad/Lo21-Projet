#ifndef neuron
#define neuron

#include <stdlib.h>
#include <stdio.h>

typedef struct Entree {
    int valeur;
    struct Entree* suivant;
} Entree;


typedef Entree* listEntrees;  

typedef struct Poids {
    float valeur;
    struct Poids* suivant;
} Poids;

typedef Poids* listPoids;

typedef struct Neurone {
    listPoids listePoids;
    float biais;
    struct Neurone* suivant;
} Neurone;

typedef struct Neurone* listNeurone;

typedef struct Couche {
    Neurone* listeNeurones; 
    struct Couche* suivant; 
} Couche;

typedef struct Couche* listCouche;


typedef struct Reseau {
    Couche* premiereCouche;  
    int nbCouches;           
} Reseau;





// Fonction pour créer une liste chaînée d'Entrees
listEntrees creerListeEntrees(int nombreEntrees) {
    Entree* listeEntrees = NULL;
    Entree* courant = NULL;

    for (int i = 0; i < nombreEntrees; i++) {
        int entree;
        printf("Entrez l'Entree %i : ", i + 1);
        scanf("%i", &entree);
        
        // Création dynamique de l'Entree
        Entree* nouvelleEntree = (Entree*)malloc(sizeof(Entree));
        nouvelleEntree->valeur = entree;
        nouvelleEntree->suivant = NULL;

        if (listeEntrees == NULL) {
            listeEntrees = nouvelleEntree;  //Si c'est la première Entree ça devient la tête de liste sinon on l'ajoute à la liste
        } else {
            courant->suivant = nouvelleEntree;  
        }
        courant = nouvelleEntree;  
    }

    return listeEntrees;
}


// Fonction pour créer une liste chaînée de poids (même algo que creerListeEntrees)
listPoids creerListePoids(int nombreEntrees) {
    Poids* listePoids = NULL;
    Poids* courant = NULL;

    for (int i = 0; i < nombreEntrees; i++) {
        float poids;
        printf("Entrez le poids %i : ", i + 1);
        scanf("%f", &poids);
        
        Poids* nouveauPoids = (Poids*)malloc(sizeof(Poids));
        nouveauPoids->valeur = poids;  
        nouveauPoids->suivant = NULL;

        if (listePoids == NULL) {
            listePoids = nouveauPoids;  
        } else {
            courant->suivant = nouveauPoids;  
        }
        courant = nouveauPoids;  
    }

    return listePoids;
}


// Fonction pour créer un noeud d'Entree
Entree* creerEntree(int valeur) {
    Entree* nouvelleEntree = (Entree*)malloc(sizeof(Entree));
    nouvelleEntree->valeur = valeur;
    nouvelleEntree->suivant = NULL;
    return nouvelleEntree;
}



// Fonction pour initialiser un neurone avec une liste chaînée de poids et un biais
Neurone* InitNeur(int nombreEntrees) {
    float biais;
 
    Poids* listePoids = creerListePoids(nombreEntrees);
    printf("Entrez le biais : ");
    scanf("%f", &biais);

    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    neurone->biais = biais;
    neurone->listePoids = listePoids; 
    neurone->suivant = NULL;

    return neurone;
}


int Outneurone(Neurone* neurone, Entree* entrees) {
    if (neurone == NULL || entrees == NULL) {
        printf("Erreur : Neurone ou liste d'Entrees invalide.\n");
        return -1; // Code d'erreur
    }

    float somme = 0; 
    Poids* courantPoids = neurone->listePoids;
    Entree* courantEntree = entrees;

    while (courantPoids != NULL && courantEntree != NULL) {
        somme += courantPoids->valeur * courantEntree->valeur; // Calcul à l'aide de la fonction d'activation
        courantPoids = courantPoids->suivant;  // Passer au poids suivant
        courantEntree = courantEntree->suivant;  // Passer à l'Entree suivante
    }

    if (somme >= neurone->biais) {
        return 1; 
    } else {
        return 0; 
    }
}




Couche* InitCouche(int nombreNeurones, int nombreEntrees) {
    Couche* nouvelleCouche = (Couche*)malloc(sizeof(Couche));
    nouvelleCouche->listeNeurones = NULL;
    nouvelleCouche->suivant = NULL;

    Neurone* courant = NULL;

    for (int i = 0; i < nombreNeurones; i++) {
        printf("Initialisation du neurone %i de la couche :\n", i + 1);

        // Créer un neurone en passant le nombre d'Entrees comme paramètre car le neurone autre le même nombre de poids que d'Entree
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

listEntrees Outcouche(Couche* couche, Entree* entrees) {
    if (couche == NULL || couche->listeNeurones == NULL || entrees == NULL) {
        printf("Erreur : Couche ou liste d'Entrees invalide.\n");
        return NULL;
    }

    Entree* listeSorties = NULL; 
    Entree* courantSorties = NULL;

    Neurone* courantNeurone = couche->listeNeurones;

    while (courantNeurone != NULL) {
        
        int sortie = Outneurone(courantNeurone, entrees);
        Entree* nouvelleSortie = creerEntree(sortie);

        // Ajouter cette sortie à la liste des sorties
        if (listeSorties == NULL) {
            listeSorties = nouvelleSortie; 
        } else {
            courantSorties->suivant = nouvelleSortie; 
        }

        courantSorties = nouvelleSortie; 
        courantNeurone = courantNeurone->suivant; // Passer au neurone suivant et la sortie suivante
    }

    return listeSorties; 
}



Reseau* CreerResNeur(int nbCouches, int* neuronesParCouche, int entreesPremiereCouche) {

    Reseau* reseau = (Reseau*)malloc(sizeof(Reseau));
    reseau->premiereCouche = NULL;
    reseau->nbCouches = nbCouches;

    Couche* coucheCourante = NULL;
    int nbEntrees = entreesPremiereCouche;  

    for (int i = 0; i < nbCouches; i++) {

        printf("Création de la couche %i avec %i neurones\n", i + 1, neuronesParCouche[i]);

        Couche* nouvelleCouche = InitCouche(neuronesParCouche[i], nbEntrees);

        if (reseau->premiereCouche == NULL) {
            reseau->premiereCouche = nouvelleCouche;  
        } else {
            coucheCourante->suivant = nouvelleCouche;  
        }

 
        coucheCourante = nouvelleCouche;

        // Le nombre d'Entree de la couche suivante sera le nombre de neurone de la couche précedente
        nbEntrees = neuronesParCouche[i];
    }
    printf("Réseau créé avec succès !\n");
    return reseau;
}

// Fonction pour calculer la sortie du réseau
listEntrees OutReseau(Reseau* reseau, Entree* entreesInitiales) {
    Entree* entreesActuelles = entreesInitiales;  
    Couche* coucheCourante = reseau->premiereCouche;
    
 
    while (coucheCourante != NULL) {
        // Calculer la sortie de la couche courante avec les Entrees actuelles
        // La sortie de cette couche devient l'Entree pour la couche suivante
        entreesActuelles = Outcouche(coucheCourante, entreesActuelles);
        
        coucheCourante = coucheCourante->suivant;
    }

    return entreesActuelles;
}






// Fonction pour afficher une liste chaînée d'Entrees
void afficherListeEntrees(Entree* listeEntrees) {
    Entree* courant = listeEntrees;
    while (courant != NULL) {
        printf("%i ", courant->valeur);  
        courant = courant->suivant;       
    }
    
    printf("\n");  
}

void afficherNeurone(Neurone* neurone) {
    Poids* courant = neurone->listePoids;
    printf("        Poids : ");
    while (courant != NULL) {
        printf("%f ", courant->valeur);
        courant = courant->suivant;
    }
    printf("\n        Biais : %f\n", neurone->biais);

}


// Fonction pour afficher tous les neurones d'une couche
void afficherCouche(Couche* couche) {
    if (couche == NULL || couche->listeNeurones == NULL) {
        printf("La couche est vide.\n");
        return;
    }

    Neurone* courant = couche->listeNeurones;
    int index = 1;
    while (courant != NULL) {
        printf("    Neurone %i :\n", index++);
        afficherNeurone(courant); 
        courant = courant->suivant;
    }
}


// Fonction pour afficher le réseau complet
void afficherReseau(Reseau* reseau) {
    Couche* coucheCourante = reseau->premiereCouche;
    int indexCouche = 1;
    while (coucheCourante != NULL) {
        printf("Couche %i :\n", indexCouche);
        afficherCouche(coucheCourante);  
        coucheCourante = coucheCourante->suivant;
        indexCouche++;
    }
}






void freeListeEntree(listEntrees listEntrees) {
    Entree* courant = listEntrees;
    while (courant != NULL) {
        Entree* suivant = courant->suivant; 
        free(courant);                     
        courant = suivant;                 
    }
}


void freeListePoids(listPoids listePoids) {
    Poids* courant = listePoids;
    while (courant != NULL) {
        Poids* suivant = courant->suivant; 
        free(courant);                     
        courant = suivant;                 
    }
}



void freeListeNeurones(listNeurone listeNeurones) {
    Neurone* courant = listeNeurones;
    while (courant != NULL) {
        Neurone* suivant = courant->suivant; 
        freeListePoids(courant->listePoids); 
        free(courant);                       
        courant = suivant;                   
    }
}

void freeListeCouches(listCouche listeCouches) {
    Couche* courant = listeCouches;
    while (courant != NULL) {
        Couche* suivant = courant->suivant;        
        freeListeNeurones(courant->listeNeurones); 
        free(courant);                              
        courant = suivant;                          
    }
}


void freeReseau(Reseau* reseau) {
    if (reseau == NULL) {
        return; 
    }

    freeListeCouches(reseau->premiereCouche); 
    free(reseau);                             
}





#endif

