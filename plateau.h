#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdio.h>
#include <stdlib.h>

/* Valeur des cases */
#define VIDE 2
#define NOIR 1
#define BLANC 0

/* Taille fenêtre*/
#define win_width 820
#define win_height 520

/*position du tableau*/
#define posX 60
#define posY 60

/* Taille des cases */
#define wd_case 50
#define hei_case 50

/* Taille des pions */
#define radius_pions 20

/* On définie le plateau comme une matrice 8x8 */
typedef int plateau[8][8];

/* Création d'un plateau vide */
void plateau_init(plateau p);

/* Etat actuel du plateau */
void plateau_config(plateau p);

/* Affichage MLV du plateau*/
void plateau_affich(plateau p);

/* Affiche MLV du jeu*/
void jeu_affich(plateau p,int *nb_n, int *nb_b);

/* Recopie du plateau */
void plateau_recopie(plateau p, plateau cp);

/* Affiche le résultat de la partie sur MLV */
void resultat_partie(int *nb_n,int *nb_b);
#endif
