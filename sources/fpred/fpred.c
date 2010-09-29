
/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier fpred.c
   15 nov 2000
   derniere mise a jour le 15 nov 2000
*/
#include <stdio.h>

#include "fpred.h"
#include <utiles.h>

#include <doublet.h>

int fpred_ppq( int l, int *r)
{
  int res;
  int first;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      printf(" !! ERREUR au moins 1 argument attendu\n");
      return ECHEC;
      *r=CODE_NIL;
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR , nombre attendu\n");
      return ECHEC;
    }
  first= ( res=doublet_cdr(nb) );
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR , nombre attendu\n");
	  return ECHEC;
	}
      
      if ( res  >=  doublet_cdr(nb) )
	{
	  *r=CODE_NIL ; return SUCCES ;
	}

      res = doublet_cdr(nb);

      pt=doublet_cdr(pt);
      
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,first);
  return SUCCES;
  
}

  
int fpred_pgq( int l, int *r)
{
  int res;
  int first;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      printf(" !! ERREUR au moins 1 argument attendu\n");
      return ECHEC;
      *r=CODE_NIL;
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR , nombre attendu\n");
      return ECHEC;
    }
  first= ( res=doublet_cdr(nb) );
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR , nombre attendu\n");
	  return ECHEC;
	}
      
      if ( res  <=  doublet_cdr(nb) )
	{
	  *r=CODE_NIL ; return SUCCES ;
	}

      res = doublet_cdr(nb);

      pt=doublet_cdr(pt);
      
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,first);
  return SUCCES;
  
}




int fpred_ppe( int l, int *r)
{
  int res;
  int first;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      printf(" !! ERREUR au moins 1 argument attendu\n");
      return ECHEC;
      *r=CODE_NIL;
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR , nombre attendu\n");
      return ECHEC;
    }
  first= ( res=doublet_cdr(nb) );
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR , nombre attendu\n");
	  return ECHEC;
	}
      
      if ( res  >  doublet_cdr(nb) )
	{
	  *r=CODE_NIL ; return SUCCES ;
	}

      res = doublet_cdr(nb);

      pt=doublet_cdr(pt);
      
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,first);
  return SUCCES;
  
}

  
int fpred_pge( int l, int *r)
{
  int res;
  int first;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      printf(" !! ERREUR au moins 1 argument attendu\n");
      return ECHEC;
      *r=CODE_NIL;
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR , nombre attendu\n");
      return ECHEC;
    }
  first= ( res=doublet_cdr(nb) );
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR , nombre attendu\n");
	  return ECHEC;
	}
      
      if ( res  <  doublet_cdr(nb) )
	{
	  *r=CODE_NIL ; return SUCCES ;
	}

      res = doublet_cdr(nb);

      pt=doublet_cdr(pt);
      
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,first);
  return SUCCES;
  
}

int fpred_eqn( int l, int *r)
{
  int res;
  int first;
  int pt=l;
  int nb;
  *r=CODE_NIL ;

  if( pt==CODE_NIL)
    {
      printf(" !! ERREUR au moins 1 argument attendu\n");
      return ECHEC;
      *r=CODE_NIL;
      return SUCCES;
    }

  nb=doublet_car(pt);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      printf (" !! ERREUR , nombre attendu\n");
      return ECHEC;
    }
  first= ( res=doublet_cdr(nb) );
  pt=doublet_cdr(pt);

  while ( pt != CODE_NIL )
    {
      nb=doublet_car(pt);
      if ( doublet_car(nb)!=CODE_NOMBRE )
	{
	  printf (" !! ERREUR , nombre attendu\n");
	  return ECHEC;
	}
      
      if ( res  !=  doublet_cdr(nb) )
	{
	  *r=CODE_NIL ; return SUCCES ;
	}

      res = doublet_cdr(nb);

      pt=doublet_cdr(pt);
      
    }
  *r= doublet_nouveau_doublet(CODE_NOMBRE,first);
  return SUCCES;
  
}

