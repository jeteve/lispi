/* 
   Jerome eteve Arnaud ceol
   
   maitrise info 2000/2001
   projet lisp 
   fichier env.c 20 novembre 2000
   derniere modif par jay le 20 novembre 2000

*/

#include "env.h"
#include <doublet.h>
#include <utiles.h>
#include <stdio.h>
#include <symboles.h>
#include <pile.h>
#define _NO_DEBUG

#ifndef _NO_DEBUG
#include <stdio.h>
#include <symboles.h>
#endif

int enviro=CODE_NIL;
int timestamp=0;

#define SIZEBUF 5
#define ENV_SYMBOL 0
#define ENV_WHERE  1
#define ENV_COUNT  2
#define ENV_WHICH  3
#define NOTHING -1
int env_buff[SIZEBUF][4];

Pile env_stack;

void env_garder(void){
  doublet_garder(enviro);
}

void env_restituer(void) {
  doublet_restituer(enviro);
}

int env_env(int l,int *r)
{
  *r=enviro;
  return SUCCES;
}

void env_init(void)
{
  register int i;
  env_stack=pile_nouvelle();
  for ( i = 0 ; i< SIZEBUF ; i++)
    {
      env_buff[i][ENV_SYMBOL]=NOTHING;
      env_buff[i][ENV_WHERE]=NOTHING;
      env_buff[i][ENV_WHICH]=NOTHING;
      env_buff[i][ENV_COUNT]=-1;
    }
}

void env_push(void){
  pile_pousse(env_stack,enviro);
}

void env_pop(void){
  int tmp;
  if(! pile_retire(env_stack,&tmp)) return; // un pop de trop ne provoque
  // pas d'erreur
  // Evidemment, l'ancien environnement est devenu inutile
  doublet_restituer_jusque(enviro,tmp);
  
  enviro=tmp;
}

void env_dump(FILE *to){
  int tmp;
  int dcour;
  int zero=0;
  int carcour ;
  fprintf(to,";  --Lispi par Jerome Eteve & Arnaud Ceol--\n");
  fprintf(to,";  --     Maitrise informatique USTL     --\n");
  fprintf(to,";  --            2000/2001               --\n\n");
  fprintf(to,"; Fichier de sauvegarde critique\n");
  fprintf(to,";   faite un load de ce fichier\n");
  fprintf(to,";   pour retaurer l'environnement\n");
  fprintf(to,"\n");
  fprintf(to,"()\n");
  while ( pile_retire(env_stack,&tmp)){
    doublet_restituer_jusque(enviro,tmp);
    enviro=tmp;
  }
  // l'enviro est celui initial 
  dcour=enviro;
  while ( doublet_car(dcour) > 0 && doublet_car((carcour=doublet_car(dcour))) != CODE_TRUE ){
    fprintf(to,"( set \'");
    fecrire_phrase(to,doublet_car(carcour),&zero);
    fprintf(to,"  \'");
    fecrire_phrase(to,doublet_cdr(carcour),&zero);
    fprintf(to," )\n");

    dcour=doublet_cdr(dcour);
  }
}



void env_cache_retire(int s)
{
  register int i;
  for (i=0; i < SIZEBUF ; i++)
    {
      if( env_buff[i][ENV_SYMBOL]==s)
	{
	  env_buff[i][ENV_SYMBOL]=NOTHING;
	  env_buff[i][ENV_WHERE]=NOTHING;
	  env_buff[i][ENV_WHICH]=NOTHING;
	  env_buff[i][ENV_COUNT]=-1;
	  return;
	}
    }
}


int env_cherche_buf(int s,int *w)
     /* succes si trouvé, w donne la ou il est */
{
  register int i ;
  for(  i=0 ; i < SIZEBUF ; i++)
    {
      if ( env_buff[i][ENV_SYMBOL]==s && env_buff[i][ENV_WHICH]==enviro)
	{
	  *w=env_buff[i][ENV_WHERE];
	  env_buff[i][ENV_COUNT]=(timestamp++);
#ifndef _NO_DEBUG
	  printf ("  symbole %s trouve dans le cache\n",symboles_image(doublet_cdr(s)));
#endif
	  return SUCCES;
	}
    }
  return ECHEC;
}

void env_ajoute_buf( int s, int w)
     /* remplace le moins utilise */
{
  register int i=0;
  register int lru=i;
  int min= env_buff[lru][ENV_COUNT];

  // recherche du LRU
  while ( i < SIZEBUF )
    {
      if( env_buff[i][ENV_COUNT] < min )
	{
	  lru=i ; min=env_buff[lru][ENV_COUNT];
	}
      i++;
    }
  
#ifndef _NO_DEBUG
  if ( env_buff[lru][ENV_SYMBOL] >= 0 )
    {
      printf( " Retrait du symbole %s du cache\n",symboles_image(doublet_cdr(env_buff[lru][ENV_SYMBOL])));
    }


  printf(" Ajout de %s dans le cache\n",symboles_image(doublet_cdr(s)));
#endif

  // remplacement de celui ci
  env_buff[lru][ENV_SYMBOL]=s;
  env_buff[lru][ENV_WHERE]=w;
  env_buff[lru][ENV_COUNT]= (timestamp++);
  env_buff[lru][ENV_WHICH]= enviro;
}



