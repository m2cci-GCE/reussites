#include <stdio.h>
#include "C4.h"

/* Tas de départ */
Tas LigneTalonC4[DerniereCouleur+1];
Tas TalonC4;
Tas LigneC4[DerniereCouleur+1];
int TasCourant = PremiereCouleur;

/* Localisation des 4 tas de départ */
Localisation LocLigneTalonC4[DerniereCouleur+1];
Localisation LocTalonC4;
Localisation LocLigneC4[DerniereCouleur+1];


/* Placement initial des tas */
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

/* Création de la situation initiale de jeu */
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

		/* Creer les 4 tas vides pour le tirage*/
		CreerTasVide(LocLigneC4[i],etale,&LigneC4[i]);
	}
}

/* Reformer le jeu entre chaque partie */
void ReformerJeuInitialC4()
{
	Couleur Co;

	/* On reforme le talon puis on le mélange */
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		EmpilerTas(&LigneC4[Co]);
		RetournerTas(&LigneC4[Co]);
		PoserTasSurTas(&LigneC4[Co],&TalonC4);
	}
	BattreTas(&TalonC4);

	/* On redistrubue les cartes en 4 tas de 8 cartes */
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		int j;
		for (j=0 ; j<8 ; j++)
		{
			DeplacerHautSur(&TalonC4,&LigneTalonC4[Co]);
		}
	}
}	

/* Affiche les tas avec leurs labels eventuels*/
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

/* Déroulement d'une partie de jeu */
void JouerUneC4(booleen* Status, ModeTrace MT)
{
	Couleur Co,CoSource,CoDestination;
	struct adCarte * AC;

	CreerJeuInitialC4();
	
	/* première étape du jeu */
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		RetournerCarteSur(&LigneTalonC4[Co]);
	}
        if (MT==AvecTrace)
        {
	AfficherC4();
        }
	
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
		if (MT==AvecTrace)
		{
		AfficherC4();
		}
	}
	while (!TasVide(LigneTalonC4[CoSource]));
	
	/*deuxieme étape du jeu apres avoir fini le tas où l'on doit piocher */
	for (CoSource = PremiereCouleur; CoSource<=DerniereCouleur; CoSource++)
	{
		while (!TasVide(LigneTalonC4[CoSource]))
		{
			DeplacerHautSur(&LigneTalonC4[CoSource],&LigneC4[CoSource]);
			if (!TasVide(LigneTalonC4[CoSource]))
			{
				RetournerCarteSur(&LigneTalonC4[CoSource]);
			}
			if(MT==AvecTrace)
			{
				AfficherC4();
			}
		}
	}
	
	/* gagné ou perdu ? Vérification des couleurs des différents tas */
	*Status = vrai;
	for (CoSource = PremiereCouleur ; CoSource<=DerniereCouleur ; CoSource++)
	{
		AC=LigneC4[CoSource].tete;
		while((AC != NULL)&&(AC->elt.CC==CoSource))
		{
			AC=AC->suiv;
		}
		if (AC != NULL)
		{
			*Status = faux;
			break;
		}
	}
}

void ObserverC4(int NP)
{
	booleen Status;
	int i=0;

	/* Première partie */
	CreerJeuInitialC4();
	JouerUneC4(&Status,AvecTrace);
	Status==vrai?printf("Vous avez gagné la partie %d !\n",i+1):printf("Vous avez perdu la partie %d !\n",i+1);

	/* Suivantes si elles existent */
	for (i=1 ; i<=NP-1 ; i++) 
	{
		ReformerJeuInitialC4();
		JouerUneC4(&Status, AvecTrace);
		Status==vrai?printf("Vous avez gagné la partie %d !\n",i+1):printf("Vous avez perdu la partie %d !\n",i+1);
	}      
}        

void AnalyserC4(int NP)
{
	int i;
	booleen Status;
	int G=0;
	int P=0;
	double taux;
	for (i=1; i<=NP ; i++)
	{
		JouerUneC4(&Status,SansTrace);
		ReformerJeuInitialC4();
		Status==vrai?G++:P++;
	}

	taux=100.0*(double)G/(double)NP;

	/* Affichage des données : nb de parties jouées, gagnées et du taux de réussite */
	printf("Sur %d partie(s) jouée(s) vous en aves gagné %d et perdu %d.\n",NP,G,P);
	printf("Taux de réussite : %.2lf%\n",taux);
}
