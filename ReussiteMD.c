/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>

/* Programme principal */

#include "MD.h"
#include "InteractionMD.h"

/* -------------------------------------------------------------------
 *      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
 * -------------------------------------------------------------------
 */
#define         TexteBienvenue           "Bienvenue \n" 
#define         TexteNbASimuler          "Choisissez le nombre de parties a simuler : "
#define         TexteNbAAnalyser         "Choisissez le nombre de parties a analyser : "
#define         TexteAuRevoir            "Au revoir \n" 

int main(void){

  CodeCommande    Commande ;
  int nbparties ;

  InitAlea();
 
  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
    case SIMULMD : 
      printf(TexteNbASimuler);
      scanf("%d",&nbparties);
      OuvrirGraphique("MD");
      ObserverMD(nbparties);
      FermerGraphique();
      break ;

    case ANALYSEMD :
      printf(TexteNbAAnalyser);
      scanf("%d",&nbparties);
      AnalyserMD(nbparties);
      break;
    } 
    SaisirCommande (&Commande) ;
    
  } 
  printf (TexteAuRevoir) ;
}
	
