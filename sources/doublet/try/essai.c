#include "doublet.h"
#include <stdio.h>
#include <stdlib.h>



int main(void) {
  char c;
  int n1, n2, n3;
  doublet_initialisation();
  while(1){
  printf("n nouveau (n car cdr) , s supprimer (s noeud), v voir, sinon sortie \n");
  scanf("%c",&c);
  switch(c)
    {
    case 'n' : scanf("%d", &n1); scanf("%d", &n2); n3 = doublet_nouveau_doublet(n1,n2); 
      if (n3 == -1){ printf("le tableau est déjà plein \n");}else{printf(" ajouté en %d \n", n3);};break;
    case 's' : scanf("%d", &n1); doublet_supprimer_doublet(n1); break;
    case 'v' : doublet_afficher_tout(); break;
    default : exit(0);
    }
  scanf("%c",&c);
  }
}
