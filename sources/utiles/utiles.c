/*  jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier utiles.c
   18 octobre 2000
   modif le 30 oct by jay
*/
#include "utiles.h"

#include <symboles.h>
#include <doublet.h>
#include <string.h>

#include <fnum.h>
#include <flist.h>
#include <fpred.h>
#include <env.h>
#include <es.h>
#include <fcontrole.h>

#include <eval.h>
#include <stdio.h>

int ft2=0;
int fft2=0;
int last_reserve=0;

int fin_ftype2(void){
  return fft2;
}

int fonctions_type2(void) {
  return ft2;
}

int dernier_reserve(void){ return last_reserve;}

void init_table_symboles(void)
{
  int le_symbole,le_doublet;

  // SYMBOLES STANDARD 0
  le_symbole=symboles_nouveau( strdup ("nil" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);  
  symboles_set_reference(le_symbole,le_doublet);

  le_symbole=symboles_nouveau( strdup ("quote" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);  
  symboles_set_reference(le_symbole,le_doublet);
  
  le_symbole=symboles_nouveau( strdup ("t" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);  
  symboles_set_reference(le_symbole,le_doublet);

  le_symbole=symboles_nouveau( strdup ("lambda" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);

  // FONCTIONS NUMERIQUES 4
  le_symbole=symboles_nouveau( strdup ("add" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_add);
  le_symbole=symboles_nouveau( strdup ("+" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_add);

  le_symbole=symboles_nouveau( strdup ("sub" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_sub);
  le_symbole=symboles_nouveau( strdup ("-" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_sub);

  le_symbole=symboles_nouveau( strdup ("mul" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_mul);
  
  le_symbole=symboles_nouveau( strdup ("*" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_mul);
  
  
  le_symbole=symboles_nouveau( strdup ("div" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_div);
    
  le_symbole=symboles_nouveau( strdup ("/" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_div);
  
  le_symbole=symboles_nouveau( strdup ("rem" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_rem);

   le_symbole=symboles_nouveau( strdup ("%" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_rem);
  
  le_symbole=symboles_nouveau( strdup ("max" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_max);  
  
  le_symbole=symboles_nouveau( strdup ("min" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_min);  
  
  le_symbole=symboles_nouveau( strdup ("abs" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_abs);  
  
  le_symbole=symboles_nouveau( strdup ("opp" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_opp);  
  
  le_symbole=symboles_nouveau( strdup ("inc" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_incr);  
  
  le_symbole=symboles_nouveau( strdup ("1+" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_incr);
    
  le_symbole=symboles_nouveau( strdup ("dec" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_decr);  
  
  le_symbole=symboles_nouveau( strdup ("1-" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fnum_decr);

  // MANIPULATION DE LISTE 22
  le_symbole=symboles_nouveau( strdup ("car" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_car);
  
  le_symbole=symboles_nouveau( strdup ("cdr" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_cdr);
  
  le_symbole=symboles_nouveau( strdup ("nth" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_nth);

  le_symbole=symboles_nouveau( strdup ("last" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_last);
  
  le_symbole=symboles_nouveau( strdup ("cons" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_cons);

  le_symbole=symboles_nouveau( strdup ("append" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_append);

  le_symbole=symboles_nouveau( strdup ("list" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,flist_list);

  // Predicats 29
  le_symbole=symboles_nouveau( strdup ("lt" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_ppq);

  le_symbole=symboles_nouveau( strdup ("<" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_ppq);

  le_symbole=symboles_nouveau( strdup ("gt" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_pgq);

  le_symbole=symboles_nouveau( strdup (">" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_pgq);

  le_symbole=symboles_nouveau( strdup ("le" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_ppe);

  le_symbole=symboles_nouveau( strdup ("<=" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_ppe);

  le_symbole=symboles_nouveau( strdup ("ge" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_pge);

  le_symbole=symboles_nouveau( strdup (">=" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_pge);

  le_symbole=symboles_nouveau( strdup ("eqn" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_eqn);

  le_symbole=symboles_nouveau( strdup ("=" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_eqn);
  
  le_symbole=symboles_nouveau( strdup ("numbp" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_numbp);

  le_symbole=symboles_nouveau( strdup ("symbp" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_symbp);

  le_symbole=symboles_nouveau( strdup ("atomp" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_atomp);

  le_symbole=symboles_nouveau( strdup ("nullp" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_nullp);
  le_symbole=symboles_nouveau( strdup ("not" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_nullp);
  
  le_symbole=symboles_nouveau( strdup ("listp" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_listp);
  
  le_symbole=symboles_nouveau( strdup ("eq" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_eq);

  le_symbole=symboles_nouveau( strdup ("equal" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fpred_equal);

  // Le SET Ajoute par eteve 47
  le_symbole=symboles_nouveau( strdup ("set" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,env_set);

  // Entrees sorties
  
  le_symbole=symboles_nouveau( strdup ("read" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_read);

  
  le_symbole=symboles_nouveau( strdup ("prin" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_prin);

   
  le_symbole=symboles_nouveau( strdup ("print" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_print);

  le_symbole=symboles_nouveau( strdup ("space" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_space);

  le_symbole=symboles_nouveau( strdup ("crlf" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_crlf);

  le_symbole=symboles_nouveau( strdup ("\\n" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_crlf);
  
  
  le_symbole=symboles_nouveau( strdup ("eval" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_eval);
  
  le_symbole=symboles_nouveau( strdup ("load" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,es_load);

  // garbage collecting 56
  le_symbole=symboles_nouveau( strdup ("gc" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,doublet_fgc);

  le_symbole=symboles_nouveau( strdup ("gcinfo" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,doublet_fgcInfo);

  le_symbole=symboles_nouveau( strdup ("env" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,env_env);

  le_symbole=symboles_nouveau( strdup ("oblist" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,doublet_fobList);

  // fonctions de type 2 : les arguments ne sont pas evalues

  // fonctions de controle 60
  le_symbole=symboles_nouveau( strdup ("prog" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fprog);

  ft2 = le_doublet;  // premiere fonction de type 2

  le_symbole=symboles_nouveau( strdup ("prog1" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fprog1);

  le_symbole=symboles_nouveau( strdup ("and" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fand);

  le_symbole=symboles_nouveau( strdup ("or" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,f_or);

  // 50
  le_symbole=symboles_nouveau( strdup ("if" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fif);
  
  le_symbole=symboles_nouveau( strdup ("while" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fwhile);
  
  le_symbole=symboles_nouveau( strdup ("repeat" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,frepeat);
 
  le_symbole=symboles_nouveau( strdup ("cond" ));
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,fcond);


  le_symbole=symboles_nouveau( strdup ("de" ));    // 68
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,env_de);
  last_reserve=fft2=le_doublet;

  // Fin des fonctions de type 2
  // fin des symboles reserves
  
  le_symbole=symboles_nouveau( strdup ("error" ));    // 69
  le_doublet=doublet_nouveau_doublet(CODE_SYMBOLE,le_symbole);
  symboles_set_reference(le_symbole,le_doublet);
  symboles_associe_fonction(le_symbole,f_error);
  last_reserve=le_doublet;

}


void init_env(void)
{
  int nil=CODE_NIL;
  int true=CODE_TRUE;

  // Liaisons predefinies et initialisation 
  env_init();
  env_ajoute(CODE_NIL,&nil);
  env_ajoute(CODE_TRUE,&true);
}

int fecrire_phrase(FILE * to,int doublet,int *espace)
{
  int supplement=0;
  int car = doublet_car(doublet); 
  int noeud_courant;

  int status=0;

  if (car == CODE_QUOTE) 
    {
      fprintf(to,"'"); 
      return fecrire_phrase(to,doublet_car(doublet_cdr(doublet)),&supplement);
      
    }
  switch(car)
    {
    case DOUBLET_INCONNU : fprintf(stderr," ERREUR, doublet %d", doublet);return ECHEC ; break;
    case CODE_SYMBOLE : fprintf(to,"%c%s",*espace ,symboles_image(doublet_cdr(doublet))) ;return SUCCES ; break;
    case CODE_NOMBRE : fprintf(to,"%c%d",*espace  , doublet_cdr(doublet)); return SUCCES ;break;
    default :  
      fprintf(to,"%c(",*espace);
      noeud_courant = doublet;

      while ( doublet_car(doublet_cdr(noeud_courant)) != CODE_SYMBOLE && doublet_car(doublet_cdr(noeud_courant)) != CODE_NOMBRE ) {
	status+=fecrire_phrase(to,doublet_car(noeud_courant),&supplement);
	noeud_courant = doublet_cdr(noeud_courant);
	supplement=' ';
      }

      if (status < SUCCES ) return ECHEC ;
      status+=fecrire_phrase(to,doublet_car(noeud_courant),&supplement );
      if (status < SUCCES ) return ECHEC ;
      if (doublet_cdr(noeud_courant) == CODE_NIL){
	fprintf(to,")"); return SUCCES ;
      }else{
	fprintf(to,".");
	status+=fecrire_phrase(to,doublet_cdr(noeud_courant),&supplement);
	if (status < SUCCES ) return ECHEC ;
	fprintf(to,")");
	return SUCCES ;
      }
    }
}



int ecrire_phrase( int doublet,int * espace )
{
  int supplement=0;
  int car = doublet_car(doublet); 
  int noeud_courant;

  int status=0;

  if (car == CODE_QUOTE) 
    {
      printf("'"); 
      return ecrire_phrase(doublet_car(doublet_cdr(doublet)),&supplement);
      
    }
  switch(car)
    {
    case DOUBLET_INCONNU : printf(" ERREUR, doublet %d", doublet);return ECHEC ; break;
    case CODE_SYMBOLE : printf("%c%s",*espace ,symboles_image(doublet_cdr(doublet))) ;return SUCCES ; break;
    case CODE_NOMBRE : printf("%c%d",*espace  , doublet_cdr(doublet)); return SUCCES ;break;
    default :  
      printf("%c(",*espace);
      noeud_courant = doublet;

      while ( doublet_car(doublet_cdr(noeud_courant)) != CODE_SYMBOLE && doublet_car(doublet_cdr(noeud_courant)) != CODE_NOMBRE ) {
	status+=ecrire_phrase(doublet_car(noeud_courant),&supplement);
	noeud_courant = doublet_cdr(noeud_courant);
	supplement=' ';
      }

      if (status < SUCCES ) return ECHEC ;
      status+=ecrire_phrase(doublet_car(noeud_courant),&supplement );
      if (status < SUCCES ) return ECHEC ;
      if (doublet_cdr(noeud_courant) == CODE_NIL){
	printf(")"); return SUCCES ;
      }else{
	printf(".");
	status+=ecrire_phrase(doublet_cdr(noeud_courant),&supplement);
	if (status < SUCCES ) return ECHEC ;
	printf(")");
	return SUCCES ;
      }
    }
}

