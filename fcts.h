#ifndef neuron
#define neuron

#include <stdlib.h>
#include <stdio.h>

typedef struct nodeWeights 
{
    int weight;
    struct nodeWeights *next;
} nodeWeights;

typedef nodeWeights *WList;

typedef struct
{
    WList *head; // La tête de la liste chaînée des poids
    int seuil;        // Biais du neurone
    int n;            // Nombre d'entrées
} neuron;



#endif