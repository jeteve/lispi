#include <pile.h>

int  main(void)
{
  int n;
  Pile la_pile = pile_nouvelle();
  
  

  pile_retire(la_pile,&n);
  pile_pousse(la_pile,1);
  pile_pousse(la_pile,3);
  pile_pousse(la_pile,4);

  pile_print(la_pile);
  return 0;
}
