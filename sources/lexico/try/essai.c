#include <stdio.h>
#include <entree.h>
#include "lexico.h"
int main(void)
{
  int erreur;
  entree_set_entree(stdin);
  lexico_init_get_token();
  do
    {
      erreur=lexico_get_token();
      printf(" Token no %d :%s:  \n",lexico_token_courant(),lexico_debut_image());
    }
  while( ! erreur && lexico_token_courant() != FIN_FICHIER );
}
