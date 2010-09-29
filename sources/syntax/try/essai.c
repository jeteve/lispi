#include "syntax.h"
#include <entree.h>
#include <lexico.h>
#include <stdio.h>
#include <stdlib.h>
#include <utiles.h>
#include <symboles.h>
#include <doublet.h>

int main(void)
{
  int phrase_lue;
  int zero=0;
  
  doublet_initialisation();
  symboles_init();
  
  init_table_symboles();

  fprintf(stdout, "\n  [ LISPInterpreteur Version 22/10/2000, Eteve-Ceol ] \n\n      Bienvenue. Tapez Control-D pour sortir. \n\n%d>  ", entree_ligne_courante());
  entree_set_entree(stdin);
  lexico_init_get_token();
  lexico_get_token();
  do
    {
      syntax_init_syntax();
      syntax_phrase(&phrase_lue);
      if( syntax_error())
	{
	  printf( ":-( Ce n'est pas du lisp  !! \n\n%d> ", entree_ligne_courante());
	}
      else
	{ 
	  putchar('=');
	  ecrire_phrase(phrase_lue,&zero);
	  printf( "\n\n%d> ",entree_ligne_courante());
	}
      lexico_get_token();
    }
  while ( lexico_token_courant() != FIN_FICHIER );
  fprintf(stdout,"\n\n :-) A Bientot, %s ... \n",getenv("USER"));

}
