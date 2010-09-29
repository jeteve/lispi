#ifndef WITH_ENV
#define WITH_ENV
/* 
   Jerome eteve Arnaud ceol
   
   maitrise info 2000/2001
   projet lisp 
   fichier env.h 20 novembre 2000
   derniere modif par jay le 5 decembre 2000
   dernieres fonctions ajoutee : voir en bas de ce fichier

*/
#include <stdio.h>

void env_init();
/* A utiliser 1 et une seule fois,
   avant d'utiliser ce module
   par exemple dans utiles.c
*/

void env_cache_retire(int s);
/* 
   force le retrait du symbole s du cache
   pas d'effet si ce symbole n'est pas present
*/
void env_push(void);
// sauvegarde de l'environnement courant

void env_pop(void);
// restauration de l'environnement precedent

void env_dump(FILE * to);
/*
  Imprime l'environnement top level dans le fichier to
  ouvert en ecriture, de sorte qu'un load de ce fichier au
  relancement du programme restaure l'environnement tel qu'il etait
*/

int env_cherche(int s,int *r);
/* s est un symbole
   Renvoie succes ou echec
   en cas de succes, *r contient le doublet ayant pour car le 
   symbole s, et pour cdr sa valeur ....
   en cas d'echec, *r est le symbole Nil
*/

int env_ajoute_en_tete(int s,int r);
/* 
   ajoute en tete de l'environnement le symbole s lie a la valeur r
*/



int env_ajoute(int s,int *r);
/*
  cette fonction ne doit pas etre utilisee au niveau utilisateur,
  mais seulement a l'initialisation
  Le symbole S est une reference dans les doublets 
  associe au symbole s la valeur *r
  si le symbole s est deja present, ecrase sa valeur
  renvoie SUCCES
  *r n'est pas modifie et doit etre construit
  auparavant
  renvoie ECHEC si plus de memoire disponible
*/

int env_set(int l,int *r);
/* LA FONCTION A UTILISER AU NIVEAU UTILISATEUR
   sa specif est dans le poly
*/

int env_de(int l,int *r);
/*  
    Fonction de definition d'une fonction (utilise le symbole lambda)
    C'est une fonction du deuxieme type, ses arguments ne doivent pas etre evalue.
*/

int env_env(int l,int *r);
/*
  fonction utilisateur
 *r vaut la liste environnement 
   renvoie toujours SUCCES !!
*/

void env_garder(void);
/* appelle doublet_garder sur l'environnement */

void env_restituer(void);
/* appelle doublet_restituer sur l'environnement */

#endif
