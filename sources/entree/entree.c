/* 
   fichier entree.c 3 oct 2000
   madif 4 oct by jay
*/

#include "entree.h"
#include <stdio.h>

#define PREMIER_CARACTERE 33
#define DERNIER_CARACTERE 126
#define RETOUR_CHARIOT    10
#define MARQUEUR_COMMENTAIRE ';'

/* variables globales */ 
FILE * var_fichier_lu ;
int ligne_courante=1;
int colonne_courante=0;

int entree_colonne_courante (void){ return colonne_courante ; }
int entree_ligne_courante (void ) { return ligne_courante ; }


int  entree_set_entree( FILE * fichier_lu )
{
  var_fichier_lu=fichier_lu;
  ligne_courante=1;
  colonne_courante=0;
  //fprintf(stdout,"%d> ", ligne_courante );
  return 0 ;
}

FILE *entree_courante(void)
{
  return var_fichier_lu;
}

/* variable globale */
int car_lu ;


void entree_passer_la_ligne ( void)
{
  while ( car_lu != RETOUR_CHARIOT  && car_lu != -1 )
    {
      car_lu=getc( var_fichier_lu);
    }
}

int entree_lire_car( void  )
{
  if( car_lu == RETOUR_CHARIOT ) { printf("?> ");}
  car_lu=getc(var_fichier_lu);
  colonne_courante++;
  if ( car_lu == MARQUEUR_COMMENTAIRE ) entree_passer_la_ligne();
  if( car_lu == RETOUR_CHARIOT )
    {
      ligne_courante++;
      colonne_courante=0;
    }


  if ( car_lu >= SEPARATEUR  && car_lu < PREMIER_CARACTERE )
    {
      car_lu=SEPARATEUR ; return 0 ;
    }
  if ( car_lu >= PREMIER_CARACTERE && car_lu <= DERNIER_CARACTERE )
    {
      return 0 ;
    }
  if ( car_lu == -1 )
    {
      return 0 ;
    }
  else
    {
      fprintf(stderr ," WARNING: caractere \'%c\' non valide (l%d,c%d) => Ignore \n",
	      car_lu, ligne_courante , colonne_courante );
      return entree_lire_car();
    }
}

int entree_car_lu(void)
{
  return car_lu ;
}




