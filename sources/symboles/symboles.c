#include <stdio.h>
#include <string.h>
#include <doublet.h>
#include <unistd.h>
#include <signal.h>
#include "symboles.h"
/* 
   Jerome eteve Arnaud Ceol
   projet Lispi ustl 2000/2001
   fichier symboles.c 10/20/2000

   revision du 5/12/2000
   fonctions ajoutee : voir en fin de fichier .h
*/

#define _NO_DEBUG


#define DEBUT_SYMBOLES 0
#define FIN_SYMBOLES    499


int symboles_presents=0;

enregistrement es[NB_MAX_SYMBOLES];
int TT[NB_MAX_SYMBOLES];

#define LIBRE NULL
#define FIN_LISTE -10 


int symboles_liste_libre;
int fin_tt;
#define BEFORE_TT -1  

int symboles_nutiles(void){ return symboles_presents ;}
int symboles_nlibre(void){ return NB_MAX_SYMBOLES - symboles_presents ;}
void symboles_init( void )
{
  register int i;

  for( i = DEBUT_SYMBOLES ; i <= FIN_SYMBOLES ; i++)
    {
      es[i].s_image=LIBRE;
      es[i].s_ref=i+1;
      es[i].fass=NULL;
    }

  es[FIN_SYMBOLES].s_ref=FIN_LISTE ;

  symboles_liste_libre=DEBUT_SYMBOLES;
  fin_tt=BEFORE_TT;



}

void symboles_afficher_table(void)
{
  register int i ;
  fprintf(stdout,"\n Table des symboles \n");
  fprintf(stdout,"I |   image   | reference ; libre : %d\n",symboles_liste_libre);
  
  for( i = DEBUT_SYMBOLES ; i <= FIN_SYMBOLES ; i++)
    {
      fprintf(stdout,"%d  |  %s | %d \n",i,es[i].s_image, es[i].s_ref);
    }
}

void symboles_afficher_table_triee(void)
{
  register int i;
  fprintf(stdout,"\n Table des symboles triee \n");
  fprintf(stdout,"numero |   image   | reference ; libre : %d\n",symboles_liste_libre);
  for( i = DEBUT_SYMBOLES ; i <= fin_tt ; i++)
    {
      fprintf(stdout,"%d  |  %s | %d \n",i,es[TT[i]].s_image, es[TT[i]].s_ref);
    }
}

void inserer_dans_tt( int symbole)
{
  register int i;
  i=fin_tt;
  while ( i >= DEBUT_SYMBOLES && strcmp(es[TT[i]].s_image , es[symbole].s_image) >= 0 )
    {
      TT[i+1]=TT[i];
      i--;
    }
  TT[i+1]=symbole;
  fin_tt++;
}


int last_found=NON_PRESENT;
/* memorise le dernier trouve, pour economiser du temps en cas de recherche successives 
   du meme symbole 
*/

int symboles_presence_de ( char *image )
/* Renvoie NON_PRESENT en cas d'absence de la table,
   et sa reference externe sinon 
*/
{
  int sous_cherche( int borninf, int bornsup )
    {
      int milieu,cmp;
      /* cas ou il n'y a rien dans la table */ 
      if( bornsup < borninf ) { return NON_PRESENT;}

      /* cas ou la table est mono elemement */
      if ( bornsup == borninf )
	{
	  if(strcmp(image,es[TT[bornsup]].s_image) ==0 ){ return TT[bornsup] ;}
	  return NON_PRESENT ;
	}

      /* cas d'arret */
      if( (bornsup - borninf)==1)
	{
	  if(strcmp(image,es[TT[borninf]].s_image) ==0 ){ return TT[borninf] ;}
	  if(strcmp(image,es[TT[bornsup]].s_image) ==0 ){ return TT[bornsup] ;}
	  return NON_PRESENT ;
	}

      /* considerons le milieu */
      milieu= (bornsup+borninf)/2;
      cmp= strcmp(image,es[TT[milieu]].s_image);
      if( cmp < 0 ) {return sous_cherche(borninf,milieu);}
      if( cmp > 0 ) {return sous_cherche(milieu,bornsup);}
      if( cmp==0 ) { return TT[milieu] ;}
      return NON_PRESENT;
    }
     
  /*if( last_found != NON_PRESENT && es[last_found].s_image != NULL && strcmp(image,es[last_found].s_image)==0 ) 
    { return last_found;}
  else 
    {return last_found=sous_cherche(DEBUT_SYMBOLES,fin_tt);}
  */
  return sous_cherche(DEBUT_SYMBOLES,fin_tt);
  
}



