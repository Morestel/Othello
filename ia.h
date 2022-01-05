#ifndef IA_H
#define IA_H

#include "jeux.h"

/* Modification de la profondeur ( Option -p ) */
void modifier_prof(int prof);

/* L'IA jouera de manière aléatoire */
void ia_aleatoire(plateau p);

/* Création d'un arbre des coups possibles */
arbre ia_arbre(plateau p, int niveau, int *prof);

/* L'IA jouera le meilleur coup possible */
void coup_ordinateur(arbre a, plateau p, int niveau, int *prof);

/* Algorithme MinMax suivant l'algorithme présent sur le site de la fédération française d'Othello */
int min_max(arbre a, int prof);

/* Algorithme Alpha-Bêta suivant l'algorithme présent sur le site de la férération française d'Othello */
int alphabeta(arbre a, int prof, int alpha, int beta);

#endif
