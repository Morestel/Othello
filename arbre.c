#include "arbre.h"

/* Création d'un arbre vide */
arbre arbre_vide(){
  return NULL;
}

/* Création d'un arbre à une position donnée (Pour le niveau 4) */
arbre creer_arbre_position(plateau p){
  int i,j;
  arbre a = (arbre)malloc(sizeof(noeud));
  if(a == NULL){ /* Test d'allocation mémoire */
      printf("Erreur d'allocation mémoire\n");
      exit(EXIT_FAILURE);
    }
  
  /* Copie du plateau dans l'arbre */
  for(i=0;i<8;i++){
    for(j=0;j<8;j++)
      a->position[i][j] = p[i][j];
  }
  a->nb_fils = 0;
  a->valeur_plateau = 0;
  a->tab_fils = NULL;
  
  return a;
}

void inserer_fils(arbre a, int num_fils, arbre fils){
  a->nb_fils++;
  a->tab_fils = (arbre *)realloc(a->tab_fils,a->nb_fils*sizeof(arbre));
  if(a->tab_fils == NULL){ /* Test de l'allocation */
    printf("Erreur lors de l'allocation de la mémoire \n");
    exit(EXIT_FAILURE);
  }
  a->tab_fils[num_fils] = fils;
}
