LigneC4 : tableau de 4 tas, un pour chaque couleur

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









#include <stdio.h>
#include <C4.h>

// Tas de départ
Tas LigneTalonC4[DerniereCouleur+1];
Tas TalonC4;
Tas LigneC4[DerniereCouleur+1];
int TasCourant = PremiereCouleur;

// Localisation des 4 tas de départ
Localisation LocLigneTalonC4[DerniereCouleur+1];
Localisation LocTalonC4;
Localisation LocLigneC4[DerniereCouleur+1];


// Placement initial des tas
void SaisirLocTasC4()
{
	LocTalonC4.NC = 1;
	LocTalonC4.NL = 1;

	for (int i=PremiereCouleur ; i<=DerniereCouleur ; i++)
	{
		LocLigneTalonC4[i].NC = 2+2*i;
		LocLigneTalonC4[i].NL = 1;

		LocLigneC4[i].NC = 2+2*i;
		LocLigneC4[i].NL = 2;
	}
}

void CreerJeuInitialC4()
{
	CreerJeuNeuf(32,LocTalonC4,&TalonC4);
	BattreTas(&TalonC4);

	for (int i=PremiereCouleur ; i<=DerniereCouleur ; i++)
	{
		// Creer les 4 tas de 8 cartes et les remplis
		CreerTasVide(LocLigneTalonC4[i],empile,&LigneTalonC4[i]);
		for (int j=0 ; j<8 ; j++)
		{
			DeplacerHautSur(&TalonC4,&LigneTalonC4[i]);
		}

		// Creer les 4 tas vides pour le tirage
		CreerTasVide(LocLigneC4[i],etale,&LigneC4[i]);
	}
}

