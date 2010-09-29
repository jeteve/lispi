#include "flambda.h"
#include <env.h>
#include <fcontrole.h>
#include <utiles.h>
#include <doublet.h>
#include <stdio.h>
int flambda(int le,int pe,int *res)
{
  int status;
  int pfs;
  int pes;

  *res=CODE_NIL;
  env_push();
  
  pfs=doublet_car(le);
  pes=pe;

  // attribution des parametres effectifs aux parametres formels
  while( doublet_car(pfs) >= 0 )
    {
      if( doublet_car(pes)>=0 )
	{
	  env_ajoute_en_tete(doublet_car(pfs),doublet_car(pes));
	}
      else
	{
	  printf(" !!ERREUR pas assez d'arguments\n");
	  return ECHEC;
	}
      // avancon dans les 2 listes
      pfs=doublet_cdr(pfs); pes=doublet_cdr(pes);
    }

  // Les parametres sont fixes

  // executons le corps
  status=fprog(doublet_cdr(le),res);

  // restauration de l'environnement precedent
  env_pop();

  return status;
}

	    

  
  
  
