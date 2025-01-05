#include <stdio.h>
#include <stdlib.h>
#include "reseau.h"

int main() {





    /** 
    
    // Créer une couche avec 3 neurones, chacun ayant 2 Entrees                                                  TEST AVEC JUSTE LES COUCHES
    Couche* maCouche = InitCouche(2, 1);

    // Créer une liste chaînée d'Entrees
    Entree* mesEntrees = creerListeEntrees(1); // Deux Entrees, e.g., {1, 0}

    // Calculer les sorties de la couche
    Entree* sorties = Outcouche(maCouche, mesEntrees);

    // Afficher les sorties
    printf("Sorties de la couche : ");
    afficherListeEntrees(sorties);

    freeListeEntree(mesEntrees);
    freeListeCouches(Couche);
    free(sorties);

    */








    /** 
   

    Neurone* Node=InitNeur(2);                           //TEST AVEC JUSTE LES NEURONES
    Entree* entry=creerListeEntrees(2);
    afficherNeurone(Node);
    printf("\n%i",Outneurone(Node,entry));
    
    freeListeEntree(entry);
    freeListeNeurones(Node);

    */




   /** 


    int nbCouches = 2;                                       // RESEAU ENTIER
    int neuronesParCouche[] = {3,2};  
    int entreesPremiereCouche = 3;  

    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    afficherReseau(reseau);

    Entree* entreesInitiales = creerListeEntrees(entreesPremiereCouche);  
    printf("Entree du réseau : ");
    afficherListeEntrees(entreesInitiales);

    Entree* sortieReseau = OutReseau(reseau, entreesInitiales);
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);

    freeListeEntree(entreesInitiales);
    freeReseau(reseau);
    free(sortieReseau);

    
    */


















   /** 




    int nbCouches = 1;                                   // RESEAU ET
    int neuronesParCouche[] = {1};  
    int entreesPremiereCouche = 3;  

    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    afficherReseau(reseau);

    Entree* entreesInitiales = creerListeEntrees(entreesPremiereCouche);  
    printf("Entree du réseau : ");
    afficherListeEntrees(entreesInitiales);

    Entree* sortieReseau = OutReseau(reseau, entreesInitiales);
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);

    freeListeEntree(entreesInitiales);
    freeReseau(reseau);
    free(sortieReseau);
    
    */  







   /** 


    int nbCouches = 1;                                   // RESEAU OU
    int neuronesParCouche[] = {1};  
    int entreesPremiereCouche = 3;  

    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    afficherReseau(reseau);

    Entree* entreesInitiales = creerListeEntrees(entreesPremiereCouche);  
    printf("Entree du réseau : ");
    afficherListeEntrees(entreesInitiales);

    Entree* sortieReseau = OutReseau(reseau, entreesInitiales);
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);

    freeListeEntree(entreesInitiales);
    freeReseau(reseau);
    free(sortieReseau);

    */






    /** 

    int nbCouches = 1;                                   // RESEAU NOT
    int neuronesParCouche[] = {1};  
    int entreesPremiereCouche = 1;  

    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    afficherReseau(reseau);

    Entree* entreesInitiales = creerListeEntrees(entreesPremiereCouche);  
    printf("Entree du réseau : ");
    afficherListeEntrees(entreesInitiales);

    Entree* sortieReseau = OutReseau(reseau, entreesInitiales);
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);

    freeListeEntree(entreesInitiales);
    freeReseau(reseau);
    free(sortieReseau);

    */



   /** 

    int nbCouches = 3;                                   // RESEAU MULTI COUCHE [A ET (NON B) ET C] OU [A ET (NON C)]
    int neuronesParCouche[] = {5,2,1};  
    int entreesPremiereCouche = 3;  

    Reseau* reseau = CreerResNeur(nbCouches, neuronesParCouche, entreesPremiereCouche);

    afficherReseau(reseau);

    Entree* entreesInitiales = creerListeEntrees(entreesPremiereCouche);  
    printf("Entree du réseau : ");
    afficherListeEntrees(entreesInitiales);

    Entree* sortieReseau = OutReseau(reseau, entreesInitiales);
    printf("Sortie du réseau : ");
    afficherListeEntrees(sortieReseau);

    freeListeEntree(entreesInitiales);
    freeReseau(reseau);    
    free(sortieReseau);

    */



    return 0;
}
