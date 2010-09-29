#ifndef WITH_DOUBLET
#define WITH_DOUBLET
/* 
   Jerome eteve Arnaud ceol
   
   maitrise info 2000/2001
   projet lisp 
   fichier doublet.h 11 octobre 2000
   derniere modif par jay le 12 octobre 2000

*/

#define DOUBLET_INCONNU  -5
#define DOUBLETS_PLEINS -4
#define CODE_SYMBOLE -2
#define CODE_NOMBRE -3
#define CAR 0
#define CDR 1
#define MAX_NOEUDS 5000
#define doublet_car(i) Tdoublet[i][CAR]
#define doublet_cdr(i) Tdoublet[i][CDR]

extern int Tdoublet[MAX_NOEUDS] [2];

void doublet_initialisation(void);
/* initialisation obligatoire avant de commencer */

int doublet_nouveau_doublet(int car, int cdr);
/* renvoie DOUBLETS_PLEINS en cas d'échec, la référence (le noeud) du doublet crée sinon */

int doublet_set_car(int d,int car);
int doublet_set_cdr(int d,int cdr);
/* renvoient DOUBLET_INCONNU si d ou cdr ou car n'existe pas , 0 sinon */


/* int doublet_car(int noeud); */
/* int doublet_cdr(int noeud); */
/* renvoie DOUBLET_INCONNU si le noeud n'existe pas, la valeur contenue dans le car ou le cdr du noeud indiqué sinon */

int doublet_supprimer_doublet( int noeud );
/* renvoie DOUBLET_INCONNU en cas d'erreur, 0 sinon */

void doublet_afficher_tout(void);

/* garbage collector */
void doublet_gc(void);
void doublet_garder(int d);
void doublet_restituer(int d);
void doublet_restituer_jusque(int d,int stop);
/* Restitue et s'arrete sur le doublet stop,
   qu'il soit car ou cdr ...
*/


void doublet_lock(int d);
void doublet_unlock(int d);
/* Empeche toute operation de garder/restituer sur les doublets concernes 
   utiles dans les fonctions repeat ... et while ...
*/

int doublet_fgcInfo(int l, int *r);
int doublet_fgc(int l, int *r);

int doublet_fobList(int l, int *r);

#endif
