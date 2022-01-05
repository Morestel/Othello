#include "ia.h"
#include <MLV/MLV_all.h>
#include <unistd.h> /* Pour la gestion des options en arguments */

void niveau_zero(){
  plateau p;
  int x, y;
  int nb_noirs;
  int nb_blancs;
  plateau_init(p);
  jeu_affich(p, &nb_noirs, &nb_blancs);
  plateau_affich(p);
  plateau_config(p);
  while(1){
    MLV_actualise_window();
    if(jouable(p,NOIR) || jouable(p,BLANC)){
      if(jouable(p,NOIR)){
	printf("\nJOUEUR\n");
	do{
	  if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
	    MLV_get_mouse_position(&x, &y);
	    x = (x - posX) / 50;
	    y = (y - posY) /50;
	  }
	}while(!coup_valide(p, x, y, NOIR));
	capture(p, x, y, NOIR);
	plateau_config(p);
      }
  
      if(jouable(p,BLANC)){
	printf("\nIA\n");
	ia_aleatoire(p);
	plateau_config(p);
      }
      
      jeu_affich(p, &nb_noirs, &nb_blancs);
      plateau_affich(p);
    }
    else
      resultat_partie(&nb_noirs, &nb_blancs);
  }
}

void niveau_un_deux_trois(int niveau, int *prof, int prof_globale){
  plateau p;
  int x, y;
  arbre a = arbre_vide();
  int nb_noirs;
  int nb_blancs;
 /* Par défaut, la profondeur est de 5 pour les niveaux 2 et 3 et de 2 pour le niveau 1 */
  /* Si l'utilisateur a entré une profondeur, on la modifie dans le fichier ia.c */
  if(prof_globale != -1)
    modifier_prof(prof_globale);
  /* Niveau 1: L'IA utilise une profondeur d'arbre de 2 */
  if(niveau == 1)
    modifier_prof(2);
  /* Crée un plateau et l'initialise à la configuration de base*/
  plateau_init(p);
  jeu_affich(p, &nb_noirs, &nb_blancs);
  plateau_affich(p);
  plateau_config(p);
  
  /*Tant qu'au moins un des joueurs peut jouer*/
  while(1){
    MLV_actualise_window();
    if(jouable(p,NOIR) || jouable(p,BLANC)){
    /*Si les pions ont des positions valident*/
      if(jouable(p,NOIR)){
	/*Le tour continue jusqu'à une position valide*/
	printf("\nJOUEUR\n");
	  do{
	    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED){
	      MLV_get_mouse_position(&x, &y);
	      x = (x - posX) / 50;
	      y = (y - posY) / 50;
	    }
	  }while(!coup_valide(p,x,y,NOIR));
	  
	  /*Si le coup est valide, on capture les pions, on affiche le plateau et c'est au joueur suivant de jouer*/
	  capture(p, x, y, NOIR);
	  plateau_config(p);
	}
      
      if(jouable(p,BLANC)){
	printf("\nIA\n");
	a = ia_arbre(p, niveau, prof);
	coup_ordinateur(a, p, niveau, prof);
	free(a);
	plateau_config(p);
      }
      jeu_affich(p, &nb_noirs, &nb_blancs);
      plateau_affich(p);
    }
    
    else
      resultat_partie(&nb_noirs, &nb_blancs);
  }
}

void usage(char *s){
  printf("Usage: %s   Paramètres: \n -niveau <entier entre 0 et 3 (inclu)>\n [OPTIONNEL] -prof <entier positif> \n", s);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
  MLV_create_window("Reversi","Reversi", win_width, win_height);
  MLV_init_audio();
  int niveau;
  int profondeur = 0;
  int *prof = &profondeur;
  int prof_globale = -1;
  /*MLV_Music* music= MLV_load_music("musique/astronomia.mp3");
    MLV_play_music(music, 0.01, -1);*/

  /* Vérifications des paramètres */
  if (argc != 3 && argc != 5){
    usage(argv[0]);
  }
  
  if (strcmp(argv[1], "-niveau") < 0)
    usage(argv[0]);
  
  niveau = atoi(argv[2]);
  if (niveau < 0 || niveau > 4)
    usage(argv[0]);
  
  if (argc == 5){
    if (strcmp(argv[3], "-prof") < 0)
      usage(argv[0]);
    prof_globale = atoi(argv[4]);
    if (prof_globale < 0)
      usage(argv[0]);
  }

  
  
  if (niveau == 0)
    niveau_zero();
  else
    niveau_un_deux_trois(niveau, prof, prof_globale);

  /*MLV_free_audio();*/
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
