#ifndef WITH_FLIST
#define WITH_FLIST

/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier flist.h
   2 nov 2000
   derniere mise a jour le 6 nov 2000
*/



/***************************************
 * TOUTES LES                          *
 * FONCTIONS RENVOIENT SUCCES OU ECHEC *
 **************************************/

int flist_car(int l,int *r);
/* le car de la premiere liste des arguments, le reste est ignore */
int flist_cdr(int l,int *r);
/* pareil sauf que different */
/* Si l'argument est la liste vide => return Vide */

int flist_nth(int l,int *r);
/* si on demande trop loin, equivalent a last */
int flist_last(int l,int *r);
/* toutes ces fonctions attendent des listes non-vides  */

int flist_cons(int l,int *r);
/* le cdr de l'avant dernier devient egal au dernier */
// l n'est pas reconstruite  //
// La liste peut etre vide //

int flist_list(int l,int *r);
/* Identite l n'est pas reconstruite*/

int flist_append(int l, int *r);
/* Les atomes derriere les points sont ignores */


#endif
