#ifndef WITH_ES
#define WITH_ES
/* 
   Jerome eteve Arnaud ceol
   
   maitrise info 2000/2001
   projet lisp 
   fichier es.h 20 novembre 2000
   derniere modif par jay le 20 novembre 2000

*/

int es_read(int l,int *r);
/*
  attend la frappe d'UNE phrase lisp et renvoie celle ci
*/
int es_prin(int l,int *r);
/*
  imprime tout ses arguments, sans retour chariot
  resultat : vrai
  les arguments DOIVENT etre evalu
*/


int es_print(int l,int *r);
/*
  imprime tout ses arguments, AVEC retour chariot
  resultat : vrai
  les arguments DOIVENT etre evalue
*/

int es_space(int l,int *r);
/* 
   imprime un espace et retourne vrai
   toujours succes
*/
 
int es_crlf(int l,int *r);
/* 
   imprime un retour chariot et retourne vrai
   toujours succes
*/

int es_eval(int l,int *r);
/*
  retourne l'evaluation de son premier argument
  sans argument : retourne nil
*/

int es_load(int l,int *r);
/*
  evalue le contenu du fichier passe
  en premier argument ( doit etre un symbole )
  
  resultat vrai si ca c'est bien passe,
  faux sinon

  retourne succes ou echec
*/


#endif
