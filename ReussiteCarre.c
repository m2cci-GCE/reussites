#include <stdio.h>
#include "Carre.h"
#include "InteractionCarre.h"

#define         TexteBienvenue           "Bienvenue \n" 
#define         TexteNbASimuler          "Choisissez le nombre de parties a simuler : "
#define         TexteNbAAnalyser         "Choisissez le nombre de parties a analyser : "
#define         TexteAuRevoir            "Au revoir \n" 

int main(void)
{
	CodeCommande Commande;
	int nbParties;
	
	InitAlea();

	printf(TexteBienvenue);
	SaisirCommande (&Commande);
	while (Commande != FIN)
	{
		switch (Commande)
		{
			case SIMULCARRE:
				printf(TexteNbASimuler);
				scanf("%d",&nbParties);		
				OuvrirGraphique("Carre");
				ObserverCarre(nbParties);
				FermerGraphique();
				break;
			case ANALYSECARRE:
				printf(TexteNbAAnalyser);
				scanf("%d",&nbParties);
				AnalyserCarre(nbParties);
				break;
		}
		SaisirCommande(&Commande);
	}
	printf (TexteAuRevoir);	

}
