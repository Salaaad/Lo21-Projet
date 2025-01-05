# Chiem Romain et Desmaret Mathéo #Rapport LO21 « Réseaux de neurones »


## Table des matières
1. [Choix de conception et d’implémentation](#choix-de-conception-et-dimplémentation) 1  
   - Liste chaînée pour les poids : 1  
   - Structure pour le neurone : 1  
   - Liste dynamique pour les neurones dans une couche : 2  
   - Structure pour le réseau : 2  
   - Démarche adoptée : 2  
2. [Algorithmes et explications](#algorithmes-et-explications) 2  
   - Création d’une liste de poids : 2  
   - Calcul de la sortie d’un neurone : 2  
   - Initialisation d’une couche : 2  
   - Calcul de la sortie d’une couche : 3  
3. [Jeux d’essais](#jeux-dessais) 3  
   - Une seule couche avec deux neurones : 3  
   - Deux couches connectées : 3  
4. [Commentaires sur les résultats](#commentaires-sur-les-résultats) 3

## 1. Choix de conception et d’implémentation

### Liste chaînée pour les poids :
- Chaque neurone possède une liste chaînée de poids. Ce choix permet une gestion dynamique et extensible des poids sans besoin de donner leurs nombres à l’avance.
- La liste chaînée est idéale car les poids peuvent être ajoutés ou supprimés dynamiquement.

### Structure pour le neurone :
- Un neurone contient une liste de poids et un biais, regroupant ainsi toutes les informations pour le calcul de sa sortie.

### Liste dynamique pour les neurones dans une couche :
- Les couches sont représentées par une liste de neurones. Ce choix permet de gérer facilement un nombre variable de neurones dans chaque couche.

### Structure pour le réseau :
- Le réseau est organisé en une liste chaînée de couches, ce qui permet une construction simple et pratique des couches du réseau.

### Démarche adoptée
- Chaque composant (poids, neurone, couche, réseau) est conçu séparément pour respecter le principe de modularité.
- Les fonctions sont conçues pour être réutilisables et flexibles, par exemple en utilisant des paramètres tels que le nombre d’entrées ou les biais.

## 2. Les Algorithmes 

Fonction CreerListePoids (nombreEntrees: entier strict positif):liste<Poids>

Début

    listePoids <- créerListeVide()
    courant <- CreerListeVide()

    Pour i allant de 1 à nombreEntrees faire :
        poids<- (UserEntry)
        nouveauPoids<-CréerPoidsVide()
        nouveauPoids.poids<-poids
        Si listePoids == NULL faire 
            listePoids <- nouveauPoids
        Sinon 
            courant.suivant <- nouveauPoids
        courant <- nouveauPoids
        Fin Si
    Fin Pour


    CreerListePoids <- listePoids

Fin


Fonction InitNeur (nombreEntrees: entier strict positif): Neurone

Début

    biais <- (UserEntry)
    listePoids <- CreerListePoids(nombreEntrees)

    neurone <- CréerNeuroneVide()
    neurone.biais <- biais
    neurone.listePoids <- listePoids
    neurone.suivant <- NULL

    InitNeur <- neurone

Fin





Fonction OutNeurone (neurone: Neurone, entrees: Liste<entrée:entier>): entier

Début

    Si neurone == NULL ou entrees == NULL faire
        Afficher("Erreur : Neurone ou liste d'entrées invalide.")
        OutNeurone<- ERREUR
    Fin Si

    somme <- 0
    courantPoids <- neurone.listePoids
    courantEntree <- entrees

    Tant que courantPoids != NULL et courantEntree != NULL faire
        somme <- somme + courantPoids.poids * courantEntree.valeur
        courantPoids <- courantPoids.suivant
        courantEntree <- courantEntree.suivant
    Fin Tant Que

    Si somme >= neurone.seuil faire
        OutNeurone<-1
    Sinon
        OutNeurone<-0
    Fin Si

Fin




Fonction InitCouche (nombreNeurones: entier strict positif, nombreEntrees: entier strict positif): Couche

Début

    nouvelleCouche <- CréerCoucheVide()
    nouvelleCouche.listeNeurones <- NULL
    nouvelleCouche.suivant <- NULL
    
    courant <- NULL
    
    Pour i allant de 1 à nombreNeurones faire
        Afficher "Initialisation du neurone " + i + " de la couche :"
        
        nouveauNeurone <- InitNeur(nombreEntrees)
        
        Si nouvelleCouche.listeNeurones == NULL alors
            nouvelleCouche.listeNeurones <- nouveauNeurone
        Sinon
            courant.suivant <- nouveauNeurone
        Fin Si
        
        courant <- nouveauNeurone
    Fin Pour
    
    InitCouche <- nouvelleCouche

Fin



Fonction Outcouche (couche: Couche, entrees: Liste<entré:entier>): Liste<entrée:entier>

Début

    Si couche == NULL ou couche.listeNeurones == NULL ou entrees == NULL alors
        Afficher "Erreur : Couche ou liste d'entrées invalide."
        Outcouche<- ERROR
    Fin Si

    listeSorties <- CréerListeVide()
    courantSorties <- NULL

    courantNeurone <- couche.listeNeurones

    Tant que courantNeurone != NULL faire
        sortie <- Outneurone(courantNeurone, entrees)

        Si listeSorties == NULL alors
            listeSorties <- nouvelleSortie
        Sinon
            courantSorties.suivant <- nouvelleSortie
        Fin Si

        courantSorties <- nouvelleSortie
        courantNeurone <- courantNeurone.suivant
    Fin Tant Que

    Outcouche<-listeSorties

Fin






Fonction CreerResNeur (nbCouches: entier strict positif, neuronesParCouche: tableau d'entiers, entreesPremiereCouche: entier strict positif): Reseau

Début

    reseau <- CréerRéseauVide(Reseau)
    reseau.premiereCouche <- NULL
    reseau.nbCouches <- nbCouches

    coucheCourante <- NULL
    nbEntrees <- entreesPremiereCouche

    Pour i allant de 0 à nbCouches - 1 faire

        Afficher "Création de la couche " + (i + 1) + " avec " + neuronesParCouche[i] + " neurones..."

        nouvelleCouche <- InitCouche(neuronesParCouche[i], nbEntrees)

        Si reseau.premiereCouche == NULL alors
            reseau.premiereCouche <- nouvelleCouche
        Sinon
            coucheCourante.suivant <- nouvelleCouche
        Fin Si

        coucheCourante <- nouvelleCouche

        nbEntrees <- neuronesParCouche[i]

    Fin Pour

    CréerResNeur <- reseau

Fin


Fonction OutReseau (reseau: Reseau, entreesInitiales: Liste<Entrée:entier>): Liste<Entrée:entier>

Début

    entreesActuelles <- entreesInitiales
    coucheCourante <- reseau.premiereCouche

    Tant que coucheCourante != NULL faire
        entreesActuelles <- Outcouche(coucheCourante, entreesActuelles)
        coucheCourante <- coucheCourante.suivant
    Fin Tant que

    OutReseau <- entreesActuelles

Fin



Fonction afficherListeEntrees (listeEntrees: Liste<Entrée>)

Début

    courant <- listeEntrees
    Tant que courant != NULL faire
        Afficher courant.valeur
        courant <- courant.suivant
    Fin Tant que

    Afficher "\n"

Fin



Fonction AfficherNeurone (neurone: Neurone)

Début

    courant <- neurone.listePoids
    Afficher "Poids : "
    
    Tant que courant != NULL faire
        Afficher courant.poids
        courant <- courant.suivant
    Fin Tant que
    
    Afficher "Biais : " + neurone.biais

Fin


Fonction afficherCouche (couche: Couche)

Début

    Si couche == NULL ou couche.listeNeurones == NULL alors
        Afficher "La couche est vide."
        afficheCouche<-- ERROR
    Fin Si

    courant <- couche.listeNeurones
    index <- 1
    Tant que courant != NULL faire
        Afficher "Neurone " + index + " :"
        afficherNeurone(courant) 
        courant <- courant.suivant
        index <- index + 1
    Fin Tant Que

Fin


Fonction afficherReseau (reseau: Reseau)

Début

    coucheCourante <- reseau.premiereCouche
    indexCouche <- 1

    Tant que coucheCourante != NULL faire
        Afficher "Couche ", indexCouche, ":"
        afficherCouche(coucheCourante)
        coucheCourante <- coucheCourante.suivant
        indexCouche <- indexCouche + 1
    Fin Tant que

Fin

## Explications des algorithmes 
## 1. Fonction `CreerListePoids(nombreEntrees: entier strict positif): liste<Poids>`

- **Entrée :**
  - `nombreEntrees` : Un entier strictement positif représentant le nombre d'entrées pour le neurone.

- **Sortie :**
  - Une liste chaînée de poids (`liste<Poids>`), où chaque élément contient un poids associé à une entrée du neurone.

- **Lexique :**
  - `listePoids` : La liste qui contiendra les poids des entrées.
  - `nouveauPoids` : Un nœud de la liste, contenant un poids.
  - `courant` : Un pointeur permettant de naviguer dans la liste des poids.

---

## 2. Fonction `InitNeur(nombreEntrees: entier strict positif): Neurone`

- **Entrée :**
  - `nombreEntrees` : Un entier strictement positif représentant le nombre d'entrées pour le neurone.

- **Sortie :**
  - Un neurone initialisé (`Neurone`), avec un biais et une liste de poids associée.

- **Lexique :**
  - `biais` : La valeur du biais du neurone, saisie par l'utilisateur.
  - `listePoids` : Liste des poids des entrées, créée par la fonction `CreerListePoids`.
  - `neurone` : Le neurone initialisé, contenant un biais et une liste de poids.

---

## 3. Fonction `OutNeurone(neurone: Neurone, entrees: Liste<entrée:entier>): entier`

- **Entrée :**
  - `neurone` : Le neurone dont on veut calculer la sortie.
  - `entrees` : La liste d'entrées à traiter.

- **Sortie :**
  - Un entier représentant la sortie du neurone, soit `0` ou `1`.

- **Lexique :**
  - `somme` : La somme des produits des poids et des entrées.
  - `courantPoids` : Un pointeur sur les poids du neurone.
  - `courantEntree` : Un pointeur sur les entrées.
  - `seuil` : La valeur seuil qui détermine la sortie (si la somme est supérieure ou égale au seuil, la sortie est `1`).

---

## 4. Fonction `InitCouche(nombreNeurones: entier strict positif, nombreEntrees: entier strict positif): Couche`

- **Entrée :**
  - `nombreNeurones` : Un entier strictement positif représentant le nombre de neurones dans la couche.
  - `nombreEntrees` : Un entier représentant le nombre d'entrées pour chaque neurone.

- **Sortie :**
  - Une couche de neurones (`Couche`), qui contient les neurones initialisés.

- **Lexique :**
  - `nouvelleCouche` : La couche créée.
  - `courant` : Un pointeur qui permet de relier les neurones entre eux dans la couche.
  - `nouveauNeurone` : Un neurone créé pour la couche, initialisé avec les entrées spécifiées.

---

## 5. Fonction `Outcouche(couche: Couche, entrees: Liste<entrée:entier>): Liste<entrée:entier>`

- **Entrée :**
  - `couche` : La couche de neurones dont on veut calculer la sortie.
  - `entrees` : La liste des entrées pour cette couche.

- **Sortie :**
  - Une liste d'entiers représentant les sorties des neurones dans la couche.

- **Lexique :**
  - `listeSorties` : Liste des sorties des neurones dans la couche.
  - `courantSorties` : Pointeur pour naviguer et relier les sorties.
  - `courantNeurone` : Pointeur pour naviguer dans la liste des neurones de la couche.

---

## 6. Fonction `CreerResNeur(nbCouches: entier strict positif, neuronesParCouche: tableau d'entiers, entreesPremiereCouche: entier strict positif): Reseau`

- **Entrée :**
  - `nbCouches` : Le nombre de couches dans le réseau.
  - `neuronesParCouche` : Un tableau d'entiers indiquant le nombre de neurones pour chaque couche.
  - `entreesPremiereCouche` : Le nombre d'entrées pour la première couche du réseau.

- **Sortie :**
  - Un réseau de neurones (`Reseau`), composé de plusieurs couches de neurones.

- **Lexique :**
  - `reseau` : Le réseau de neurones créé.
  - `nouvelleCouche` : Une couche de neurones créée pour le réseau.
  - `coucheCourante` : Un pointeur pour naviguer à travers les couches du réseau.
  - `nbEntrees` : Le nombre d'entrées pour chaque couche, mis à jour à chaque itération.

---

## 7. Fonction `OutReseau(reseau: Reseau, entreesInitiales: Liste<Entrée:entier>): Liste<Entrée:entier>`

- **Entrée :**
  - `reseau` : Le réseau de neurones à traiter.
  - `entreesInitiales` : La liste des entrées initiales pour le réseau.

- **Sortie :**
  - La liste des sorties finales du réseau.

- **Lexique :**
  - `entreesActuelles` : La liste d'entrées à chaque étape (met à jour les sorties des couches successives).
  - `coucheCourante` : Un pointeur permettant de naviguer à travers les couches du réseau.

---

## 8. Fonction `afficherListeEntrees(listeEntrees: Liste<Entrée>)`

- **Entrée :**
  - `listeEntrees` : Une liste d'entrées à afficher.

- **Sortie :**
  - Aucune. Cette fonction affiche les valeurs des entrées à l'écran.

- **Lexique :**
  - `courant` : Pointeur permettant de naviguer à travers la liste d'entrées.

---

## 9. Fonction `AfficherNeurone(neurone: Neurone)`

- **Entrée :**
  - `neurone` : Le neurone dont on veut afficher les poids et le biais.

- **Sortie :**
  - Aucune. Cette fonction affiche les poids et le biais du neurone.

- **Lexique :**
  - `courant` : Pointeur permettant de naviguer dans la liste des poids du neurone.

---

## 10. Fonction `afficherCouche(couche: Couche)`

- **Entrée :**
  - `couche` : La couche de neurones à afficher.

- **Sortie :**
  - Aucune. Cette fonction affiche tous les neurones de la couche.

- **Lexique :**
  - `courant` : Pointeur permettant de naviguer à travers les neurones de la couche.
  - `index` : Un compteur pour indiquer l'index du neurone dans la couche.

---

## 11. Fonction `afficherReseau(reseau: Reseau)`

- **Entrée :**
  - `reseau` : Le réseau de neurones à afficher.

- **Sortie :**
  - Aucune. Cette fonction affiche toutes les couches et neurones du réseau.

- **Lexique :**
  - `coucheCourante` : Pointeur permettant de naviguer à travers les couches du réseau.
  - `indexCouche` : Un compteur pour indiquer l'index de la couche dans le réseau.

---

### Résumé du Lexique :
- **Poids** : Valeur qui détermine l'importance d'une entrée pour un neurone.
- **Biais** : Valeur qui ajuste la sortie d'un neurone avant l'application de la fonction d'activation.
- **Seuil** : Valeur utilisée pour décider de la sortie d'un neurone en comparant la somme pondérée des entrées.
- **Couche** : Un groupe de neurones dans le réseau.
- **Reseau** : Un ensemble de couches de neurones connectées entre elles.

Ces fonctions forment un réseau de neurones où chaque neurone reçoit des entrées, les multiplie par des poids et ajoute un biais, puis applique une fonction de seuil pour produire une sortie. Le réseau peut être constitué de plusieurs couches de neurones et est utilisé pour effectuer des prédictions ou classifications basées sur des entrées données.

## 3. Jeux d’essais

### Une seule couche avec deux neurones
- **Entrées** : `1,01`, `01,0`, Poids du premier neurone : `2,−12`, `-12,−1`, Poids du second neurone : `−1,2-1`, `2−1,2`, Biais : 1 pour les deux neurones.
- **Résultat attendu** :
  - Neurone 1 : `(2∗1) +(−1∗0) =2 ≥ 1 ⇒ Sortie : 1`
  - Neurone 2 : `(−1∗1) +(2∗0) =−1 < 1 ⇒ Sortie : 0`
  - Sortie de la couche : `1,01`, `01,0`.

### Deux couches connectées
- **Entrées** : `1,11`, `11,1`, Poids et biais prédéfinis.
- **Résultat attendu** : La sortie de la première couche alimente les entrées de la deuxième couche, permettant une propagation avant complète.

## 4. Commentaires sur les résultats
- Les tests montrent que les algorithmes fonctionnent correctement pour des entrées et poids simples.
- Les résultats des neurones respectent les calculs de sommes pondérées et la comparaison avec le biais.
- L’implémentation est robuste pour des petites structures, mais des optimisations (comme une gestion mémoire efficace) seraient nécessaires pour des réseaux de grande taille.
