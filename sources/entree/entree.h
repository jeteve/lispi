#ifndef WITH_ENTREE
#define WITH_ENTREE
/* 
   Arnaud Ceol, Jerome Eteve
   Maitrise info 2000/2001
   
   projet lisp
   fichier entree.h 3 oct 2000
   modifie 4 oct by jay

*/


#include <stdio.h>
#define SEPARATEUR 0
#define MARQUEUR_FIN -1

/*
  caractere autorises : de Ascii 0 a 126
*/
int entree_set_entree( FILE * fichier_lu );
/*
  0 en cas de succes, -1 si le fichier ne peut pas etre lu
*/
FILE *entree_courante(void);


int entree_lire_car(void);
/*
  renvoie 0 en cas de succes , et -1 si erreur ( fichier non ouvert ....
*/
int entree_car_lu( void );

/* pour la position du curseur :
 */
int entree_colonne_courante( void );
int entree_ligne_courante( void );

/* Passons des lignes : */
void entree_passer_la_ligne( void );



#endif
