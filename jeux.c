#include "jeux.h"

void jeux_init(plateau p){
  /* Configuration de base + Affichage */
  p[3][3] = BLANC;
  p[4][4] = BLANC;
  p[3][4] = NOIR;
  p[4][3] = NOIR;
  plateau_affich(p); /* Affichage du plateau*/
}

int jouable(plateau p, int couleur){
  int i,j;
  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
      if(coup_valide(p,i,j,couleur))
	return 1; /* Le coup est valide on retourne 1 */
    }
  }
  return 0; /* Sinon il ne l'est pas on retourne 0 */
}

/* Indique si une direction de capture est possible ou non */
int est_direction_possible(plateau p, int x, int y, int dir, int couleur) {
  int i, j;
  int trouve=0;
  switch (dir){
    /* On test toutes les directions possibles */
  case 1: 
    for (i=1; i < 8; i++){
      if (y + i > 7 || p[x][y+i] == VIDE) /* On atteint la bordure ou une case vide */
	return 0;
      if (p[x][y+i] == couleur) /* */
	return trouve; /* Si ce pion est de la même couleur que celui à côté on renvoie trouve qui est encore égal à 0 */
      trouve=1; /* On a trouvé un pion de couleur différente */
    }
    break;
    
  case 2: 
    for (i = 1; i < 8; i++){
      if (y - i < 0 || p[x][y-i] == VIDE)
	return 0;
      if (p[x][y-i] == couleur)
	return trouve;
      trouve = 1;
    }
    break;
    
  case 3: 
    for (i = 1; i < 8; i++){
      if (x + i > 7 || p[x+i][y] == VIDE)
	return 0;
      if (p[x+i][y] == couleur)
	return trouve;
      trouve=1;
    }
    break;
    
  case 4:
    for (i = 1; i < 8; i++){
      if (x - i < 0 || p[x-i][y] == VIDE)
	return 0;
      if (p[x-i][y] == couleur)
	return trouve;
      trouve=1;
    }
    break;
    
  case 5:
    for (i = 1, j = 1; i < 8 && j < 8; i++, j++){
      if (( x + j > 7 || y - i < 0 )|| p[x+j][y-i] == VIDE)
	return 0;
      if (p[x+j][y-i] == couleur)
	return trouve;
      trouve = 1;
    }
    break;
    
  case 6: 
    for (i = 1, j = 1; i < 8 && j < 8; i++, j++){
      if (( x + j > 7 || y + i > 7)|| p[x+j][y+i] == VIDE)
	return 0;
      if (p[x+j][y+i] == couleur)
	return trouve;
      trouve = 1;
    }
    break;
    
  case 7: 
    for (i = 1, j = 1; i < 8 && j < 8; i++, j++){
      if (( x - j < 0 || y - i < 0 )|| p[x-j][y-i] == VIDE)
	return 0;
      if (p[x-j][y-i] == couleur)
	return trouve;
      trouve = 1;
    }
    break;
    
  case 8: 
    for (i = 1, j = 1; i < 8 && j < 8; i++, j++){
      if (( x - j < 0 || y + i > 7)|| p[x-1][y+1] == VIDE)
	return 0;
      if (p[x-j][y+i] == couleur)
	return trouve;
      trouve = 1;
    }
    break;
  }
  return 0;
}

