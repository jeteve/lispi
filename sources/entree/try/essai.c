#include "entree.h"
#include <stdio.h>

int main(void)
{
  

  entree_set_entree(stdin);
  do
    {
      if( ! entree_lire_car() ){ printf(" Caractere lu : %d \n", entree_car_lu());}
      else { entree_passer_la_ligne();}
    }
  while( entree_car_lu() != MARQUEUR_FIN);

  return 0;
}
