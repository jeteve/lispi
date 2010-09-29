/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier syntax.c
   5 octobre 2000
   modif le 01/11/2000 oct by jay
*/
#include <lexico.h>
#include <entree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"

#include <doublet.h>
#include <symboles.h>
#include <utiles.h>

int niveau_de_recursivite;
int syntax_err;

int syntax_error( void )
{
  return syntax_err;
}

void syntax_init_syntax(void)
{
  syntax_err=0;
  niveau_de_recursivite=0;
}

/* renvoie 0 si ce n'est pas un nombre , 1 si oui */
int est_nombre(char *chaine )
{
  int i = 0;
  if( chaine[i]=='+' || chaine[i]=='-') i++ ;
  if( i == strlen(chaine) ) return 0; // cas des symboles "+" et "-"
  
  while( i < strlen(chaine)) {
    if (chaine[i] < '0' || chaine[i] > '9') return 0;
    else i++;
  }
  return 1;
}


int syntax_code_de( char * chaine)
{
  int le_symbole;
  int le_doublet;
  if( est_nombre(chaine) )
    { return doublet_nouveau_doublet(CODE_NOMBRE,atoi(chaine)); }

  if( (le_symbole=symboles_presence_de(chaine))==NON_PRESENT )
    {
      le_symbole=symboles_nouveau( strdup ( chaine ));
      le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
      
      symboles_set_reference(le_symbole,le_doublet);
      return le_doublet;
    }
  return symboles_est_reference(le_symbole);
}


void syntax_choix_si_sortie( void )
{
  if ( niveau_de_recursivite > 0 ) lexico_get_token();
}


void syntax_erreur( char * message )
{
  fprintf(stderr," ! SYNTAX ERROR at (l%d,c%d): %s, found \'%s\' \n",
	  entree_ligne_courante(),entree_colonne_courante(),message,lexico_debut_image());

  syntax_err=1;
}


void syntax_parenthese_fermante( void )
{
  if(syntax_error()) {return ;} ;
  switch( lexico_token_courant())
    {
    case PARENTHESE_FERMANTE : 
      niveau_de_recursivite--;
      syntax_choix_si_sortie();
      break;
    default :
      syntax_erreur(" Parenthese fermante attendue ");
    }
}

void syntax_subsentence(int *phrase_lue)
{
  int phrase_annexe1, phrase_annexe2;
  
  *phrase_lue=CODE_NIL;
  if(syntax_error()) {return ;} ;
  switch( lexico_token_courant())
    {
    case PARENTHESE_FERMANTE :
      niveau_de_recursivite--;
      syntax_choix_si_sortie();
      break;
    case POINT :
      lexico_get_token(); syntax_phrase(&phrase_annexe1);
      *phrase_lue=phrase_annexe1;
      syntax_parenthese_fermante();

      break;
    default :
      syntax_phrase(&phrase_annexe1);syntax_subsentence(&phrase_annexe2);
      *phrase_lue=doublet_nouveau_doublet(phrase_annexe1, phrase_annexe2);

    }
}



void syntax_phrase(int *phrase_lue )
{
  int phrase_annexe1;

  *phrase_lue=CODE_NIL;

  if(syntax_error()) {return; }  ;
  switch( lexico_token_courant())
    {
    case ATOME :
      *phrase_lue=syntax_code_de(lexico_debut_image());
      syntax_choix_si_sortie();

      break;
    case APOSTROPHE :
      lexico_get_token();syntax_phrase(&phrase_annexe1);

      *phrase_lue=doublet_nouveau_doublet(CODE_QUOTE,
					  doublet_nouveau_doublet(phrase_annexe1,CODE_NIL));
	break;
    case PARENTHESE_OUVRANTE :
      niveau_de_recursivite++;
      lexico_get_token();
      syntax_subsentence(&phrase_annexe1);
      *phrase_lue=phrase_annexe1;
      break;
    default : 
      syntax_erreur(" Attendu : Atome, ou ''', ou '(' "); 
    }

}

