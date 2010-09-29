/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier flist.c
   2 nov 2000
   derniere mise a jour le 2 nov 2000
*/
#include "flist.h"
#include <doublet.h>
#include <utiles.h>
#include <stdio.h>
#include <unistd.h>

#define _NO_DEBUG
int flist_car(int l,int *r)
{
  int car;
  int carcar;
  *r=CODE_NIL;
  
  if( l==CODE_NIL )
    { printf(" !! ERREUR dans car, 1 argument attendu\n");
    return ECHEC;
    }
  car= doublet_car(l);

  if ( car == CODE_NIL ){
    return SUCCES;
  }
  // la liste vide est autorisee 

  
  carcar= doublet_car(car);
  if( carcar == CODE_SYMBOLE ||
      carcar == CODE_NOMBRE )
    { printf(" !! ERREUR dans car, liste non vide attendue\n");
    return ECHEC;
    }

  *r=carcar;
  return SUCCES;
}

int flist_cdr(int l,int *r)
{
  int car;
  int carcar;
  *r=CODE_NIL;
  
  if( l==CODE_NIL )
    { printf(" !! ERREUR dans cdr, 1 argument attendu\n");
    return ECHEC;
    }
  car= doublet_car(l);
  if ( car == CODE_NIL ){
    return SUCCES;
  }
  // la liste vide est autorisee 


  carcar= doublet_car(car);
  if( carcar == CODE_SYMBOLE ||
      carcar == CODE_NOMBRE )
    { printf(" !! ERREUR dans cdr, liste non vide attendue\n");
    return ECHEC;
    }

  *r=doublet_cdr(car);
  return SUCCES;
}

int flist_nth(int l,int *r)
{
  // l doit avoir 2 arguments
  int nb;
  int list;
  int i;
  *r=CODE_NIL;
  
  nb=l;
  if ( nb==CODE_NIL )
    { printf(" !!ERREUR dans nth, attendu 2 arguments\n"); return ECHEC; }

  // il y a 1 argument 
  list=doublet_cdr(nb);
  if( list==CODE_NIL )
    {  printf(" !!ERREUR dans nth, attendu 2 arguments\n"); return ECHEC; }
  // il y a 2 arguments
  // descendons au nombre
  nb=doublet_car(nb);
  if ( doublet_car(nb) != CODE_NOMBRE || doublet_cdr(nb) < 1 )
    { printf (" !!ERREUR dans nth, nombre positif attendu en premier argument\n");
    return ECHEC;
    }

  // descendons a la liste 
  list=doublet_car(list);
  if( doublet_car(list) < 0 )
    { printf (" !!ERREUR dans nth, attendu liste non vide comme second argument\n");
    return ECHEC;
    }

  i=1;
  while ( i < doublet_cdr(nb) && doublet_car(doublet_cdr(list))>0)
    // Pour ne pas depasser la fin de liste 
    {
      list=doublet_cdr(list);
      i++;
    }

  *r=list;
  return SUCCES;
}

int flist_last(int l,int *r)
{
  // l doit avoir 1 arguments
  int list;
  *r=CODE_NIL;
  
  list=l;
  if( list==CODE_NIL )
    {  printf(" !!ERREUR dans last, attendu 1 argument\n"); return ECHEC; }
  // il y a 1 arguments
  // descendons au nombre

  // descendons a la liste 
  list=doublet_car(list);
  if( doublet_car(list) < 0 )
    { printf (" !!ERREUR dans last, attendu liste non vide comme argument\n");
    return ECHEC;
    }

  while (  doublet_car(doublet_cdr(list))>0)
    // Pour ne pas depasser la fin de liste 
    {
      list=doublet_cdr(list);
    }

  *r=list;
  return SUCCES;
}

int flist_cons(int l,int *r)
{
  // l doit etre au moins de 2 arguments
  int avdern;
  int dern;
  *r=CODE_NIL;
  avdern=l;
  if ( avdern==CODE_NIL )
    { printf(" !!ERREUR dans cons, attendu au moins 2 arguments\n"); return ECHEC; }

  // il y a 1 argument 
  dern=doublet_cdr(avdern);
  if( dern==CODE_NIL )
    {  printf(" !!ERREUR dans cons, attendu au moins 2 arguments\n"); return ECHEC; }
  // il y a 2 arguments

  // avancons jusqu'au bout
  while(doublet_cdr(dern)!=CODE_NIL )
    {
      avdern=dern;
      dern=doublet_cdr(dern);
    }
  
  // nous sommes au bout
  // verifions que le dernier argument est une liste
  if( doublet_car(doublet_car(dern))<0 && doublet_car(dern) != CODE_NIL  )
    // cas de la liste vide traite par le &&
    { printf(" !! ERREUR dans cons, le dernier argument doit etre une liste\n"); return ECHEC;
    }

  doublet_restituer(doublet_cdr(avdern));
  doublet_set_cdr(avdern,doublet_car(dern));
  *r=l;
  return SUCCES;
}


int flist_list(int l,int *r)
{
  *r=l;
  return SUCCES;
}

int flist_append(int l,int *r)
{
  
  int arg ;
  int liste ;
  int nvx ; 
  int fnvx;
  int plus;
  int first=1;

  arg=l;
  *r = CODE_NIL ;
  fnvx=CODE_NIL;
  nvx=CODE_NIL;
  
  // parcourons les arguments 
  while ( arg  != CODE_NIL )
    {

#ifndef _NO_DEBUG
      printf(" => boucle externe \n");
      sleep(1);
#endif

      // descendons  a la liste
      liste = doublet_car(arg);
      
      if ( liste != CODE_NIL && doublet_car(liste) < 0 )
	{ printf(" !! ERREUR attendu une liste \n");
	return ECHEC;
	}

	
      // parcourons la liste
      while ( doublet_car(liste) > 0 ) // on s'arrete sur un symbole ou sur nil
	{
#ifndef _NO_DEBUG
	  printf("    => boucle interne \n");
	  sleep(1);
#endif
	  plus=doublet_nouveau_doublet(doublet_car(liste) ,CODE_NIL);
	  if ( first==1 ){ nvx=fnvx=plus;}

	  first=0;
	  doublet_set_cdr(fnvx,plus);
	  fnvx=doublet_cdr(fnvx);
      
	  // passons au prochain element 
	  liste= doublet_cdr(liste);
	}

      // passons au prochain argument
      arg= doublet_cdr(arg);
    }
  doublet_set_cdr(fnvx,CODE_NIL);
  *r=nvx;
  return SUCCES;
      
}
       
