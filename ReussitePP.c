
#include <stdio.h>

/* Programme principal */

#include "PP.h"
#include "InteractionPP.h"

/* -------------------------------------------------------------------
 *      PROGRAMME PRINCIPAL AVEC MENU D'INTERACTION
 * -------------------------------------------------------------------
 */
#define         TexteBienvenue           "Bienvenue \n" 
#define         TexteNbASimuler          "Choisissez le nombre de parties a simuler : "
#define		TexteNbCartes		 "Choisissez le nombre de cartes (32 ou 52) : "
#define         TexteNbAAnalyser         "Choisissez le nombre de parties a analyser : "
#define         TexteAuRevoir            "Au revoir \n" 


int main(void)
{
  CodeCommande    Commande ;
  int nbparties ;
  int nbcartes ;

  InitAlea();
 
  printf (TexteBienvenue) ;
  SaisirCommande (&Commande) ;
  while (Commande != FIN) {
    switch  (Commande) {
    case SIMULPP : 
      printf(TexteNbASimuler);
      scanf("%d",&nbparties);
      printf(TexteNbCartes);
      scanf("%d",&nbcartes);
      OuvrirGraphique("PP");
      ObserverPP(nbparties, nbcartes);
      FermerGraphique();
      break ;

    case ANALYSEPP :
      printf(TexteNbAAnalyser);
      scanf("%d",&nbparties);
      printf(TexteNbCartes);
      scanf("%d",&nbcartes);
      AnalyserPP(nbparties,nbcartes);
      break;
    } 
    SaisirCommande (&Commande) ;
    
  } 
  printf (TexteAuRevoir) ;
}
