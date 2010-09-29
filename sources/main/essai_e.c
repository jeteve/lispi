#include <syntax.h>
#include <entree.h>
#include <lexico.h>
#include <stdio.h>
#include <stdlib.h>
#include <utiles.h>
#include <symboles.h>
#include <doublet.h>
#include <eval.h>
#include <env.h>

#include <signal.h>
#define DUMP_FILE_NAME "last_session"

void panic_dump_env(void){
  // Procedure de dump de l'environnement 
  // dans le fichier DUMP_FILE_NAME
  FILE * f ;
  
  fprintf(stderr," \nTentative de sauvegarde de l'environnement \n");
  fprintf(stderr,"dans le fichier %s .\n",DUMP_FILE_NAME);
  if((f=fopen(DUMP_FILE_NAME,"w"))!=NULL){
  env_dump(f);
  fclose(f);
  fprintf(stderr," :-D  REUSSI ( ouf ) !! \n");
  fprintf(stderr," \"\"\"  Relancer le programme et faite ( load \'%s ) \n",
	  DUMP_FILE_NAME);
  fprintf(stderr,"         pour restaurer l'environnement courant.\n");
 
  return ;
  }
  fprintf(stderr, " °+( NON-REUSSI ( desole ).\n");
}

void s_handler(int s){
  switch(s){
  case SIGINT : fprintf(stderr," \n * recu signal SIGINT  *\n");break;
  case SIGSEGV :  fprintf(stderr," \n * recu signal SIGSEGV  *\n");break;
  case SIGUSR1 :   fprintf(stderr," \n * recu signal SIGUSR1  *\n");break;
  }

  panic_dump_env();
  fprintf(stderr,"  \n\n ! QUITTEZ PAR [CONTROL-D] LA PROCHAINE FOIS !\n");
  exit(1);
}
  
  


int main(int argc,char *argv[])
{
  int phrase_lue;
  int result;
  int zero=0;
  
  signal(SIGINT,s_handler);
  signal(SIGSEGV,s_handler);
  signal(SIGUSR1,s_handler);
 
	 doublet_initialisation();
  symboles_init();
  
  init_table_symboles();
  init_env();
  eval_init();

  fprintf(stdout, "\n  [ LISPInterpreteur Version 1.0 , Eteve-Ceol ] \n\n      Bienvenue. Tapez Control-D pour sortir. \n\n%d>  ", entree_ligne_courante());
  entree_set_entree(stdin);
  lexico_init_get_token();
  lexico_get_token();
  do
    {
      syntax_init_syntax();
      syntax_phrase(&phrase_lue);
      if( syntax_error())
	{
	  // ELIMINONS CETTE PHRASE
	  doublet_restituer(phrase_lue);
	  printf( ":-( Ce n'est pas du lisp  !! \n\n%d> ", entree_ligne_courante());
	}
      else
	{ 
	  if(eval_phrase(phrase_lue,&result)==ECHEC) eval_print_appels() ;
	  // Apres l'appel de eval, on peut eliminer la phrase lue
	  doublet_restituer(phrase_lue);
	  doublet_garder(result);
	  
	  putchar('=');
	  ecrire_phrase(result,&zero);
	  // Le resultat est ecrit, on peut l'eliminer
	  doublet_restituer(result);
	  printf( "\n\n%d> ",entree_ligne_courante());
	}
      lexico_get_token();
    }
  while ( lexico_token_courant() != FIN_FICHIER );
  // printf(" WARNING : Premature end of file \n");
  panic_dump_env();
  fprintf(stdout,"\n\n :-) A Bientot, %s ... \n",getenv("USER"));
  exit(0);

}
