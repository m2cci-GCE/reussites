#include <stdio.h>
#include "C4.h"
#include "InteractionC4.h"

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
			case SIMULC4:
				printf(TexteNbASimuler);
				scanf("%d",&nbParties);		
				OuvrirGraphique("C4");
				ObserverC4(nbParties);
				FermerGraphique();
				break;
			case ANALYSEC4:
				printf(TexteNbAAnalyser);
				scanf("%d",&nbParties);
				AnalyserC4(nbParties);
				break;
		}
		SaisirCommande(&Commande);
	}
	printf (TexteAuRevoir);	
}
