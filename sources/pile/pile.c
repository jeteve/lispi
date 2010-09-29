/* Jerome eteve 30 mai 2000 */
#define __PILE_C
#include <assert.h>
#include <pile.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _NO_DEBUG

typedef struct Pile 
{
  int * tableau ;
  int taille ;
  int position ;
} _Pile ;
#define PAS_TABLEAU 100

/* creation */
Pile pile_nouvelle()
{
  Pile pile = malloc(sizeof(_Pile));
  if(! pile) goto ERROR ;
  memset(pile,0,sizeof(_Pile));
  
  pile->position = 0;
  pile->taille = PAS_TABLEAU ;
  
  /* allocation du tableau */
  pile->tableau = malloc( sizeof(int)*PAS_TABLEAU );
  if ( ! pile->tableau) goto ERROR ;

  return pile;

  ERROR :
    if(pile){
      if(pile->tableau) free (pile->tableau);
      free(pile);
    }
  fprintf(stderr," FATAL Plus de memoire disponible");
  abort();
}

int pile_detruit( Pile pile)
{
  assert( (pile !=NULL)  && ((pile-> tableau) != NULL) );
  
  free(pile->tableau);
  free(pile);
  return 1;
}


 int pile_pousse( Pile pile, int element)
{
  assert(pile && pile->tableau);


  if(pile->position == pile->taille)
    {
#ifndef _NO_DEBUG
      printf(" TENTATIVE DE REALLOCATION d'une PILE\n");
#endif
      pile->tableau = realloc(pile->tableau,( pile->taille + PAS_TABLEAU)*
			      sizeof(int) );
      if(!pile->tableau)
	{
	  fprintf(stderr,"/\\ ! Impossible de pousser dans la pile");
	  return 0;
	}

      pile->taille += PAS_TABLEAU ;
    }
  /* la pile est assez grande */ 
  
#ifndef _NO_DEBUG
  printf(" TENTATIVE D'empiler \n");
#endif
  pile->tableau[pile->position] = element ;
  pile->position++;
#ifndef _NO_DEBUG
  printf(" Empilage reussi\n");
#endif

  return 1;
  
} 

int pile_retire(Pile pile, int * element)
{
  assert( pile && pile->tableau );
  if(pile->position)
    {
#ifndef _NO_DEBUG
  printf(" TENTATIVE De depiler \n");
#endif    
      pile->position--;
      *element = pile->tableau[pile->position];
#ifndef _NO_DEBUG
  printf(" DEPILAGE  reussi \n");
#endif 
      return 1;
    }
  else
    {
      
      // fprintf(stderr," /\\ ! Impossible de retirer de la pile \n");
      return 0;
    }
}

int pile_vide(Pile pile)
{
  assert( pile && pile->tableau );
  if(pile->position)
    {
      return 0;
    }
  else
    {
      /*  fprintf(stderr," /\\ ! Impossible de retirer de la pile \n");*/
      return 1;
    }
}

void pile_print( Pile pile )
{
  register int i;
  for (i=pile->position-1 ; i >= 0 ; printf("  %d \n",pile->tableau[i]) , i--);
}






