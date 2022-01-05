#ifndef _EVALUATION_H
#define _EVALUATION_H

#include "jeux.h"

/* Créée un arbre utilisé par l'IA */
arbre evaluation_plateau(plateau p,int x, int y, int couleur, int *prof, int niveau);

/* Compte le nombre de pions consécutifs */
int pions_consecutifs(plateau p, int couleur);

/* Calcul du score de mobilité */
float mobilite(plateau p, int couleur);

/* Quantifie la mobilité en point */
int quantificateur_mobi(plateau p, int couleur);

/* Compte le nombre de point définitif */
int definitif(plateau p, int couleur);

/* Regarde si des pions sont placés en zone de grand danger (Càd que l'adversaire pourra avoir un coin au prochain tour) */
int est_suicidaire(plateau p, int couleur);



#endif
