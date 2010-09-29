#include "eval.h"
#include <doublet.h>
#include <utiles.h>
#include <symboles.h>
#include <pile.h>
#include <env.h>

#include <stdio.h>

#include "flambda.h"

/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier eval.c
   23 octobre 2000
*/
Pile callstack ;
int poubelle;

int eval_liste(int a,int *r);
int eval_apply(int f,int r,int *res);

void eval_init(void)
{
  callstack = pile_nouvelle();
}

void eval_print_appels(void)
{
  while(pile_retire(callstack,&poubelle))
    {
      fprintf(stdout,"   dans l'appel de %s\n",symboles_image(poubelle));
    }
}

int eval_liste(int a,int *r)
{
  int cara=doublet_car(a);
  int cdra=doublet_cdr(a);
  int liste;
  int reseval;
  *r=CODE_NIL;

  if (a == CODE_NIL || cara==CODE_NOMBRE || cara==CODE_SYMBOLE)
    {
      *r=CODE_NIL; return SUCCES;
    }
  // evaluons la chose
  if( eval_phrase(cara,&reseval)==ECHEC ){
    doublet_restituer(cara);
    return ECHEC ;
  }
  // l'evaluation s'est bien passee
  //doublet_restituer(cara);
  // construisons la liste restante
  if ( eval_liste(cdra,&liste)==ECHEC )
    { 
      doublet_restituer(cdra);
      return ECHEC ;
    }

  // la liste restante est valide
  //doublet_restituer(cdra);

  *r=doublet_nouveau_doublet(reseval,liste);
  return SUCCES;
}


int eval_apply( int f, int r,int *res)
{
  int where;
  int status;
  int resfonc=0;
  int zero=0;

  int (*fapp)();
  *res=CODE_NIL ;

  if ( doublet_car(f)!=CODE_SYMBOLE )
    {
      fprintf(stdout," !! ERREUR symbole attendu,trouve:");
      ecrire_phrase( f,&zero);
      fprintf(stdout,"\n");
      return ECHEC;
    }
  // regardons si c'est une fonction primitive

  fapp=symboles_fonction_associee(doublet_cdr(f));
  
  /*if ( fapp==NULL) 
    {
      fprintf(stdout," !! ERREUR Aucune fonction associee au symbole %s\n",
	      symboles_image(doublet_cdr(f)));
      return ECHEC;
    }
  */
  if ( fapp != NULL ){
  status= (*fapp)(r,&resfonc);// on applique la fonction a la liste de ses arguments 
  *res=resfonc;
  return status;
  }

  // ce n'est pas une fonction primitive
  // regardons d'abord si ce n'est pas une fonction utilisateur
  if ( env_cherche(f,&where)==SUCCES)
    // le symbole est trouve
    {
      // regardons si il correspond a une lamnda expression
      if( doublet_car(doublet_cdr(where))==CODE_LAMBDA )
	// la valeur du symbole est une lambda expression
	{
	  // reste a appeler flambda avec les bons parametres
	  status=flambda(doublet_cdr(doublet_cdr(where)),r,res);
	  //  la lambda expression ^^^^^^^^ sans lambda
	  // les parametres effectifs evalue             ^

	  return status;
	}
    }

  // ce n'est pas non plus une focntion utilisateur
  fprintf(stdout," !! ERREUR Aucune fonction associee au symbole %s\n",
	  symboles_image(doublet_cdr(f)));
  return ECHEC; 
  
}


int eval_phrase(int l,int *r)
{
  int cdr=doublet_cdr(l);
  int car=doublet_car(l);
  int liste;
  int reseval;
  int where;

  *r=CODE_NIL;

  
  if ( car==CODE_NOMBRE ) { doublet_garder(l); *r = l; return SUCCES ;} // ne detruisons pas ces resultats
  if ( car==CODE_QUOTE  ) { *r = doublet_car(cdr) ; doublet_garder(*r);return SUCCES;}
  if ( car==CODE_SYMBOLE )
    {
      // CODE AJOUTE POUR LA PRISE EN COMPTE DES VARIABLES
      // Par eteve
      if( env_cherche(l,&where)==SUCCES )
	{
	  *r=doublet_cdr(where);
	  return SUCCES ;
	}
      // FIN du code ajoute

      fprintf(stderr," !! ERREUR symbole %s non defini.\n",
	      symboles_image(doublet_cdr(l)));
      return ECHEC ;
    }
  if (cdr == DOUBLET_INCONNU) return ECHEC;

  if ( doublet_car(doublet_car(l))==CODE_SYMBOLE ) {
    //fprintf(stdout,"   -> Appel de la fonction %s\n",symboles_image(doublet_cdr(doublet_car(l))));
    pile_pousse( callstack, doublet_cdr(doublet_car(l)));
  }

  if( car  >= fonctions_type2() && car <= fin_ftype2()) { 
    liste=cdr ;
  } else {
    if ( eval_liste(cdr,&liste)==ECHEC ) { 
      doublet_restituer(cdr);
      doublet_restituer(liste) ;return ECHEC;}
    // LA liste est desormais inutile
    // la liste est valide, on peut appeler eval_apply
  }

  if( eval_apply(car,liste,&reseval )==ECHEC ){ doublet_restituer(liste); return ECHEC;}
  // la liste est desormais inutile
  doublet_restituer(liste);
  // si le resultat est construit a partir de la liste,
  doublet_garder(reseval);
  // l'appel s'est bien passe
  pile_retire(callstack, &poubelle);
  *r=reseval ;return SUCCES ;
}
