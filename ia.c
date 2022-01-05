#include "ia.h"
#include <time.h>
#include <math.h>

/* Variable globale qui est égal à 5 de base */
int prof_globale = 5;

/* Fonction pour modifier cette variable globale */
void modifier_prof(int prof){
  prof_globale = prof;
}

/* L'IA joue aléatoirement */
void ia_aleatoire(plateau p){
  int x, y;
    
    /* Tant qu'un coup n'est pas valide on recommence */
  do{
    x = rand() % 8;
    y = rand() % 8;
  }while(!coup_valide(p, x, y, BLANC));
  /* On a trouvé un coup valide, on capture */
  capture(p, x, y, BLANC);
}

/* Création d'un arbre des possibilités */
arbre ia_arbre(plateau p, int niveau, int *prof){
    arbre a = arbre_vide();
    plateau tmp;
    int i, j, num_fils=0;
    int couleur;
 
    a = creer_arbre_position(p);
    if(*prof <= prof_globale){
      /* On ne souhaite pas modifier le plateau donc on en fait un temporaire */
      plateau_recopie(p,tmp);
      /* Changement de couleur en fonction de la profondeur d'arbre */
      if(*prof % 2 == 0)
	couleur = BLANC;
      else
	couleur = NOIR;
      
      /* On crée un fils pour chaque coup possible */
      if (jouable(tmp, couleur)){
	for(i=0; i<8; i++){
	  for(j=0; j<8; j++){
	    if(coup_valide(tmp,i,j,couleur)){
	      inserer_fils(a, num_fils, evaluation_plateau(tmp, i, j, couleur, prof, niveau));
	      /* Une fois que toutes les solutions ont été explorées on baisse la profondeur */
	      *prof -= 1;
	      num_fils++;
	    }
	  }
	}
      }
    }
    return a;
}

int min_max(arbre a, int prof){
  int i, score = 0, min, max;
  if (prof == 0 || a->nb_fils == 0)
    return score;
  
  if (prof % 2 == 0){
    score = -15;
    for (i = 0; i<a->nb_fils; i++){
      min = min_max(a->tab_fils[i], prof - 1);
      if (min > score)
	score = min;
    }
  }
  else{
    score = 100;
    for (i = 0; i<a->nb_fils; i++){
      max = min_max(a->tab_fils[i], prof - 1);
      if (max < score)
	score = max;
    }
  }
  return score;
}


void coup_ordinateur(arbre a, plateau p, int niveau, int *prof){
  int i = 0;
  int profondeur = *prof;
  /* Niveau 1 à 2: */
  if(niveau == 1 || niveau == 2)
    a->valeur_plateau = min_max(a, profondeur);
  
  if(niveau == 3 || niveau == 4)
    a->valeur_plateau = alphabeta(a, profondeur, -300, 300);
  
  /* On met par défaut le premier fils sinon si la valeur du plateau du fils est toujours inférieur au plateau actuel (C'est-à-dire que l'IA va forcémment perdre / être en mauvaise posture) alors elle ne jouera aucun coup (Spoil: Ce n'est pas ce qu'on veut) */
  plateau_recopie(a->tab_fils[i]->position, p);
  
  /* Ensuite on explore tous les fils en regardant lequel donne le plus de points */
  while (i < a->nb_fils){
    if (a->tab_fils[i]->valeur_plateau >= a->valeur_plateau)
      plateau_recopie(a->tab_fils[i]->position, p);
    i++;
    }
}

int alphabeta(arbre a, int prof, int alpha, int beta){
  int i;
  int score;

  /* Si on est sur une feuille ou que la profondeur = 0 ou moins on renvoie la valeur du plateau */
  if (a->nb_fils == 0 || prof < 0)
    return a->valeur_plateau;

  /* Profondeur pair: A l'IA de jouer */
  if (prof % 2 == 0){
    for (i = 0; i < a->nb_fils; i++){
      score = alphabeta(a->tab_fils[i], prof - 1, alpha, beta);
      if (score > alpha){
	alpha = score;
	if (alpha >= beta)
	  break;
      }
    }
    return alpha;
  }
  /* Profondeur Impair: Au joueur de jouer */
  else{
    for (i = 0; i < a->nb_fils; i++){
      score = alphabeta(a->tab_fils[i], prof - 1, alpha, beta);
      if (score < beta){
	beta = score;
	if (alpha >= beta)
	  break;
      }
    }
    return beta;
  }
}
  
