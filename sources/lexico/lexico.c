/*
  derniere modif by jay 3 oct 2000
*/

#include <entree.h>
#include "lexico.h"



/* Les variables globales */
#define TAILLE_BUFFER 256
token token_courant;
int erreur;

char buffer[TAILLE_BUFFER];
int  ibuff;

char * lexico_debut_image(void){return buffer;}
int lexico_taille_image(void){ return ibuff;}

int lexico_init_get_token(void)
{
  return erreur=entree_lire_car();
}


void passer_separateurs(void)
{
  while ( erreur ==0 && entree_car_lu() == SEPARATEUR )
    {
     erreur= entree_lire_car();
    }
}

void lire_atome(void)
{
  register int c ;

 
    do
      {
	if( ibuff < TAILLE_BUFFER )   /* Ne debordons pas !! */
	  {
	    buffer[ibuff]=entree_car_lu();ibuff++; 
	  }
	erreur=entree_lire_car();
	c=entree_car_lu();
      }
    while (  erreur != -1 && c != ')' && c != '(' && c != '.' && c != '\'' &&
	     c != SEPARATEUR && c != MARQUEUR_FIN );

    if(ibuff >= TAILLE_BUFFER )
      {
	fprintf(stderr," WARNING: atome trop long (l %d, c %d) \n",
		entree_ligne_courante(),entree_colonne_courante());  
	buffer[TAILLE_BUFFER-1]='\0';    /* Faut bien mettre un \0 a la fin d'une chaine */
	ibuff=TAILLE_BUFFER-2;
	return;
      }

    buffer[ibuff]='\0';
}



int lexico_get_token(void)
{
  if( erreur == -1 ) return -1; /* Au cas zou init aurait fait une erreur */ 
  erreur=0;
  /* for(ibuff=0 ; ibuff < TAILLE_BUFFER ; buffer[ibuff]='\0', ibuff++); c'est bien inutile */
  ibuff=0;
  passer_separateurs();
  if( erreur == -1 ) return -1 ;

  switch( entree_car_lu())
    {
    case '(' : token_courant=PARENTHESE_OUVRANTE;
      buffer[ibuff]=entree_car_lu(); ibuff++ ;
      buffer[ibuff]='\0';
      erreur=entree_lire_car() ;
      break;
    case ')' : token_courant=PARENTHESE_FERMANTE; 
      buffer[ibuff]=entree_car_lu(); ibuff++ ;
      buffer[ibuff]='\0';
      erreur=entree_lire_car() ;
      break;
    case '.' : token_courant=POINT ;
      buffer[ibuff]=entree_car_lu(); ibuff++ ;
      buffer[ibuff]='\0';
      erreur=entree_lire_car() ;
      break;
    case '\'' : token_courant=APOSTROPHE ;
      buffer[ibuff]=entree_car_lu(); ibuff++ ;
      buffer[ibuff]='\0';
      erreur=entree_lire_car();
      break;
    case MARQUEUR_FIN : token_courant=FIN_FICHIER ; 
      break;
    default : token_courant=ATOME ; lire_atome() ; 
    
    }
  return erreur ;
}


token lexico_token_courant(void)
{
  return token_courant ;
}