int fpred_numbp(PROTOARGS){
  int nb ;
  *r=CODE_NIL;
    if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,1 argument attendu\n");
      return ECHEC;
    }

  nb = doublet_car(l);
  if ( doublet_car(nb)!=CODE_NOMBRE )
    {
      *r=CODE_NIL ;
      return SUCCES;
    }
  
 
  *r=nb;
  return SUCCES;
}
int fpred_symbp(PROTOARGS){
  int nb ;
  *r=CODE_NIL;
    if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,1 argument attendu\n");
      return ECHEC;
    }

  nb = doublet_car(l);
  if ( doublet_car(nb)!=CODE_SYMBOLE )
    {
      *r=CODE_NIL ;
      return SUCCES;
    }
  
  if ( nb == CODE_NIL ){ *r= CODE_TRUE ; return SUCCES ;}

  *r=nb;
  return SUCCES;
}

int fpred_atomp(PROTOARGS){
  int nb ;
  *r=CODE_NIL;
    if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,1 argument attendu\n");
      return ECHEC;
    }

  nb = doublet_car(l);
  if ( doublet_car(nb)>= 0 )
    {
      *r=CODE_NIL ;
      return SUCCES;
    }
  
  if ( nb == CODE_NIL ){ *r= CODE_TRUE ; return SUCCES ;}

  *r=nb;
  return SUCCES;
}


int fpred_nullp(PROTOARGS){
  int nb ;
  *r=CODE_NIL;
    if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,1 argument attendu\n");
      return ECHEC;
    }

  nb = doublet_car(l);
  
  
  if ( nb == CODE_NIL ){ *r= CODE_TRUE ; return SUCCES ;}

  *r=CODE_NIL;
  return SUCCES;
}
int fpred_listp(PROTOARGS){
  int nb ;
  *r=CODE_NIL;
    if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,1 argument attendu\n");
      return ECHEC;
    }

  nb = doublet_car(l);
  
  

  if ( nb == CODE_NIL ) { *r=CODE_TRUE ; return SUCCES ;}
  if ( doublet_car(nb) >= 0 ){ *r= nb ; return SUCCES ;}

  *r=CODE_NIL;
  return SUCCES;
}

int fpred_eq(int l,int*r)
{
  int args;
  int arg1, arg2;
  
  *r=CODE_NIL;

  if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,2 argument attendu\n");
      return ECHEC;
    }
   
  arg1=doublet_car(l);
  
  args= doublet_cdr(l);

    
  if( args==CODE_NIL)
    {
      printf(" !! ERREUR ,2 argument attendu\n");
      return ECHEC;
    }

  arg2= doublet_car(args);

  if( arg1==arg2)
    {
      if ( arg1==CODE_NIL)
	{
	  *r=CODE_TRUE ; return SUCCES;
	}
      *r=arg1;
      return SUCCES;
    }

  return SUCCES ;

}



int fpred_equal(int l,int*r)
{

  int equality( int a,int  b)
    {
      // ce sont les memes ( eventuellement les meme symboles )!!
      if ( a==b ){ return 1;}
      
      
      
      if ( doublet_car(a)==CODE_NOMBRE &&
	   doublet_car(b)==CODE_NOMBRE && doublet_cdr(a)==doublet_cdr(b)
	   ) return 1;
      
      if( doublet_car(a)==CODE_NOMBRE &&
	  doublet_car(b)==CODE_NOMBRE && doublet_cdr(a)!=doublet_cdr(b))
	return 0;
      
	  

      if  ( doublet_car(a)>= 0 &&
	    doublet_car(b) >= 0 &&
	    equality(doublet_car(a),doublet_car(b))==1 &&
	    equality(doublet_cdr(a),doublet_cdr(b))==1)
	{ 
	  return 1;
	}
	  return 0;
	  

    }


      


  int args;
  int arg1, arg2;
  
  *r=CODE_NIL;

  if( l==CODE_NIL)
    {
      printf(" !! ERREUR ,2 argument attendu\n");
      return ECHEC;
    }
   
  arg1=doublet_car(l);
  
  args= doublet_cdr(l);

    
  if( args==CODE_NIL)
    {
      printf(" !! ERREUR ,2 argument attendu\n");
      return ECHEC;
    }

  arg2= doublet_car(args);

  if( (arg1==arg2 )&& (arg1 ==CODE_NIL))
    {
      *r=CODE_TRUE;
      return SUCCES;
    }

  if ( equality( arg1 , arg2 )==1)
    {
      *r=arg1;
      return SUCCES;
    }
   

  return SUCCES ;

}
