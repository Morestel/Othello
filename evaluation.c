#include "evaluation.h"

/* Utilisée par l'ia pour savoir si sa position est favorable */
arbre evaluation_plateau(plateau p, int x, int y, int couleur, int *prof, int niveau){
  arbre a = arbre_vide();
  plateau tmp;
  int points;
  *prof += 1;
  /* Création d'un plateau temporaire */
  plateau_recopie(p,tmp);
  /* Calcul des points à partir de cette position */
  /* Tous les niveaux n'ont pas les mêmes fonctions d'évalutations */
  /* On commence par les points obtenus grâce aux pions retournés */
  points = capture(tmp, x, y, couleur);
  
  if (niveau == 1){ /* On s'arrête là pour le niveau 1 */
    a = ia_arbre(tmp, 1, prof);
    a->valeur_plateau = points;
    return a;
  }
  points += pions_consecutifs(tmp, couleur);
  if (niveau == 2){ /* On s'arrête là pour le niveau 2 */
    a = ia_arbre(tmp, 2, prof);
    a->valeur_plateau = points;
    return a;
  }
  points += definitif(tmp, couleur);
  points += quantificateur_mobi(tmp, couleur);
  points += est_suicidaire(tmp, couleur);
  a = ia_arbre(tmp, 3, prof);
  a->valeur_plateau = points;
  
  return a;
}

int pions_consecutifs(plateau p, int couleur){
  int i, j;
  int pions = 0;
  for (i = 0; i < 7; i++){
    for (j = 0; j < 7; j++){
      /* On test pour toutes les directions possibles */
      /* Deux pions successifs donne 2 points, trois pions donne 3 points*/
      if (p[i][j] == couleur){
	
	if (i + 1 < 7 && p[i+1][j] == couleur){
	  pions += 2;
	  if (i + 2 < 7 && p[i+2][j] == couleur)
	    pions += 1;
	}

	if (i - 1 > 0 && p[i-1][j] == couleur){
	  pions += 2;
	  if (i - 2 > 0 && p[i-2][j] == couleur)
	    pions += 1;
	}

	if (j + 1 < 7 && p[i][j+1] == couleur){
	  pions += 2;
	  if (j + 2 < 7 && p[i][j+2] == couleur)
	    pions += 1;
	}

	if (j - 1 > 0 && p[i][j-1] == couleur){
	  pions += 2;
	  if (j - 2 > 0 && p[i][j-2] == couleur)
	    pions += 1;
	}
      }
    }
  }
  return pions;
}

float mobilite(plateau p, int couleur){
  int i, j;
  int pt_blanc = 0;
  int pt_noir = 0;
  float av_mobilite;
  /* Calcul du nombre de coup possible */
  for (i= 0; i<8; i++){
    for (j=0; j<8; j++){
      if (coup_valide(p, i, j, NOIR) == 1)
	pt_noir ++;
      if (coup_valide(p, i, j, BLANC) == 1)
	pt_blanc ++;
    }
  }

  /* Calcul de l'avantage de mobilité */
  /* La mobilité est calculée de la sorte: (mobilité_joueur - mobilité adversaire) / (mobilité_joueur + mobilité_adversaire)*/
  if (couleur == NOIR)
    av_mobilite = (float)(pt_noir - pt_blanc) / (pt_noir + pt_blanc);

  if (couleur == BLANC)
    av_mobilite = (float)(pt_blanc - pt_noir) / (pt_blanc + pt_noir);

  return av_mobilite;
  /* On retourne la mobilité que l'on traitera dans une autre fonction pour savoir si un coup est rentable ou non */
}

