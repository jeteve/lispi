#ifndef WITH_FNUM
#define WITH_FNUM
/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier fnum.h
   23 octobre 2000
   derniere mise a jour le 2 novembre
*/
#include <utiles.h>
// Pour les macro SUCCES et ECHEC
// pour PROTOARGS



/***************************************
 * TOUTES LES                          *
 * FONCTIONS RENVOIENT SUCCES OU ECHEC *
 **************************************/

/* fonctions d'arite n */
int fnum_add(PROTOARGS);
/* si aucun argumen  => r=0 */

int fnum_sub(PROTOARGS);
/* si aucun argument => r=0   retourne celui ci si il est seul*/

int fnum_mul(PROTOARGS);
/* si aucun argument => r=1 */

int fnum_div(PROTOARGS);
/* si aucun arguments => r=1 */

int fnum_rem(PROTOARGS);
/* Attend au - un argument, renvoient celui ci si il est seul */


int fnum_max(PROTOARGS);
/* Max de rien vaut min de tout MININT */

int fnum_min(PROTOARGS);

/* fonctions d'arité 1 */
/* doivent avoir au moins un argument, ne prennent en compte que le premier argument */
int fnum_abs(PROTOARGS);
int fnum_opp(PROTOARGS);
int fnum_incr(PROTOARGS);
int fnum_decr(PROTOARGS);


#endif
