#include "symboles.h"
#include <stdio.h>
int f1(int p)
{
  printf("Appel de f1\n");
  return p;
}

int f2(int p)
{
  printf("appel de f2\n");
  return p;
}

int main(void)
{
  int (*fonc)(int);
  
  symboles_init();
  symboles_nouveau("Blabla");
/*    symboles_nouveau("Arthur"); */
/*    symboles_nouveau("Koala"); */
  symboles_nouveau("Fistule");
  symboles_nouveau("Diantre");

/*    symboles_nouveau("Caca"); */
  symboles_nouveau("Fistule");
  symboles_nouveau("Koala");
 
  symboles_detruire( symboles_presence_de("Blabla"));

  symboles_afficher_table();
  symboles_afficher_table_triee();
  
  printf("Present de Koala : %d \n",symboles_presence_de("Koala"));
  printf("Present de Gateau : %d \n",symboles_presence_de("Gateau"));

  symboles_associe_fonction(
			    symboles_presence_de("Fistule"),f1);

  symboles_associe_fonction(symboles_presence_de("Koala"),f2);
  
  fonc=symboles_fonction_associee(symboles_presence_de("Fistule"));
  (*fonc)(2);
  fonc=symboles_fonction_associee(symboles_presence_de("Koala"));
  (*fonc)(3);

  return 1;

}
