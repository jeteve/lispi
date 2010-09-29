#ifndef WITH_UTILES
#define WITH_UTILES
/*  jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier utiles.h
   18 octobre 2000
   modif le 18 oct by jay
*/


/* ATTENTION a l'ordre d'initialisation
   pour que ces valeurs soient coherentes !!! */
#define CODE_NIL 0
#define CODE_QUOTE 1
#define CODE_TRUE  2
#define CODE_LAMBDA 3

#define DERNIER_RESERVE 69

#define SUCCES 0
#define ECHEC  -1
#define PROTOARGS int l,int *r

#include <stdio.h>

int fonctions_type2(void);
/* indice de la premiere fonction de type 2 */
int fin_ftype2(void);
/* Indice de la derniere fonction de type 2 */
int dernier_reserve(void);
/* indice du dernier symbole reserve */

void init_table_symboles(void);
/* AJOUTE LES SYMBOLES PRE DEFINIS dans les tables */

void init_env(void);

int fecrire_phrase(FILE * to,int doublet,int *espace);
/*
  Ecrit la phrase pointee par d dans le fichier to, ouvert en ecriture...
  !! N'est pas une fonction utilisateur.
  Espace doit etre une variable valant 0 pour avoir un bon affichage ...

*/


int ecrire_phrase( int doublet,int * espace  );
/* imprime la phrase pointee par doublet , a appeler avec espace=0 pour bon affichage
   retourne SUCCES ou ECHEC
 */

#endif
