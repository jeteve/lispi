/* derniere modif par Jay le 12 Octobre */

#include "doublet.h"
#include <stdio.h>
#include <utiles.h>
#include <symboles.h>
#include <stdlib.h>
#include <env.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

/* nombre maximum de noeuds : pour définir la taille du tableau */

#define DEBUT_NOEUDS 0
#define FIN_NOEUDS 4999
/* #define MAX_NOEUDS 5000 */
#define FIN_LIBRE  5000
/* #define CAR 0 */
/* #define CDR 1 */
#define CODE_LIBRE -10
#define CODE_NON_RECUPERABLE 2
#define CODE_RECUPERABLE 3
#define MIN_LOCKED 4


/* la mise a "locked" correspond a un decalage de 1 bit vers la gauche.
   le "delockage" correspond a un decalage vers la droite.
   Ainsi, on retrouve l'etat precedent du doublet apres un Unlock
   
   Un piti schema vaut mieux qu'un long discours :
   recuperable=[ ... 1 1] --lock-> [ ... 1 1 0] --unlock-> [... 1 1]
   nrecuperabl=[ ... 1 0] --lock-> [ ... 1 0 0] --unlock-> [... 1 0]

   On voit qu'un doublet "locked" a une valeur >=4 -> facile a verifier
   Un doublet "unlocked" a une valeur < 4 -> facile a verifier


   Sur un doublet "locked", les operations lock,restituer et garder n'ont aucun
   effet ( code des fonctions modifié).
   
   Sur un doublet "unlocked", l'operation unlock n'a aucun effet

   Le gc ne recupere pas les doublets "locked", car il ne recupere que les
   doublets recuperables
*/
   

// FIN_LIBRE doit etre egal a MAX_NOEUD 

int Tdoublet[MAX_NOEUDS] [2];
unsigned int Trecuperable[MAX_NOEUDS];
int nbLibres = MAX_NOEUDS;

/* le doublet libre à utiliser pour entrer un nouveau doublet */
int doublet_libre;

void doublet_initialisation(void) {
  register int i;
  doublet_libre = DEBUT_NOEUDS ;
  for (i = 0; i < MAX_NOEUDS; i++) {
    Trecuperable[i]=CODE_RECUPERABLE;
    Tdoublet[i][CAR] = CODE_LIBRE;
    Tdoublet[i][CDR] = i +1;
    Trecuperable[i] = 0;
  }
  Tdoublet[FIN_NOEUDS][CDR]=FIN_LIBRE;

}

int doublet_nouveau_doublet( int car, int cdr) {
  int emplacement ;
  if(doublet_libre == FIN_LIBRE ){
    doublet_gc();
    if (doublet_libre == FIN_LIBRE){ 
      fprintf(stderr," !! ERREUR INTERNE plus de place libre dans l'espace des doublets\n");
      fprintf(stderr,"    Probable recursion trop profonde !!\n Le programme va se terminer !!\n");
      kill( getpid(),SIGUSR1);
      /* TERMINONS PAR SIGNAL !!!! */

    }
  } 
  
  emplacement = doublet_libre;
  doublet_libre = Tdoublet[doublet_libre][CDR];
  Tdoublet[emplacement][CAR] = car;
  Tdoublet[emplacement][CDR] = cdr;
  Trecuperable[emplacement]= CODE_NON_RECUPERABLE ;
  nbLibres--;
  return emplacement;
  
}

int doublet_set_car(int d,int car)
{
  if (d >= MAX_NOEUDS || d < 0 || Tdoublet[d][CAR]==CODE_LIBRE ){
    fprintf(stderr," !! ERREUR INTERNE, Tentative d'acces a un doublet inexistant\n");
    return DOUBLET_INCONNU;
  }
  
 if (car >= MAX_NOEUDS || car < 0 || Tdoublet[car][CAR]==CODE_LIBRE ){
    fprintf(stderr," !! ERREUR INTERNE, Tentative d'acces a un doublet inexistant\n");
    return DOUBLET_INCONNU;
  }
 // les parametres sont valides
 Tdoublet[d][CAR]=car;
 return 0;
}

int doublet_set_cdr(int d,int cdr)
{
  if (d >= MAX_NOEUDS || d < 0 || Tdoublet[d][CAR]==CODE_LIBRE ){
    fprintf(stderr," !! ERREUR INTERNE, Tentative d'acces a un doublet inexistant\n");
    return DOUBLET_INCONNU;
  }
  
 if (cdr >= MAX_NOEUDS || cdr < 0 || Tdoublet[cdr][CAR]==CODE_LIBRE ){
    fprintf(stderr," !! ERREUR INTERNE, Tentative d'acces a un doublet inexistant\n");
    return DOUBLET_INCONNU;
  }
 // les parametres sont valides
 Tdoublet[d][CDR]=cdr;
 return 0;
}

/* int doublet_car( int noeud ){ */
/* #ifndef _NO_DEBUG */
/*   if (noeud >= MAX_NOEUDS || noeud < 0  || Tdoublet[noeud][CAR]==CODE_LIBRE  ){ */
/*     fprintf(stderr," !! ERREUR INTERNE, Tentative d'interroger un doublet inexistant \n"); */
/*     return DOUBLET_INCONNU; */
/*   } */
/* #endif */
/*   return Tdoublet[noeud][CAR]; */

/* } */

/* int doublet_cdr( int noeud ){ */
/*   if (noeud >= MAX_NOEUDS || noeud < 0 || Tdoublet[noeud][CAR]==CODE_LIBRE ){ */
/*     fprintf(stderr," !! ERREUR INTERNE, Tentative d'interroger un doublet inexistant\n"); */
/*     return DOUBLET_INCONNU; */
/*   } */
/*   return Tdoublet[noeud][CDR]; */
/* } */


