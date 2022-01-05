#ifndef ARBRE_H
#define ARBRE_H

#include "plateau.h"
/* Création de la structure arbre */
typedef struct noeud{
    plateau position;
    int valeur_plateau;
    int nb_fils;
    struct noeud **tab_fils;
}noeud;
typedef noeud *arbre;

/* Renvoie un arbre vide */
arbre arbre_vide();
/* Création d'un arbre des possibilités de placement en prenant en compte le plateau actuel */
arbre creer_arbre_position(plateau p);
/* Insertion de fils */
void inserer_fils(arbre a,int num_fils,arbre fils);

#endif
