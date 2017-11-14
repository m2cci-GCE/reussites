/*LigneC4 : tableau de 4 tas, un pour chaque couleur

TasCourrant : entier, indice du tas en cours d'utilisation. a e.i. =0 (trefle)


etat initial LigneC4[0] contient 8 cartes (hasard)
						 LigneC4[1] contient 8 cartes
						 LigneC4[2] contient 8 cartes
						 LigneC4[3] contient 8 cartes

tant que LigneC4[TasCourrant] non vide:
	retourner 1ere carte du tas LigneC4[TasCourant]
	placer carte en dessous du tas de la couleur associee
	changer le tas courrant avec le tas cible

decouvre les cartes caches
si elle sont sous le bon tas : gagne!
sinon perdu

*/







#include <stdio.h>
#include "C4.h"
/*Tas de départ*/

Tas LigneTalonC4[DerniereCouleur+1];
Tas TalonC4;
Tas LigneC4[DerniereCouleur+1];
int TasCourant = PremiereCouleur;

/* Localisation des 4 tas de départ*/
Localisation LocLigneTalonC4[DerniereCouleur+1];
Localisation LocTalonC4;
Localisation LocLigneC4[DerniereCouleur+1];


/* Placement initial des tas*/
void SaisirLocTasC4()
{
	LocTalonC4.NC = 1;
	LocTalonC4.NL = 1;

	int i;
	for (i=PremiereCouleur ; i<=DerniereCouleur ; i++)
	{
		LocLigneTalonC4[i].NC = 2+2*i;
		LocLigneTalonC4[i].NL = 1;

		LocLigneC4[i].NC = 2+2*i;
		LocLigneC4[i].NL = 3;
	}
}

void CreerJeuInitialC4()
{
	SaisirLocTasC4();
	CreerJeuNeuf(32,LocTalonC4,&TalonC4);
	BattreTas(&TalonC4);

	int i;
	for (i=PremiereCouleur ; i<=DerniereCouleur ; i++)
	{
		/* Creer les 4 tas de 8 cartes et les remplis*/
		CreerTasVide(LocLigneTalonC4[i],empile,&LigneTalonC4[i]);
		int j;
		for (j=0 ; j<8 ; j++)
		{
			DeplacerHautSur(&TalonC4,&LigneTalonC4[i]);
		}
		BattreTas(&LigneTalonC4[i]);

		/* Creer les 4 tas vides pour le tirage*/
		CreerTasVide(LocLigneC4[i],etale,&LigneC4[i]);
	}
}

void AfficherC4()
{
	EffacerGraphique();
	AfficherTas(LigneTalonC4[1],"Trefle");
	AfficherTas(LigneTalonC4[2],"Carreau");
	AfficherTas(LigneTalonC4[3],"Coeur");
	AfficherTas(LigneTalonC4[4],"Pique");

	int i;
	for (i=PremiereCouleur ; i<=DerniereCouleur ; i++)
	{
		AfficherTas(LigneC4[i],"");
	}
	AttendreCliquer();
}

void JouerUneC4()
{
	Couleur Co,CoSource,CoDestination;

	CreerJeuInitialC4();
	
	/* premier partie du jeu*/
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		RetournerCarteSur(&LigneTalonC4[Co]);
	}

	AfficherC4();
        
	CoSource = 1;
	do
	{
		CoDestination = LaCouleur(LigneTalonC4[CoSource].queue->elt);
		DeplacerHautSur(&LigneTalonC4[CoSource],&LigneC4[CoDestination]);
		if (!TasVide(LigneTalonC4[CoSource]))
		{
			RetournerCarteSur(&LigneTalonC4[CoSource]);
		}
		CoSource = CoDestination;
		AfficherC4();
	}
	while (!TasVide(LigneTalonC4[CoSource]));
	
	/*deuxieme partie du jeu apres avoir fini le premier tas*/
	for (CoSource = PremiereCouleur; CoSource<=DerniereCouleur; CoSource++)
	{
        	while (!TasVide(LigneTalonC4[CoSource]))
        	{	        
        	        DeplacerHautSur(&LigneTalonC4[CoSource],&LigneC4[CoSource]);
        	        if (!TasVide(LigneTalonC4[CoSource]))
        	        {
        	                RetournerCarteSur(&LigneTalonC4[CoSource]);
        	        }
        	        AfficherC4();
        	}
	}
	
	/*gagné ou perdu*/
	booleen Status = vrai;
	for (CoSource = PremiereCouleur ; CoSource<=DerniereCouleur ; CoSource++)
	{
	        struct adCarte * AC;
	        AC=LigneC4[CoSource].tete;
	        while((AC != NULL)&&(AC->elt.CC==CoSource))
	        {
	                AC=AC->suiv;
	        }
	        if (AC != NULL)
	        {
	                Status = faux;
	                break;
	        }
	}
	Status==vrai?printf("Gagné\n"):printf("Perdu\n");
	
	
}
