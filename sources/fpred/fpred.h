#ifndef WITH_FPRED
#define WITH_FPRED


/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier fpred.h
   15 nov 2000
   derniere mise a jour le 15 nov 2000
*/

/***************************************
 * TOUTES LES                          *
 * FONCTIONS RENVOIENT SUCCES OU ECHEC *
 **************************************/
int fpred_ppq(int l,int *r);
// ses arguments numeriques sont dans l'ordre strict croissant
int fpred_pgq(int l,int *r);
// strict decroissant

int fpred_ppe(int l,int *r);
// croissants

int fpred_pge(int l,int *r);
// decroissants 


int fpred_eqn( int l, int *r);
// un de leurs arguments, ou nil si non-vrai

int fpred_numbp( int l , int *r );
// ce nombre si c'en est un, nil sinon

int fpred_symbp( int l, int *r );
// ce symbole, t si nil , nil sinon 
int fpred_atomp( int l, int *r );
// cet atom, t si nil, nil sinon ;

int fpred_nullp( int l, int *r );
// equivalent au not logique

int fpred_listp( int l, int *r );


int fpred_eq ( int l, int *r);
// teste si ces 2 arguments sont les meme,
// ie le meme arbre dans les doublets 

int fpred_equal(int l, int *r);
// teste si ces deux arguments sont les meme arbres,
// en terme de forme

#endif