int env_cherche(int s,int *r)
{
  int tmp=enviro;
  int db=0;
  *r=CODE_NIL;

  /* if ( env_cherche_buf( s , &db) == SUCCES)
    {
      *r=db;
      return SUCCES;
    }
  */
  // le symbole n'a pas ete trouve dans le cache
  while(tmp!=CODE_NIL)
    {
      db=doublet_car(tmp);
      if(doublet_car(db)==s)
	{
	  //env_ajoute_buf(s,db);
	  *r=db;
	  return SUCCES;
	}

      tmp=doublet_cdr(tmp);
    }
  // le symbole n'a pas ete trouve

  return ECHEC;
}

void env_printall(void)
{
  int zero=0;
  int tmp=enviro;
  int db,sym, val;
  while ( tmp != CODE_NIL )
    {
      db=doublet_car(tmp);
      sym=doublet_car(db);
      val=doublet_cdr(db);

      printf(" %s ",symboles_image(doublet_cdr(sym)));
      ecrire_phrase(val,&zero);
      printf("\n");

      tmp=doublet_cdr(tmp);
    }
}
      

int env_ajoute(int s,int *r)
{
  int deja;
  int new_env;
  
  if (env_cherche(s,&deja)==SUCCES )
    {
      doublet_restituer(doublet_cdr(deja));
      // ELIMINONS L'ANCIENNE VALEUR
      doublet_set_cdr(deja,*r);
#ifndef _NO_DEBUG
      printf("  Symbole %s mis a jour\n",symboles_image(doublet_cdr(s)));
#endif
      return SUCCES ;
    }

  if ( (deja=doublet_nouveau_doublet(s,*r))!=DOUBLETS_PLEINS 
       &&
       ( new_env=doublet_nouveau_doublet(deja,enviro)) != DOUBLETS_PLEINS )
    {
      enviro=new_env;
#ifndef _NO_DEBUG
      printf("  Symbole %s ajoute a l'environnemment\n",symboles_image(doublet_cdr(s)));
#endif
      return SUCCES;
    }

#ifndef _NO_DEBUG
  printf(" Failed to add symbol %s to environnement\n",symboles_image(doublet_cdr(s)));
#endif;
  return ECHEC ;
}

int env_ajoute_en_tete(int s,int r)
{
  int new_env;
  int deja;

  if ( (deja=doublet_nouveau_doublet(s,r))!=DOUBLETS_PLEINS 
       &&
       ( new_env=doublet_nouveau_doublet(deja,enviro)) != DOUBLETS_PLEINS )
    {
      enviro=new_env;
#ifndef _NO_DEBUG
      printf("  Symbole %s ajoute en tete de l'environnemment\n",symboles_image(doublet_cdr(s)));
#endif
      return SUCCES;
    }

#ifndef _NO_DEBUG
  printf(" Failed to add symbol %s to environnement\n",symboles_image(doublet_cdr(s)));
#endif;
  return ECHEC ;
}

int env_set(int l,int *r) {
  int sym;
  int val;
  int arg;
  *r=CODE_NIL;
  
  // verification des arguments
  if (l==CODE_NIL ) {
    /* printf("  ERREUR, 2 arguments attendus\n");
       return ECHEC; */
    env_printall();
    *r=CODE_TRUE;
    return SUCCES;
  }
  
  sym=doublet_car(l);
  if ( sym <=DERNIER_RESERVE || doublet_car(sym) != CODE_SYMBOLE ) {
    printf("  ERREUR, premier argument doit etre un symbole non-reserve\n");
    return ECHEC;
  }
  
  if( symboles_fonction_associee(doublet_cdr(sym)) != NULL ) {
    printf("  ERREUR, vous ecrasez la definition d'une fonction predefinie\n");
    return ECHEC;
  }
  
  // le symbole est valide 
  arg=doublet_cdr(l);
  if (arg==CODE_NIL )  {
    printf("  ERREUR, 2 arguments attendus\n");
    return ECHEC;
  }

  val=doublet_car(arg);
  // pas de verification, ca peut etre n'importe koi
  
  *r=val;
  return env_ajoute(sym,&val);
}



int env_de(int l,int *r)
{
  int lambdaexpr;
  int syml;
  int ptl;
  int pt;
  int sym;
  int liste_sym;
  *r=CODE_NIL;
  
  /* Verification des arguments */
  if ((sym=doublet_car(l))< 0 ) {
    printf(" !!ERREUR, pas assez d'arguments\n");
    return ECHEC; 
  }

  if ( sym <=DERNIER_RESERVE || doublet_car(sym)!=CODE_SYMBOLE) {
    printf(" !!ERREUR le premier argument doit etre un symbole non-reserve\n");
    return ECHEC;
  }
  
  // le premier argument est un symbole pointe par sym
  
  pt=doublet_cdr(l);
  // verifions le second argument
  if( (liste_sym=doublet_car(pt)) < 0 ) {
    printf(" !!ERREUR le second argument doit etre une liste\n");
    return ECHEC;
  }
  
  // verification de la liste
  ptl=liste_sym;
  while ((syml=doublet_car(ptl)) >= 0) {
    if( syml <= DERNIER_RESERVE || doublet_car(syml)!=CODE_SYMBOLE) {
      printf(" !!ERREUR second argument doit etre une liste de symbole non-reserves\n");
      return ECHEC;
    }
    ptl=doublet_cdr(ptl);
  }

  /* la liste est valide et est pointee par liste_sym
     le reste des arguments peut etre n'importe quoi
  */
  
  // On peut construire la lambda expression
  lambdaexpr=doublet_nouveau_doublet(CODE_LAMBDA, pt);
  
  if(env_ajoute(sym,&lambdaexpr)==SUCCES) {
    *r=sym;
    return SUCCES;
  }
  return ECHEC;
}
