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

		/* Creer les 4 tas vides pour le tirage*/
		CreerTasVide(LocLigneC4[i],etale,&LigneC4[i]);
	}
}

void ReformerJeuInitialC4()
{
	Couleur Co;
	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		EmpilerTas(&LigneC4[Co]);
		RetournerTas(&LigneC4[Co]);
		PoserTasSurTas(&LigneC4[Co],&TalonC4);
	}
	BattreTas(&TalonC4);

	for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
	{
		int j;
		for (j=0 ; j<8 ; j++)
		{
			DeplacerHautSur(&TalonC4,&LigneTalonC4[Co]);
		}
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

void JouerUneC4(booleen* Status, ModeTrace MT)
{
	Couleur Co,CoSource,CoDestination;

	CreerJeuInitialC4();
	
	/* premier partie du jeu*/
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
        	       if(MT==AvecTrace)
        	       {
        	        AfficherC4();
        	        }
        	}
	}
	
	/*gagné ou perdu*/
	*Status = vrai;
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
	                *Status = faux;
	                break;
	        }
	}
	
	
	
}

void ObserverC4(int NP)
{
        booleen Status;
        int i=0;
        CreerJeuInitialC4();
        JouerUneC4(&Status,AvecTrace);
         Status==vrai?printf("Vous avez gagné la partie %d !\n",i+1):printf("Vous avez perdu la partie %d !\n",i+1);
        
       
        for ( i = 1 ; i <=NP-1 ; i++) 
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
        for ( i=1; i <= NP ; i++)
        {
                JouerUneC4(&Status,SansTrace);
                ReformerJeuInitialC4();  
                Status==vrai?G++:P++;  
        }
        
        taux=100.0*(double)G/(double)NP;
        
        printf("Sur %d partie(s) jouée(s) vous en aves gagné %d et perdu %d.\n",NP,G,P);
        printf("Taux de réussite : %.2lf%\n",taux);
}
