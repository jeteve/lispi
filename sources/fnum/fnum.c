/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier eval.c
   23 octobre 2000
   derniere mise a jour le 1/11/2000
*/

#include "fnum.h"
#include <stdio.h>
#include <utiles.h>
#include <doublet.h>

#define MAXINT 2147483645
#define MININT -2147483647

int fnum_add(PROTOARGS)
{
  int somme=0;
  int pt=l;
  int nb;
  *r=CODE_NIL;

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans add, nombre attendu\n");
	  return ECHEC;
	}
      somme+=doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r = doublet_nouveau_doublet(CODE_NOMBRE,somme);
  return SUCCES;

}

int fnum_sub(PROTOARGS)
{
  int res;
  int pt=l;
  int nb;

  *r=CODE_NIL;
  if( pt==CODE_NIL)
    {
      //printf(" !! ERREUR dans sub, au moins 1 argument attendu\n");
      //return ECHEC;
      *r=doublet_nouveau_doublet(CODE_NOMBRE,0);
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR dans sub, nombre attendu \n");
      return ECHEC;
    }
  res=doublet_cdr(nb);
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans sub, nombre attendu \n");
	  return ECHEC;
	}
      res-=doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r = doublet_nouveau_doublet(CODE_NOMBRE,res);
  return SUCCES;
}

int fnum_mul(PROTOARGS)
{
  int prod=1;
  int pt=l;
  int nb;
  
  *r=CODE_NIL;
  
  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans mul, nombre attendu\n");
	  return ECHEC;
	}
      prod*=doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r = doublet_nouveau_doublet(CODE_NOMBRE,prod);
  return SUCCES;
}

int fnum_div(PROTOARGS)
{
  int res;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      // printf(" !! ERREUR dans div, au moins 1 argument attendu\n");
      // return ECHEC;
      *r=doublet_nouveau_doublet(CODE_NOMBRE,1);
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR dans div, nombre attendu\n");
      return ECHEC;
    }
  res=doublet_cdr(nb);
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans div, nombre attendu\n");
	  return ECHEC;
	}
      if( doublet_cdr(nb) == 0 ){
	printf (" !! ERREUR dans div, nombre non nul attendu\n");
	return ECHEC;
      }
      res/=doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,res);
  return SUCCES;
}

int fnum_rem(PROTOARGS)
{
  int res;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      printf(" !! ERREUR dans rem, au moins 1 argument attendu\n");
      return ECHEC;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR dans rem, nombre attendu\n");
      return ECHEC;
    }
  res=doublet_cdr(nb);
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans rem, nombre attendu\n");
	  return CODE_NIL;
	}
      if( doublet_cdr(nb) == 0 ){
	printf (" !! ERREUR dans rem, nombre non nul attendu\n");
	return ECHEC;
      }
      res%=doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,res);
  return SUCCES;
}


int fnum_max(PROTOARGS){
  int max = MININT;
  int pt=l;
  int nb;
  *r=CODE_NIL;

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans max, nombre attendu\n");
	  return ECHEC;
	}
      if(doublet_cdr(nb) > max) max = doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r = doublet_nouveau_doublet(CODE_NOMBRE,max);
  return SUCCES;
}

int fnum_min(PROTOARGS){
  int min = MAXINT;
  int pt=l;
  int nb;

  *r=CODE_NIL;
  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR dans min, nombre attendu\n");
	  return ECHEC;
	}
      if(doublet_cdr(nb) < min) min = doublet_cdr(nb);
      pt=doublet_cdr(pt);
    }
  *r = doublet_nouveau_doublet(CODE_NOMBRE,min);
  return SUCCES;
}


/* fonctions d'arité 1 */
/* ne prennent en compte que le premier argument */
/* envoient un message d'avertissement si des arguments sont ignores */

int fnum_abs(PROTOARGS){
  int nb ;
  *r=CODE_NIL;
    if( l==CODE_NIL)
    {
      printf(" !! ERREUR dans abs,1 argument attendu\n");
      return ECHEC;
    }

  nb = doublet_car(l);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR dans abs, nombre attendu\n");
      return ECHEC;
    }
  
  if (doublet_cdr(l) != CODE_NIL){
    printf (" !! WARNING: dans abs, trop d'arguments\n");
  }
  
  if(doublet_cdr(nb) < 0)
    {*r=doublet_nouveau_doublet(CODE_NOMBRE, -1*doublet_cdr(nb)); return SUCCES ; }
  *r= doublet_nouveau_doublet(CODE_NOMBRE, doublet_cdr(nb));
  return SUCCES;
}

int fnum_opp(PROTOARGS){
  int nb;
  *r=CODE_NIL;
  if( l==CODE_NIL)
    {
      printf(" !! ERREUR dans opp,1 argument attendu\n");
      return ECHEC;
    }
  
   nb = doublet_car(l);
   if ( doublet_car(nb)!=CODE_NOMBRE )
     {
       printf (" !! ERREUR dans add, nombre attendu\n");
       return ECHEC;
     }
   if(doublet_cdr(l) != CODE_NIL){
     printf (" !! WARNING: dans opp : trop d'arguments\n");
   }
   *r= doublet_nouveau_doublet(CODE_NOMBRE, -1*doublet_cdr(nb));
   return SUCCES;
}

int fnum_incr(PROTOARGS){
  int nb;
  *r=CODE_NIL;

  if( l==CODE_NIL)
    {
      printf(" !! ERREUR dans inc,1 argument attendu\n");
      return ECHEC;
    }
  
  nb = doublet_car(l);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR dans inc, nombre attendu\n");
      return ECHEC;
    }
  if(doublet_cdr(l) != CODE_NIL){
    printf (" !! WARNING: dans abs, trop d'arguments\n");
  
  }
  *r= doublet_nouveau_doublet(CODE_NOMBRE, doublet_cdr(nb) + 1);
  return SUCCES;
}

int fnum_decr(PROTOARGS){
  int nb;
  *r=CODE_NIL;
  if( l==CODE_NIL)
    {
      printf(" !! ERREUR dans dec,1 argument attendu\n");
      return ECHEC;
    }
  
  nb = doublet_car(l);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR dans dec, nombre attendu\n");
      return ECHEC;
    }
  if(doublet_cdr(l) != CODE_NIL){
    printf (" !! WARNING: dans dec : trop d'arguments\n");

  }
  *r= doublet_nouveau_doublet(CODE_NOMBRE, doublet_cdr(nb) - 1);
  return SUCCES;
}
