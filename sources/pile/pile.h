/* Jerome Eteve 30 mai 2000 
   module de gestion de pile */
/* Les piles peuvent contenir des element castable
   par int */
#ifndef _WITH_PILE_H
#define _WITH_PILE_H

typedef struct Pile * Pile ;

/* constructeur */

Pile pile_nouvelle();

int pile_detruit( Pile );


int pile_pousse( Pile, int );
/* renvoient 0 en cas d'echec ( pile pleine ), 1 en cas de succes */

int pile_retire( Pile , int *);
int pile_vide(Pile);
/* renvoient 0 si la pile est non vide, 1 sinon */


void pile_print(Pile);


#endif /* _WITH_PILE_H */
