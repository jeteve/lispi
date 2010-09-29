#ifndef WITH_SYNTAX
#define WITH_SYNTAX
/* 
   jerome eteve arnaud ceol
   maitrise info 2000/2001 USTL
   projet lispi
   fichier syntax.h
   4 octobre 2000
*/

/* la grammaire :
   P ::= atome |
         ' P | ( S
   S ::= ) | P S | . P )

*/

void syntax_init_syntax(void);
  /*  A Appeler Avant tout appel de syntax_phrase !! */
void  syntax_phrase(int *phrase_lue);
/* 
   Il faut imperativement faire un get_token AVANT tout appel de syntax_phrase
*/
int syntax_error(void);
/* retourne 1 si une erreur est apparue, 0 sinon */


#endif;
