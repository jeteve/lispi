#include "fcontrole.h"
#include <doublet.h>
#include <utiles.h>
#include <stdio.h>
#include <unistd.h>
#include <eval.h>
/* while et repeat utilisent lock et unlock pour sauvegarder leurs arguments du
   garbage collecting
*/


// sequence
int fprog(int l, int *r) {
  int carl=doublet_car(l);
  int cdrl=doublet_cdr(l);
  *r = CODE_NIL;

  /*si on a aucun argument*/
  if (carl < 0) {
    printf(" !! ERREUR dans and, 1 argument attendu\n");
    return ECHEC;
  }
  /*si le cdr n'est pas un noeud on arrete*/
  if (doublet_car(cdrl) < 0) {
    if (eval_phrase(carl, r) != ECHEC) {
      doublet_restituer(carl);
      doublet_restituer(*r);
      return SUCCES;
    }
    return ECHEC;
  }

  /*sinon on evalue le noeud et on recommence avec le noeud suivant*/
  if (eval_phrase(carl, r) != ECHEC) {
    doublet_restituer(carl);
    doublet_restituer(*r);
    return fprog(cdrl, r);
  }
  /*si ca s'est mal passé, on arrete*/
  return ECHEC;
}


int fprog1(int l, int *r) {
  int carl=doublet_car(l);
  int cdrl= doublet_cdr(l);
  int res;
  *r = CODE_NIL;

  /*si on a aucun argument*/
  if (carl < 0) {
    printf(" !! ERREUR dans and, 1 argument attendu\n");
    return ECHEC;
  }
  
  if ((res = eval_phrase(carl, r)) == ECHEC){
    doublet_restituer(carl);
    return ECHEC;
  }

  if (cdrl >= 0) {
    int temp;
    doublet_restituer(carl);
    res = fprog(cdrl, &temp);
  }
  return res;
}

int fand(int l, int *r) {
  int carl= doublet_car(l);
  int cdrl=doublet_cdr(l);
  *r = CODE_NIL;

  /* si on a aucun argument */
  if (carl < 0) {
    printf(" !! ERREUR dans and, 1 argument attendu\n");
    return ECHEC;
  }
  
  /* si on est a la fin, on a gagné */
  if (doublet_car(cdrl) < 0) return eval_phrase(carl, r);
  /* sinon */
  if ( eval_phrase(carl, r) == ECHEC){
    doublet_restituer(carl);
    return ECHEC;
  }

  if (*r != CODE_NIL) {
    doublet_restituer(carl);
    doublet_restituer(*r);
    return fand(cdrl, r);
  }
  return SUCCES;
}

int f_or(int l, int *r) {
  int carl=doublet_car(l);
  int cdrl=doublet_cdr(l);
  *r = CODE_NIL;

  /*si on a aucun argument*/
  if (carl < 0) {
    printf(" !! ERREUR dans or, 1 argument attendu\n");
    return ECHEC;
  }

  /*si on est a la fin, on a gagné*/
  if (doublet_car(cdrl) < 0) return eval_phrase(carl, r);
  /*sinon */
  if ( eval_phrase(carl, r) == ECHEC) return ECHEC;
  if (*r == CODE_NIL) {
    doublet_restituer(carl);
    doublet_restituer(*r);
    return f_or(doublet_cdr(l), r);
  }
  return SUCCES;
}

// conditionnelle
int fif(int l, int *r) {
  int carl=doublet_car(l);
  int cdrl=doublet_cdr(l);
  int cond;
  int res;

  *r = CODE_NIL;

  /* si on a aucun argument */
  if (carl < 0) {
    printf(" !! ERREUR dans if, 1 argument attendu\n");
    return ECHEC;
  }

  /* si on a un seul argument on peut retourner nil */
  if (doublet_car(cdrl) < 0)  return SUCCES;

  /*si la condition est respectee*/
  if (eval_phrase(carl, &cond) == ECHEC) return ECHEC;
  doublet_restituer(carl);
  if (cond != CODE_NIL){
    doublet_restituer(cond);
    return eval_phrase(doublet_car(cdrl), r);
  }

  doublet_restituer(cond);
  /* sinon */
  {
    int noeud_courant = doublet_cdr(l); /* noeud_courant = "si" */
    doublet_restituer(doublet_car(noeud_courant));
    while (doublet_car(doublet_cdr(noeud_courant)) >= 0) {
      noeud_courant = doublet_cdr(noeud_courant);
      if ( (res=eval_phrase(doublet_car(noeud_courant), r)) == ECHEC) return ECHEC;
      doublet_restituer(doublet_car(noeud_courant));
    }
    return res;
  }
}


