/*--------------------------------------------------------------*/
/* Reussites. Cecile Dumas, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>

/* Interaction avec l'utilisateur */

/* ----------------------------------------------------------
 * CONSTANTES 
 * ----------------------------------------------------------
*/

#define         NbMaxEssais              5 
#define         Invite                   "Votre Choix (? pour liste des commandes) : " 
#define         TexteSimulationCarre     '1' 
#define         TexteAnalyseCarre        '2' 
#define         TexteFin                 'F' 
#define         TexteAide                '?' 

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULR7, ANALYSER7, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULCARRE, ANALYSECARRE, FIN}     CodeCommande ;

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
    ((c == TexteSimulationCarre) ||
     (c == TexteAnalyseCarre) ||
     (c == TexteFin)) ;
}

void EcrireMenu ()
{
  printf ("Tapez \n") ; 
  printf ("%c pour Simulation graphique de la reussite Carré, \n",TexteSimulationCarre) ; 
  printf (" %c pour Analyse d une serie de reussites Carré (sans affichage graphique), \n",TexteAnalyseCarre);
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
    case TexteSimulationCarre : *CC = SIMULCARRE ; break ;
    case TexteAnalyseCarre :    *CC = ANALYSECARRE ; break ;
    case TexteFin :          *CC = FIN ; break ;
    } 
} 