int symboles_nouveau ( char *image )
{
  int res;
  int suivant ;
  
    
  if( symboles_liste_libre == FIN_LISTE )
    {
      doublet_gc();
      
      if( symboles_liste_libre == FIN_LISTE )
	{
	  fprintf(stderr," !! ERREUR INTERNE, plus de place disponible pour le symbole %s \n",image);
	  kill(getpid(),SIGUSR1);
	}
    }

  if ( symboles_presence_de( image ) != NON_PRESENT )
    {
       fprintf(stderr," !! ERREUR INTERNE,Tentative d\'enregistrement du symbole %s deja present  \n",image);
       return -1;
    }
  else
    {
      res=symboles_liste_libre;
      suivant= es[res].s_ref ;
      
      es[res].s_image=image;
      es[res].s_ref=NON_REFERENCE;
      
      symboles_liste_libre=suivant ;
      inserer_dans_tt(res);
#ifndef _NO_DEBUG
      fprintf(stdout,"  ;Symbole %s ajoute avec succes \n",image );
#endif
      symboles_presents++;
      return res;
    }
}


void remove_from_tt( int a_enlever )
     /* enleve l'entier a_enlever de TT */
{
  register int i=DEBUT_SYMBOLES ;
  while ( i <= fin_tt && TT[i] != a_enlever ){i++;}
  /*  i pointe sur la case a virer => il suffit de decaler */
  for( ; i < fin_tt; TT[i]=TT[i+1] , i++);
  /* .. et de decrementer fin_tt .. */
  fin_tt--;
}


/*int symboles_est_reference(int symbole)
  {
 
if( symbole < DEBUT_SYMBOLES || symbole > FIN_SYMBOLES ||
  es[symbole].s_image==NULL )
      {
    
    fprintf(stderr," !! ERREUR INTERNE tentative d'acces a un symbole inexistant \n");
      
      return NON_REFERENCE ;
      }

return es[symbole].s_ref;
  }*/


/* char * symboles_image( int symbole ) */
/* { */
  
/*   if( symbole < DEBUT_SYMBOLES || symbole > FIN_SYMBOLES || */
/*       es[symbole].s_image==NULL ) */
/*     { */
/* #ifndef _NO_DEBUG */
/*       fprintf(stderr," !! ERREUR INTERNE tentative d'acces a un symbole inexistant \n"); */
/* #endif */
/*       return NULL  ; */
/*     } */
/*   return es[symbole].s_image; */

/* } */


int symboles_detruire( int le_symbole )
{
  int a_detruire;

  if( le_symbole < DEBUT_SYMBOLES || le_symbole > FIN_SYMBOLES ||
      es[le_symbole].s_image==NULL )
    {
      fprintf(stderr," !! ERREUR INTERNE tentative de destruction d\'un symbole inexistant \n");

      return 0 ;
    }
  else
    {
      a_detruire=le_symbole ;

      es[a_detruire].s_image=NULL;
      es[a_detruire].s_ref=symboles_liste_libre;
      symboles_liste_libre=a_detruire;

      remove_from_tt( a_detruire );

#ifndef _NO_DEBUG
      fprintf(stdout," Destruction du symbole %d Ok  \n",a_detruire);
#endif
      symboles_presents--;
      last_found=NON_PRESENT;
      return 1;
    }
}



void symboles_set_reference( int symbole , int doublet )
{
    if( symbole < DEBUT_SYMBOLES || symbole > FIN_SYMBOLES ||
      es[symbole].s_image==NULL )
    {

      fprintf(stderr," !! ERREUR INTERNE tentative d'acces a un symbole inexistant \n");

      return ;
    }
    
    es[symbole].s_ref=doublet ;
}

void symboles_associe_fonction(int symbole, int (*f)())
{
  
  if( symbole < DEBUT_SYMBOLES || symbole > FIN_SYMBOLES ||
      es[symbole].s_image==NULL )
    {
      
      fprintf(stderr," !! ERREUR INTERNE tentative d'acces a un symbole inexistant \n");
      
      return ;
    }
    
  es[symbole].fass=f;
}

/* void *symboles_fonction_associee( int symbole ) 
 { 
   if( symbole < DEBUT_SYMBOLES || symbole > FIN_SYMBOLES || 
       es[symbole].s_image==NULL ) 
     { 
      
       fprintf(stderr," !! ERREUR INTERNE tentative d'acces a un symbole inexistant \n"); 
      
       return NULL; 
     } 

   return es[symbole].fass; 
 } */
