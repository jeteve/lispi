/* 
   Jerome eteve Arnaud ceol
   
   maitrise info 2000/2001
   projet lisp 
   fichier es.c 20 novembre 2000
   derniere modif par jay le 20 novembre 2000

*/

#include "es.h"
#include <syntax.h>
#include <lexico.h>
#include <utiles.h>
#include <doublet.h>
#include <symboles.h>
#include <eval.h>
#include <entree.h>

#include <stdlib.h>
#include <stdio.h>
int es_read(int l,int *r)
{
  int phrase_lue;
  *r=CODE_NIL;
 
  lexico_get_token();
  syntax_init_syntax();
  syntax_phrase(&phrase_lue);
  
  if( syntax_error())
	{
	  printf( " !!ERREUR : erreur de syntaxe\n");
	  return ECHEC;
	}

  *r=phrase_lue;
  return SUCCES;
}


int es_prin(int l,int *r)
{
  int zero=0;
  int pt=l;
  *r=CODE_NIL;

    while ( doublet_car(pt) >= 0 )
      {
	if(ecrire_phrase(doublet_car(pt),&zero)==ECHEC)
	{
	  printf(" !!ERREUR d'ecriture\n");
	  return ECHEC;
	}

	pt=doublet_cdr(pt);
      }

    *r=CODE_TRUE;
    return SUCCES;
}

int es_print(int l,int *r)
{
  int zero=0;
  int pt=l;
  *r=CODE_NIL;

    while ( doublet_car(pt) >= 0 )
      {
	if(ecrire_phrase(doublet_car(pt),&zero)==ECHEC)
	{
	  printf(" !!ERREUR d'ecriture\n");
	  return ECHEC;
	}

	pt=doublet_cdr(pt);
      }

    printf("\n");
    *r=CODE_TRUE;
    return SUCCES;
}

int es_space(int l,int *r)
{
  printf(" ");
  *r=CODE_TRUE;
  return SUCCES;
}

int es_crlf(int l,int *r)
{
  printf("\n");
  *r=CODE_TRUE;
  return SUCCES;
}
  
int es_eval(int l,int *r)
{
  int carl=doublet_car(l);
  int reseval;
  *r=CODE_NIL;

  if( carl < 0)
    {
      return SUCCES;
    }

  if( eval_phrase(carl,&reseval)==ECHEC )
    {
      // Le resultat peut etre nettoye
      doublet_restituer(reseval);
      return ECHEC;
    }

  *r=reseval;
  return SUCCES;
}

  
int es_load(int l,int *r)
{
#define RESTORE { \
  entree_set_entree(back); \
  if ( back==stdin) \
    { \
      printf("\n\n [toplevel]> "); \
    } \
 \
  lexico_init_get_token(); \
}


  int arg;
  char *filename;
  FILE *back;
  FILE * flu;

  int phrase_lue;
  int result;
  int zero=0;

  *r=CODE_NIL;

  if( doublet_car(l) < 0 )
    {
      printf(" !! ERREUR, un argument attendu\n");
      return ECHEC ;
    }

  arg=doublet_car(l);
  
  if ( doublet_car(arg) != CODE_SYMBOLE )
    {
      printf(" !! ERREUR, l'argument doit etre un symbole\n");
      return ECHEC ;
    }

  // l'argument est un symbole
  filename=symboles_image(doublet_cdr(arg));

  if( (flu=fopen(filename,"r"))==NULL)
    {
      printf(" !! ERREUR ouverture de %s impossible\n",filename);
      printf("    verifiez le nom ou les permissions\n");
      return ECHEC;
    }

  // le fichier existe
  // sauvegardons l'autre
  back=entree_courante();

  entree_set_entree(flu);
  lexico_init_get_token();
  lexico_get_token();

  printf("  chargement de %s ...\n",filename);
  do
    {
      syntax_init_syntax();
      syntax_phrase(&phrase_lue);
      if( syntax_error())
	{
	  printf( ":-( Ce n'est pas du lisp  !! \n");
	  // Supprimons cette mauvaise phrase
	  doublet_restituer(phrase_lue);
	  RESTORE;
	  return ECHEC;
	}
      else
	{ 
	  if(eval_phrase(phrase_lue,&result)==ECHEC)
	    { 
	      eval_print_appels();
	      // Supprimons cette mauvaise phrase ainsi que
	      // ce mauvais resultat
	      doublet_restituer(phrase_lue);
	      doublet_restituer(result);
	      RESTORE;
	      return ECHEC ;
	     
	    } ;
	  ecrire_phrase(result,&zero);
	  // le rsultat est imprimer, a quoi bon le garder ?
	  doublet_restituer(result);
	  // restituons aussi la phrase lue
	  doublet_restituer(phrase_lue);
	  printf("\n");
	}
      lexico_get_token();
    }
  while ( lexico_token_courant() != FIN_FICHIER );
  
  RESTORE;
  *r=CODE_TRUE;
  return SUCCES;


}

  
  