// switch
int fcond(int l, int *r) {
  int condition;
  int noeud_courant = l;
  int Ai;

/*    noeud_courant=+------------------+---------------+------------nil
                    l                  l               l
                    A1--+---+--nil     A2..            A3..
	            l   l   l
              Ai1=pred  Ai2 Ai3
*/
  *r = CODE_NIL;

  /* si on a aucun argument */
  if (doublet_car(l) < 0) {
    printf(" !! ERREUR dans cond, 1 argument attendu\n");
    return ECHEC;
  }

  while ( (Ai = doublet_car(noeud_courant)) >= 0) {     // le noeud courant n'est pas un atome
    if ((doublet_car(Ai)) < 0) return ECHEC;      // Ai est un atome

    /* si la condition est respectee */
    if (eval_phrase(doublet_car(Ai), &condition) == ECHEC) return ECHEC;
    if (condition != CODE_NIL) {
      doublet_restituer(condition); // on a plus besoin du resultat de la condition
      doublet_restituer(doublet_car(Ai));  // on restitue le predicat
      Ai = doublet_cdr(Ai);
      while (doublet_car(Ai) >= 0) {
	if ( eval_phrase(doublet_car(Ai), r) == ECHEC) return ECHEC;
	doublet_restituer(doublet_car(Ai)); // on restitue ce qu'on vient de lire
	Ai = doublet_cdr(Ai);
      }
      return SUCCES;
    }
    noeud_courant = doublet_cdr(noeud_courant);
  }
  return SUCCES;
}


// repetitive
int fwhile(int l, int *r) {
  int res;
  int doublet_condition = doublet_car(l);
  int condition;
  int noeud_courant;  
  *r = CODE_NIL;
  
  /* si on a aucun argument */
  if (doublet_condition < 0) {
    printf(" !! ERREUR dans while, 1 argument attendu\n");
    return ECHEC;
  }
  
  doublet_lock(l);
  if (eval_phrase(doublet_condition, &condition) == ECHEC){doublet_unlock(l); return ECHEC;}

  while (condition != CODE_NIL) {
    doublet_restituer(condition);
    noeud_courant = doublet_cdr(l);
    while (doublet_car(noeud_courant) >= 0) {
      doublet_restituer(*r);
      if (eval_phrase(doublet_car(noeud_courant), r) == ECHEC){doublet_unlock(l); return ECHEC;}
      noeud_courant = doublet_cdr(noeud_courant);
    }
    if ((res = eval_phrase(doublet_condition, &condition)) == ECHEC) {doublet_unlock(l);return ECHEC;}
  }
  doublet_unlock(l);
  return res;
}


int frepeat(int l, int *r) {
  int noeud_nbIterations;
  int nbIterations;
  int res;
  int noeud_courant;
  
  *r = CODE_NIL;
  
  /* si on a aucun argument */
  if (doublet_car(l) < 0) {
    printf(" !! ERREUR dans repeat, 1 argument attendu\n");
    return ECHEC;
  }
  
  /* calcul du nombre d'iterations */
  if (eval_phrase(doublet_car(l), &noeud_nbIterations) == ECHEC) return ECHEC;
  if (doublet_car(noeud_nbIterations) != CODE_NOMBRE) {
    printf(" !! ERREUR dans repeat, nombre d'iteration n'est pas un nombre\n");
    return ECHEC;
  }
  nbIterations = doublet_cdr(noeud_nbIterations);
  doublet_restituer(noeud_nbIterations);
  doublet_restituer(doublet_car(l));

  if (nbIterations < 0) {
    printf(" !! ERREUR dans repeat, nombre d'iteration negatif\n");
    return ECHEC;
  }

  if (doublet_car(doublet_cdr(l)) < 0) return SUCCES;

  doublet_lock(l) ; // on est assure que rien de sera detruit de cet argument
  while (nbIterations-- > 0) {
    noeud_courant = doublet_cdr(l);
    while (doublet_car(noeud_courant) >= 0) {
      
      if ((res = eval_phrase(doublet_car(noeud_courant), r)) == ECHEC) { 
	doublet_unlock(l);return ECHEC; // unlock est necessaire pour ne pas perdre de doublets ...
      }
      doublet_garder(doublet_car(noeud_courant));
      doublet_restituer(*r);
      noeud_courant = doublet_cdr(noeud_courant);
    }
  }
  doublet_unlock(l); // pour qu'il soit eventuellement destructible ensuite 
  return res;
}

int f_error(int l,int *r){
  *r=CODE_NIL;
  return ECHEC;
}