int quantificateur_mobi(plateau p, int couleur){
  float mobi = mobilite(p, couleur);
  int points = 0;
  /* On compare la valeur à des bornes choisies arbitrairement */
  
  /* Partie rapportant des points négatifs ou nul */
  if (mobi <= -2.0) /* On trouvera rarement un rapport inférieur à -2 */ 
    points = -15;
  if (mobi < -2.0 && mobi <= -1.5)
    points = -10;
  if (mobi < -1.5 && mobi <= -1.0)
    points = -5;
  if (mobi < -1.0 && mobi <= -0.5)
    points = -3;
  if (mobi < -0.5 && mobi <= 0.0)
    points = 0;

  /* Partie rapportant des points positifs ou nul */
  if (mobi > 0.0 && mobi < 0.5)
    points = 0;
  if (mobi >= 0.5 && mobi < 1.0)
    points = 3;
  if (mobi >= 1.0 && mobi < 1.5)
    points = 5;
  if (mobi >= 1.5 && mobi > 2.0)
    points = 10;
  if (mobi >= 2) /* On trouvera rarement un rapport supérieur à 2 */
    points = 15;

  return points;
}

  
/* Fonction pour conn1aître le nombre de pions définitifs */
int definitif(plateau p, int couleur){
  int i, j;
  int pions_def = 0;
  
  /* On parcourt toutes les directions */
  if (p[7][7] == couleur){
    pions_def ++;
    i = 6;
    j = 6;
    /* Tant que i ou j différent de 0 ou que les pions nous appartiennent */
    while (i != 0 && p[i][7] == couleur){
      pions_def ++;
      i --;
    }
    while (j != 0 && p[7][j] == couleur){
      pions_def ++;
      j --;
    }
  }

  if (p[7][0] == couleur){
    pions_def ++;
    i = 6;
    j = 1;
    /* Tant que i ou j différent de 0 ou que les pions nous appartiennent */
    while (i != 0 && p[i][7] == couleur){
      pions_def ++;
      i --;
    }
    while (j != 7 && p[0][j] == couleur){
      pions_def ++;
      j ++;
    }
  }

  if (p[0][0] == couleur){
    pions_def ++;
    i = 1;
    j = 1;
    /* Tant que i ou j différent de 0 ou que les pions nous appartiennent */
    while (i != 7 && p[i][0] == couleur){
      pions_def ++;
      i ++;
    }
    while (j != 7 && p[0][j] == couleur){
      pions_def ++;
      j ++;
    }
  }

  if (p[0][7] == couleur){
    pions_def ++;
    i = 1;
    j = 6;
    /* Tant que i ou j différent de 0 ou que les pions nous appartiennent */
    while (i != 7 && p[i][0] == couleur){
      pions_def ++;
      i ++;
    }
    while (j != 0 && p[0][j] == couleur){
      pions_def ++;
      j --;
    }
  }
  /* Fin du parcours, on renvoie le nombrede pions définitifs */
  return pions_def;
}

/* Fonctions listant les coups dit "suicidaire" (Les jouer revient à se tirer une balle dans le pied */
int est_suicidaire(plateau p, int couleur){
  int points = 0;

  /* On fait plutôt un listing des cases pour éviter de surcharger le code, la fonctio n'est pas optimale car il y a bien d'autres cas de figure mais ce sont les plus récurrent  */
  /* La fonction ne renverra que des nombres négatifs ou égaux à 0. Le nombre de points attribués à chaque case est arbitraire et résulte de notre ressenti par rapport à l'importance de ces cases */
  /* On test déjà sur les coins sont vides, ce qui nous évite de faire d'autres tests qui ne marcheraient pas dans tous les cas */
  
  if (p[0][0] == VIDE){
    if (p[1][0] == couleur && p[2][0] != couleur)
      points -= 5;
    if (p[1][1] == couleur && p[2][2] != couleur)
      points -= 5; 
    if (p[0][1] == couleur && p[0][2] != couleur)
      points -= 5;
  }
  
  if (p[7][0] == VIDE){
    if (p[6][0] == couleur && p[5][0] != couleur)
      points -= 5;
    if (p[6][1] == couleur && p[5][2] != couleur)
      points -= 5; 
    if (p[7][1] == couleur && p[7][2] != couleur)
      points -= 5;
  }
   
  if (p[0][7] == VIDE){
  if (p[0][6] == couleur && p[0][5] != couleur)
    points -= 5;
  if (p[1][6] == couleur && p[2][5] != couleur)
    points -= 5;
  if (p[1][7] == couleur && p[2][7] != couleur)
    points -= 5;
  }
  
  if (p[7][7] == VIDE){
  if (p[7][6] == couleur && p[7][5] != couleur)
    points -= 5;
  if (p[6][6] == couleur && p[5][5] != couleur)
    points -= 5;
  if (p[6][7] == couleur && p[5][7] != couleur)
    points -= 5;
  }

  /* On retourne le nombre de points cumulés */
  return points;
}
