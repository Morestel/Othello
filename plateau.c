#include "plateau.h"
#include <MLV/MLV_all.h>
#include "jeux.h"
#include <string.h>

/* Initialisation du plateau*/
void plateau_init(plateau p){
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      if((i==3 && j==3) || (i==4 && j==4)){
	p[i][j]=BLANC;
      }
      else if((i==3 && j==4) || (i==4 && j==3)){
	p[i][j] = NOIR; /* On met vide à chaque case du tableau */
      }
      else{
	p[i][j]=VIDE;
      }
    }
  }
}

/* On fait l'affichage en terminal et sur MLV dans une seule fonction */
void plateau_config(plateau p){
  int i, j;
  printf("    A B C D E F G H \n"); /* Coordonnée */
  printf("   ---------------- \n"); /* Bord supérieur du plateau */
  for(j=0;j<8;j++){
    printf("%d |",j+1);
    for(i=0;i<8;i++){
      /* Si on a un coup valide on met "*" */
      if (coup_valide(p, i, j, NOIR) == 1){
	printf(" *");
      }
      /* Si vide on affiche un . */
      else if (p[i][j] == VIDE){
	printf(" .");
      }
      /* Si la case appartient aux noirs, on affiche N */
      if(p[i][j] == NOIR){
	printf(" N");
      }
      /* Si la case appartient aux blancs, on met B en terminal ou un rond blanc sur MLV */
      if(p[i][j] == BLANC){
	printf(" B");
      }
    }
    printf("|\n");
  }
  printf("   ---------------- \n"); /* Bord inférieur du plateau */
}

void plateau_affich(plateau p){
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      /* Si le coup est valide on affiche un cercle*/
      if (coup_valide(p, i, j, NOIR) == 1){
	MLV_draw_circle(i*wd_case+wd_case/2 + posX, j*hei_case+hei_case/2 + posY, radius_pions, MLV_rgba(0, 242, 80, MLV_ALPHA_OPAQUE));
	MLV_draw_circle(i*wd_case+wd_case/2 + posX, j*hei_case+hei_case/2 + posY, radius_pions-1, MLV_rgba(0, 242, 80, MLV_ALPHA_OPAQUE));/*Pour que le trait ait 2px de largeur*/
      }
      /* Si la case appartient aux noirs, on met un pion noir dans la case */
      if(p[i][j] == NOIR){
	MLV_draw_filled_circle(i*wd_case+wd_case/2 + posX,j*hei_case+hei_case/2 + posY,radius_pions,MLV_COLOR_BLACK);
      }
      /* Si la case appartient aux blancs, on met un pion blanc dans la case */
      if(p[i][j] == BLANC){
	MLV_draw_filled_circle(i*wd_case+wd_case/2 + posX,j*hei_case+hei_case/2 + posY,radius_pions,MLV_COLOR_WHITE);
      }
    }
  }
}

void jeu_affich(plateau p,int *nb_n, int *nb_b){
  int i,j,nb_noirs,nb_blancs;
  char coordonneesX[2] = {' ','\0'};
  char coordonneesY[2] = {' ','\0'};
  char pions_noirs[19];
  char pions_blancs[19];
  compte_pions(p,nb_n,nb_b);
  nb_noirs = *nb_n;
  nb_blancs = *nb_b;
  snprintf(pions_noirs, 19,  "Pions noirs :  %d", nb_noirs);
  snprintf(pions_blancs, 19, "Pions blancs : %d", nb_blancs);
  MLV_clear_window(MLV_COLOR_BLACK);
  MLV_draw_rectangle(500, posY, 250, 200, MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));/* Cadres des scores */
  MLV_draw_text(600, 10+posY, "SCORE", MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));/* Titre reversi */
  MLV_draw_text(510, 50+posY, pions_noirs, MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));/* Affichage du nombre de pions noirs */
  MLV_draw_text(510, 70+posY, pions_blancs, MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));/* Affichage du nombre de pions blancs */
  for(i=0;i<8;i++){
    /* Affichage des coordonnées */
    coordonneesX[0]='A'+i;
    MLV_draw_text(i * wd_case + wd_case/2 + posX, 10 + hei_case/2, coordonneesX, MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));
    coordonneesY[0]='1'+i;
    MLV_draw_text(10 + wd_case/2, i*hei_case + hei_case/2 + posY, coordonneesY, MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));
    
    for(j=0;j<8;j++){
      /* Damier du plateau */
      if((i+j)%2 == 0){
	MLV_draw_filled_rectangle(i*wd_case + posX, j*hei_case + posY, wd_case, hei_case, MLV_rgba(0, 186, 59, MLV_ALPHA_OPAQUE));
      }
      else{
	MLV_draw_filled_rectangle(i*wd_case + posX, j*hei_case + posY, wd_case, hei_case, MLV_rgba(0, 122, 39, MLV_ALPHA_OPAQUE));
      }
    }
  }
  MLV_draw_rectangle(posX, posY, 400, 400, MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));/*Cadre doré*/
  MLV_draw_text(700,500,"© 13NRV Corp", MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));
}

void plateau_recopie(plateau p, plateau cp){
  int i,j;
  for(i=0;i<8;i++){ /* On recopie toutes les cases une à une dans le plateau cp */
    for(j=0;j<8;j++)
      cp[i][j] = p[i][j];
  }
}

void resultat_partie(int *nb_n,int *nb_b){
  if(*nb_n < *nb_b){
    MLV_draw_text(585,200,"IA a gagné !",MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));
  }
  else if(*nb_n > *nb_b){
    MLV_draw_text(570,200,"Joueur a gagné !",MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));
  }
  else if(*nb_n == *nb_b){
    MLV_draw_text(590,200,"Égalité !",MLV_rgba(237, 177, 12, MLV_ALPHA_OPAQUE));
  }
}