#define doublet_supprimer_doublet( noeud ){ \
    Tdoublet[(noeud)][CAR] = CODE_LIBRE; \
    Tdoublet[(noeud)][CDR] = doublet_libre; \
    Trecuperable[(noeud)]=CODE_RECUPERABLE ; \
    doublet_libre = (noeud); \
    nbLibres++; \
}

 
void doublet_afficher_tout(void) {
  int i;
  printf("                                       Libre : %d \n",doublet_libre);
  for( i = 0; i < MAX_NOEUDS; i++){
    printf("%d :%d:%d: \n", i, Tdoublet[i][CAR], Tdoublet[i][CDR]);
  }    
} 

/* garbage collector */

// garder n'a aucun affet si le doublet est locked
void doublet_garder(int d) {
  register int car = Tdoublet[d][CAR];
  if (d <= DERNIER_RESERVE) return;
  if ( car != CODE_LIBRE )
    {
      // "setons" le a non_recuperable
      if(Trecuperable[d] < MIN_LOCKED )
	{ Trecuperable[d] = CODE_NON_RECUPERABLE ;}
      // Les appels recursifs utiles
      if( car >= 0 ) 
	{
	  doublet_garder(car);
	  doublet_garder(Tdoublet[d][CDR]);
	}
    }
}


// restituer n'a aucun affet si le doublet est locked
void doublet_restituer(int d) {
  register int car=Tdoublet[d][CAR];
  if (d <= DERNIER_RESERVE) return;
  if ( car != CODE_LIBRE )
    {
      // "setons" le a recuperable
      if(Trecuperable[d] < MIN_LOCKED )
	{ Trecuperable[d] = CODE_RECUPERABLE ;}
      // Les appels recursifs utiles
      if( car >= 0 )
	{
	  doublet_restituer(car);
	  doublet_restituer(Tdoublet[d][CDR]);
	}
    }
}

void doublet_restituer_jusque(int d,int stop) {
  register int car=Tdoublet[d][CAR];
  if ( d==stop ) return;
  if (d <= DERNIER_RESERVE) return;
  if ( car != CODE_LIBRE )
    {
      // "setons" le a recuperable
      if(Trecuperable[d] < MIN_LOCKED )
	{ Trecuperable[d] = CODE_RECUPERABLE ;}
      // Les appels recursifs utiles
      if( car >= 0 )
	{
	  doublet_restituer(car);
	  doublet_restituer(Tdoublet[d][CDR]);
	}
    }
}


void doublet_lock(int d) {
  register int car=Tdoublet[d][CAR];
  if (d <= DERNIER_RESERVE) return;
  if ( car != CODE_LIBRE )
    {
      // "setons" le a locked si il n'y est pas 
      if(Trecuperable[d] < MIN_LOCKED )
	{ Trecuperable[d] <<= 1 ;} // devient >= MIN_LOCKED
      // Les appels recursifs utiles
      if( car >= 0 )
	{
	  doublet_lock(car);
	  doublet_lock(Tdoublet[d][CDR]);
	}
    }
}

void doublet_unlock(int d) {
  register int car=Tdoublet[d][CAR];
  if (d <= DERNIER_RESERVE) return;
  if ( car != CODE_LIBRE )
    {
      // "setons" le a unlocked si il est locked
      if(Trecuperable[d] >= MIN_LOCKED )
	{ Trecuperable[d] >>= 1 ;} // devient < MIN_LOCKED
      // Les appels recursifs utiles
      if( car >= 0 )
	{
	  doublet_unlock(car);
	  doublet_unlock(Tdoublet[d][CDR]);
	}
    }
}


void doublet_gc() {
  register int i;
  //fprintf(stderr," garbage collecting\n");
  env_garder();
  for (i = DERNIER_RESERVE + 1; i < MAX_NOEUDS; i++) {
    if (Tdoublet[i][CAR] != CODE_LIBRE && Trecuperable[i] == CODE_RECUPERABLE) {
      if (Tdoublet[i][CAR] == CODE_SYMBOLE) {
	free(symboles_image(Tdoublet[i][CDR]));
	symboles_detruire(Tdoublet[i][CDR]);
      }
      /*      Tdoublet[i][CAR] = CODE_LIBRE;
	      Tdoublet[i][CDR] = doublet_libre;
	      Trecuperable[i] = CODE_NON_RECUPERABLE;
	      doublet_libre = i;
	      nbLibres++;*/
      doublet_supprimer_doublet(i);
    }
  }
  // fprintf(stderr," garbage collecting terminé\n");
}

int doublet_fgcInfo(int l, int *r) {
  *r = doublet_nouveau_doublet(doublet_nouveau_doublet(CODE_NOMBRE,nbLibres), 
			       doublet_nouveau_doublet(CODE_NOMBRE,symboles_nlibre()) );
  return SUCCES;
}

int doublet_fgc(int l, int *r) {
  doublet_gc();
  return doublet_fgcInfo(l, r);
}

int doublet_fobList(int l, int *r) {
  int i;
  *r = CODE_NIL;
  for (i = 0; i < MAX_NOEUDS; i++) {
    if (Tdoublet[i][CAR] == CODE_SYMBOLE && Trecuperable[i] == CODE_NON_RECUPERABLE) {
      *r = doublet_nouveau_doublet(i, *r);
    }
  }
  return SUCCES;
}
