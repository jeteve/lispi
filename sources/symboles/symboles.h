#ifndef WITH_SYMBOLES
#define WITH_SYMBOLES
/* 
   Jerome eteve Arnaud Ceol
   projet Lispi ustl 2000/2001
   fichier symboles.h 10/20/2000

   revision du 05/12/2000
   fonctions ajoutee : voir en fin de fichier
*/

#define NON_REFERENCE -1
#define NON_PRESENT   -1
#define SYMBOLES_PLEINS -1

typedef struct s_enregistrement{
  char * s_image ;
  int  s_ref ;
  int (*fass)();
}  enregistrement ;
#define NB_MAX_SYMBOLES 500
extern enregistrement es[NB_MAX_SYMBOLES];

#define symboles_image(symbole) (es[(symbole)].s_image)
#define symboles_fonction_associee(symbole) (es[(symbole)].fass)
#define symboles_est_reference(symbole) (es[(symbole)].s_ref)


void symboles_init(void); /* Fait */
/* A UTILISER AVANT TOUT !!!! */


void symboles_afficher_table(void); /* fait */
void symboles_afficher_table_triee(void); /* fait */

int symboles_nouveau (char *image); /* fait */
/*
renvoie le numero du nouveau symbole cree.
   SYMBOLES_PLEINS en cas d'echec

   ATTENTION : image doit etre une chaine valide cree AVANT d'appeler cette
   fonction. I.e que cette fonction ne cree pas de copie de la chaine passee 
   en parametre.
*/

int symboles_detruire( int le_symbole );
/* renvoie 1 en cas de succes
   0 en cas d'echec ( destruction d'un symbole inexistant )
   !! il faut detruire a la main la chaine correspondante !!
*/

int symboles_presence_de ( char *image);
/* Renvoie NON_PRESENT en cas d'absence de la table,
   et sa reference externe sinon 
*/


//char * symboles_image( int symbole );
/* NULL Si le symbole n'existe pas */

/*int symboles_est_reference( int symbole );*/
/* 
   NON_REFERENCE sinon
   si oui => Numero de son referencement dans la table des doublets
*/ 

void symboles_set_reference( int symbole , int doublet );
/* 
   entree : le no de symbole a modifier ( trouve avec presence_de )
            le no de doublet le referencent 
*/ 

void symboles_associe_fonction(int symbole, int (*f)());
/* 
   associe une fonction f au symbole 
   exemple d'utilisation : 
   symbole_associe_fonction(symbole_presence_de("add"),Fplus);
*/

//void *symboles_fonction_associee( int symbole );
/*
  renvoie la fonction associee au symbole,
  NULL si aucune fonction n'est associee 
  exemples:
  BON :
         int (*fonc)(int); // declaration d'une variable de passage 
         fonc=symboles_fonction_associee(symboles_presence_de("Fistule"));
         (*fonc)(2); // appel effectif
  MAUVAIS :
         (*symboles_fonction_associee(symboles_presence_de("Fistule")))(2);

*/
int symboles_nutiles(void);
/* 
   Renvoie le nombre de symboles presents dans la table des symboles
*/
int symboles_nlibre(void);
/*
  renvoie le nombre de symbole libre
*/


#endif
