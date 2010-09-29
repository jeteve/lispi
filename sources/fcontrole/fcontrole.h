#ifndef WITH_FCONTROLE
#define WITH_FCONTROLE

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


int fprog(int l, int *r);

int fprog1(int l, int *r);

int fand(int l, int *r);

int f_or(int l, int *r);

int fif(int l, int *r);

int fwhile(int l, int *r);

int frepeat(int l, int *r);

int fcond(int l, int *r);

int f_error(int l,int *r);
/* renvoie Nil et provoque une erreur */
/* On peut voir cette fonction comme une sorte de RAISE */


#endif 
