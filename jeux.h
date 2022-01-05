#ifndef JEUX_H
#define JEUX_H

#include "arbre.h"
#include "ia.h"
#include "evaluation.h"

/* Création du plateu avec les 4 pions */
void jeux_init(plateau p);

/* Regarde s'il existe une position possible pour la couleur passée en paramètre */
int jouable(plateau p, int couleur);

/* Indique si une direction est possible (Pour retourner les pions */
int est_direction_possible(plateau p, int x, int y, int dir, int couleur);

/* Fonction auxilliaire de capture de pions */
int capturer_pion(plateau p, int x, int y, int dir, int couleur);

/* Capture des pions */
int capture(plateau p, int x, int y, int couleur);

/* Indique si le coup est valide ou non */
int coup_valide(plateau p, int x, int y, int couleur);

#endif