/* Capture des pions en fonction de la direction donnée*/
int capturer_pion(plateau p, int x, int y, int dir, int couleur){
  int i, j;
  /* Si la direction demandée est impossible on ne peut rien faire */ 
  if (est_direction_possible(p, x, y, dir, couleur) == 0)
    return 0;

  /* On essaye toutes les directions possibles */
  switch (dir){
  case 1:
    for (i=1; p[x][y+i] != couleur; i++)
      p[x][y+i] = couleur;
    break;
    
  case 2: 
    for (i=1; p[x][y-i] != couleur; i++)
      p[x][y-i] = couleur;
    break;

  case 3: 
    for (i=1; p[x+i][y] != couleur; i++)
      p[x+i][y] = couleur;
    break;

  case 4:
    for (i=1; p[x-i][y] != couleur; i++)
      p[x-i][y] = couleur;
    break;

  case 5:
    for (i= 1, j=1; p[x+j][y-i] != couleur; i++, j++)
      p[x+j][y-i] = couleur;
    break;

  case 6:
    for (i= 1, j=1; p[x+j][y+i] != couleur; i++, j++)
      p[x+j][y+i] = couleur;
    break;
    
  case 7:
    for (i= 1, j=1; p[x-j][y-i] != couleur; i++, j++)
      p[x-j][y-i] = couleur;
    break;
    
  case 8: 
    for (i = 1, j = 1; p[x-j][y+i] != couleur; i++, j++)
      p[x-j][y+i] = couleur;
    break;
  }
  /* On retourne le nombre de pions retournés */
  return i;
}

/* Fonction de capture se servant de capturer_pions */
int capture(plateau p, int x, int y, int couleur){
  int i;
  int pions=1;
  /* Le pion prend la couleur (Le coup est forcément valide puisque vérifier dans le main) */
  p[x][y] = couleur;
  
  for (i = 1; i <= 8; i++)
    pions+= capturer_pion(p, x, y, i, couleur);
  
  return pions;
}

/* Renvoie si un coup est valide */
int coup_valide(plateau p, int x, int y, int couleur){
   int i,j;
  
  /* On regarde si le coup est valide (Case remplie = Coup non valide) */
  if(p[x][y] != VIDE)
    return 0;
  /* On regarde si le coup est jouable  */
  /* On prend toutes les directions possibles */
  if(p[x-1][y] != couleur){
    for(i=x-1; i>0; i--){
      if (p[i][y] == VIDE)
	break;
      if(p[i-1][y] == couleur && p[i][y] != couleur)
	return 1;
    }
  }
  
  if(p[x+1][y] != couleur)
    for(i=x+1; i<8; i++){
      if (p[i][y] == VIDE)
	break;
      if(p[i+1][y] == couleur && p[i][y] != couleur)
	return 1;
    }
  
  
  if(p[x][y-1] != couleur)
    for(i=y-1; i>0; i--){
      if (p[x][i] == VIDE)
	break;
      if(p[x][i-1] == couleur && p[x][i] != couleur)
	return 1;
    }
  
  if(p[x][y+1] != couleur)
    for(i=y+1; i<8; i++){
      if (p[x][i] == VIDE)
	break;
      if(p[x][i+1] == couleur && p[x][i] != couleur)
	return 1;
    }
  
  if(p[x-1][y-1] != couleur)
    for(i=x-1, j=y-1; i>0 && j>0; i--, j--){
      if (p[i][j] == VIDE)
	break;
      if(p[i-1][j-1] == couleur && p[i][j] != couleur)
	return 1;
    }
  
  if(p[x-1][y+1] != couleur)
    for(i=x-1, j=y+1; i>0 && j<8; i--, j++){
      if (p[i][j] == VIDE)
	break;
      if(p[i-1][j+1] == couleur && p[i][j] != couleur)
	return 1;
    }
  
  if(p[x+1][y-1] != couleur)
    for(i=x+1, j=y-1; i<8 && j>0; i++, j--){
      if (p[i][j] == VIDE)
	break;
      if(p[i+1][j-1] == couleur && p[i][j] != couleur)
	return 1;
    }
  
  if(p[x+1][y+1] != couleur)
    for(i=x+1, j=y+1; i<8 && j<8; i++, j++){
      if (p[i][j] == VIDE)
	break;
      if(p[i+1][j+1] == couleur && p[i][j] != couleur)
	return 1;
    }
  return 0;
}

void compte_pions(plateau p, int *nb_n, int *nb_b){
  int i, j;
  *nb_n = 0;
  *nb_b = 0;
  for (i = 0; i<8; i++){
    for (j = 0; j<8; j++){
      if (p[i][j] == NOIR)
	*nb_n+=1;
      if (p[i][j] == BLANC)
	*nb_b+=1;
    }
  }
}

