
#include <stdio.h>
#include <ctype.h>

/* Interaction avec l'utilisateur */

/* ----------------------------------------------------------
 * CONSTANTES 
 * ----------------------------------------------------------
*/

#define         NbMaxEssais              5 
#define         Invite                   "Votre Choix (? pour liste des commandes) : " 
#define         TexteSimulationPP        '1' 
#define         TexteAnalysePP           '2' 
#define         TexteFin                 'F' 
#define         TexteAide                '?' 

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULPP, ANALYSEPP, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULPP, ANALYSEPP, FIN}     CodeCommande ;

/* -------------------------------------------------------------------
 *      INTERACTION
 *
 *      EstTexteCommande : un caractère ---> un booléen
 *      EcrireMenu       : une action
 *      SaisirCommande   : une action (le résultat : un CodeCommande)
 * -------------------------------------------------------------------
*/

void	LireCar (char	*c)
{	int l ;
	while (isspace ( l=getchar ())) ;  *c = l ; 
}

int EstTexteCommande (char c)
{
  return
    ((c == TexteSimulationPP) ||
     (c == TexteAnalysePP) ||
     (c == TexteFin)) ;
}

void EcrireMenu ()
{
  printf ("Tapez \n") ; 
  printf ("%c pour Simulation graphique de la reussite PP, \n",TexteSimulationPP) ; 
  printf (" %c pour Analyse d une serie de reussites PP (sans affichage graphique), \n",TexteAnalysePP);
  printf (" %c pour Fin, \n",TexteFin);
  printf (" %c pour Aide.\n",TexteAide); 
}


void SaisirCommande (CodeCommande *CC) 
{
  char C  ;
  int  NbEssais ;

  printf (Invite) ; LireCar (&C) ;
  NbEssais = 0 ;
  while ((NbEssais < NbMaxEssais) && (! EstTexteCommande (C))) 
    {
      if (C == TexteAide) 
	{
	  EcrireMenu ()  ; 
	  LireCar (&C) ;
	}
      else 
	{
	  printf ("Commande incorrecte.");
	  NbEssais++ ;
	  if (NbEssais < NbMaxEssais)
	    {
	      printf (Invite) ; 
	      LireCar (&C) ;
	    } 
	}
    } 
  if (NbEssais == NbMaxEssais) 
    *CC = FIN  ;
  else switch (C)  
    {
    case TexteSimulationPP : *CC = SIMULPP ; break ;
    case TexteAnalysePP :    *CC = ANALYSEPP ; break ;
    case TexteFin :          *CC = FIN ; break ;
    } 
} 

