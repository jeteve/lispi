#ifndef WITH_LEXICO
#define WITH_LEXICO
/* 
   Jerome eteve Arnaud ceol
   
   maitrise info 2000/2001
   projet lisp 
   fichier lexico.h 03 octobre 2000
   derniere modif par jay le 3 octobre 2000

*/

/* LES TOKENS ::: */
#define PARENTHESE_OUVRANTE 0
#define PARENTHESE_FERMANTE 1
#define POINT                2
#define APOSTROPHE           3
#define ATOME                4
#define FIN_FICHIER          5

typedef int token;

int lexico_init_get_token(void);
int lexico_get_token(void);
/* 0 en cas de succes, -1 en cas d'erreur ( par exemple caracatere invalide ) */

token lexico_token_courant( void );
/* renvoie le token courant ( apres succes de get_token */


char * lexico_debut_image( void); 
/* renvoie un pointeur sur le debut de la chaine image */   

int    lexico_taille_image(void); 
/* renvoie la taille de la chaine image ( pour utilisation par string copy )
*/


#endif
