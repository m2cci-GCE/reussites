#include <stdio.h>
#include "Carre.h"

/* Tas de départ */
Tas TalonCarre;
Tas CarteCourante;
Tas ListeAs[DerniereCouleur+1];
Tas Carre[DerniereCouleur+1][DernierRang];

/* Localisation des tas de départ */
Localisation LocTalonCarre;
Localisation LocCarteCourante;
Localisation LocListeAs[DerniereCouleur+1];
Localisation LocCarre[DerniereCouleur+1][DernierRang];

/* Placement initial des tas */
void SaisirLocTasCarre()
{
	Couleur Co;
	Rang Rg;

	LocTalonCarre.NC = 1;LocTalonCarre.NL = 2;
	LocCarteCourante.NC = 1;LocCarteCourante.NL = 4;

	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		LocListeAs[Co].NC = Co+4;
		LocListeAs[Co].NL = 5;
	}

	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		for (Rg=7 ; Rg<=DernierRang-1 ; Rg++)
		{
			LocCarre[Co][Rg].NC = Rg-3;
			LocCarre[Co][Rg].NL = Co;
		}
	}
}

/* Création de la situation initiale de jeu */
void CreerJeuInitialCarre()
{
	Couleur Co;
	Rang Rg;

	SaisirLocTasCarre();
	CreerJeuNeuf(32,LocTalonCarre,&TalonCarre);
	BattreTas(&TalonCarre);

	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		for (Rg=7 ; Rg<=DernierRang-1 ; Rg++)
		{
			/* Creer les 4 tas de 8 cartes et les remplis*/
			CreerTasVide(LocCarre[Co][Rg],empile,&Carre[Co][Rg]);
			DeplacerHautSur(&TalonCarre,&Carre[Co][Rg]);
		}
		/* Les 4 tas vides pour les As */
		CreerTasVide(LocListeAs[Co],empile,&ListeAs[Co]);
	}

	/* Le tas vide pour la carte courrante */
	CreerTasVide(LocCarteCourante,empile,&CarteCourante);
}

/* Reformer le jeu entre chaque partie */
void ReformerJeuInitialCarre()
{
	Couleur Co;
	Rang Rg;

	/* On reforme le talon a partir de la matrice de carte */
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		for (Rg=7 ; Rg<=DernierRang-1 ; Rg++)
		{
			RetournerTas(&Carre[Co][Rg]);
			PoserTasSurTas(&Carre[Co][Rg],&TalonCarre);
		}
		/* On reprend les As pour les mettre dans le talon */
		RetournerTas(&ListeAs[Co]);
		PoserTasSurTas(&ListeAs[Co],&TalonCarre);
	}

	BattreTas(&TalonCarre);

	/* On redistribut les cartes */
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		for (Rg=7 ; Rg<=DernierRang-1 ; Rg++)
		{
			CreerTasVide(LocCarre[Co][Rg],empile,&Carre[Co][Rg]);
			DeplacerHautSur(&TalonCarre,&Carre[Co][Rg]);
		}
	}
}	

/* Affiche les tas avec leurs labels eventuels*/
void AfficherCarre()
{
	Couleur Co;
	Rang Rg;

	EffacerGraphique();

	/* Le talon et le tas de la carte courante */
	AfficherTas(TalonCarre,"Talon");
	AfficherTas(CarteCourante,"C. Courante");

	/* Les As */
	AfficherTas(ListeAs[1],"Trefle");
	AfficherTas(ListeAs[2],"Carreau");
	AfficherTas(ListeAs[3],"Coeur");
	AfficherTas(ListeAs[4],"Pique");

	/* La matrice de carte */
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		for (Rg=7 ; Rg<=DernierRang-1 ; Rg++)
		{
			AfficherTas(Carre[Co][Rg],"");
		}
	}
	AttendreCliquer();
}


void JouerUneCarre(booleen * Status, ModeTrace MT)
{
	Couleur Co;
	Rang Rg;

	RetournerCarteSur(&TalonCarre);
	DeplacerHautSur(&TalonCarre,&CarteCourante);
	if (MT==AvecTrace) {AfficherCarre();}

	while (!TasVide(CarteCourante))
	{
		Co = LaCouleur(CarteSur(CarteCourante));
		Rg = LeRang(CarteSur(CarteCourante));

		/* Si la carte courante est un As */
		if (Rg==DernierRang)
		{
			DeplacerHautSur(&CarteCourante,&ListeAs[Co]);
			if (!TasVide(TalonCarre))
			{
				RetournerCarteSur(&TalonCarre);
				DeplacerHautSur(&TalonCarre,&CarteCourante);
			}
			if (MT==AvecTrace) {AfficherCarre();}
		}
		/* Autre carte */
		else
		{
			RetournerCarteSur(&Carre[Co][Rg]);
			if (MT==AvecTrace) {AfficherCarre();}
			DeplacerHautSous(&CarteCourante,&Carre[Co][Rg]);
			DeplacerHautSur(&Carre[Co][Rg],&CarteCourante);
			if (MT==AvecTrace) {AfficherCarre();}
		}
	}

	/* Derniere partie de jeu et vérification si gane ou perdu */
	*Status = vrai;
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		for (Rg=7 ; Rg<=DernierRang-1 ; Rg++)
		{
			if (EstCachee(CarteSur(Carre[Co][Rg])))
			{
				RetournerCarteSur(&Carre[Co][Rg]);
				if (LaCouleur(CarteSur(Carre[Co][Rg])) != Co && LeRang(CarteSur(Carre[Co][Rg])) != Rg)
				{
					*Status = faux;
				}
				if (MT==AvecTrace) {AfficherCarre();}
			}
		}
	}
}

void ObserverCarre(int NP)
{
	booleen Status;
	int i=0;

	/* Première partie */
	CreerJeuInitialCarre();
	JouerUneCarre(&Status,AvecTrace);
	Status==vrai?printf("Vous avez gagné la partie %d !\n",i+1):printf("Vous avez perdu la partie %d !\n",i+1);

	/* Suivantes si elles existent */
	for (i=1 ; i<=NP-1 ; i++)
	{
		ReformerJeuInitialCarre();
		JouerUneCarre(&Status, AvecTrace);
		Status==vrai?printf("Vous avez gagné la partie %d !\n",i+1):printf("Vous avez perdu la partie %d !\n",i+1);
	}
}

void AnalyserCarre(int NP)
{
	int i;
	booleen Status;
	int G=0;
	int P=0;
	double taux;

	CreerJeuInitialCarre();

	for (i=1 ; i<=NP ; i++)
	{
		JouerUneCarre(&Status,SansTrace);
		ReformerJeuInitialCarre();
		Status==vrai?G++:P++;
	}

	taux = 100.0 * (double)G/(double)NP;

	printf("Sur %d partie(s) jouée(s) vous en aves gagné %d et perdu %d.\n",NP,G,P);
	printf("Taux de réussite : %.2lf%%\n",taux);
}
