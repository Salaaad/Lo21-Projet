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

## 2. Algorithmes et explications

### Création d’une liste de poids
- **Description** : L’algorithme génère une liste chaînée où chaque nœud contient un poids.
- **Objectif** : Permettre une gestion flexible et dynamique des poids d’un neurone.
- **Explication** : Les poids sont créés à partir d’un tableau d’entiers et reliés successivement dans une liste chaînée.

### Calcul de la sortie d’un neurone
- **Description** : L’algorithme effectue une somme pondérée des entrées avec les poids du neurone, compare la somme avec le biais, puis retourne un signal de sortie (0 ou 1).
- **Objectif** : Simuler le fonctionnement d’un neurone dans un réseau neuronal.
- **Explication** : Ce calcul permet d’activer ou non un neurone en fonction de l’intensité des signaux d’entrée.

### Initialisation d’une couche
- **Description** : Chaque neurone de la couche est initialisé avec ses propres poids et biais.
- **Objectif** : Construire une couche contenant plusieurs neurones, chacun indépendant.
- **Explication** : Une boucle est utilisée pour itérer sur les poids et biais, appelant la fonction d’initialisation d’un neurone.

### Calcul de la sortie d’une couche
- **Description** : Les sorties de tous les neurones de la couche sont calculées en parallèle et stockées dans un tableau.
- **Objectif** : Fournir les signaux de sortie d’une couche à une couche suivante.
- **Explication** : Chaque sortie de neurone est calculée individuellement, puis regroupée dans un tableau.

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

