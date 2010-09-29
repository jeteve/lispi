#ifndef WITH_EVAL
#define WITH_EVAL
/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier eval.h
   23 octobre 2000
*/

#include <utiles.h>
// Pour succes , echec
// Pour PROTOARGS


void eval_init(void);
/* a n'utiliser qu'une fois au debut du main */


int eval_phrase(int l,int *r);
/*
  Accepte un arbre l en parametre,
  resultat dans r
  renvoie SUCCES ou ECHEC

*/
void eval_print_appels(void);


#endif
