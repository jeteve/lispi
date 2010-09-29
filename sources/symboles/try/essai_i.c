#include <entree.h>
#include <lexico.h>
#include "symboles.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void lire_commande()
{
  int a_detruire ;
  if( strcmp(lexico_debut_image(),"new")==0)
    {
      lexico_get_token();
      symboles_nouveau(strdup(lexico_debut_image()));
      return ;
    }
  if( strcmp(lexico_debut_image(),"rm")==0)
    {
      lexico_get_token();
      a_detruire=symboles_presence_de(lexico_debut_image());
      if(a_detruire != NON_PRESENT)
	{
	  free(symboles_image(a_detruire));
	  symboles_detruire(a_detruire);
	}
      else { printf( "\n Symbole Non Present !! \n") ;}
      return ;
    }
  if( strcmp(lexico_debut_image(),"p")==0)
    {
      symboles_afficher_table_triee();
      return ;
    }
  if( strcmp(lexico_debut_image(),"pa")==0)
    {
      symboles_afficher_table(); symboles_afficher_table_triee() ;
      return;
    }
  if ( strcmp( lexico_debut_image(),"is")==0)
    {
      lexico_get_token();
      a_detruire=symboles_presence_de(lexico_debut_image());
      if ( a_detruire==NON_PRESENT )
	{
	  printf("\n Il est pas la !!\n");
	  return ;
	}
      else
	{
	  printf("\n Il est la \n ");
	  return ;
	}
    }
      
  printf("\n Commande inconnue \n");
  return ;
}


int main(void)
{
  symboles_init();
  entree_set_entree(stdin);

  lexico_init_get_token();
  lexico_get_token();

  do
    {
      lire_commande();
      
      lexico_get_token();
    }
  while( lexico_token_courant() != FIN_FICHIER );
  return 0;

}
