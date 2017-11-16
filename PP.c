
/*----------------*/
/* Par paire (PP) */
/*----------------*/

#include <stdio.h>

#include "PP.h"

/* Tableau de jeu */

int NbTas = 5;

Tas TalonPP, RebutPP ;
Tas LignePP[5];
Localisation LocTalonPP, LocRebutPP ;
Localisation LocSeriesPP[5] ;

/* Formation du tableau de jeu initial */

void SaisirLocTasPP() {

	LocTalonPP.NC = 1;
	LocTalonPP.NL = 1;
	LocRebutPP.NC = 1;
	LocRebutPP.NL = 4;

	LocSeriesPP[0].NC = 3;
	LocSeriesPP[0].NL = 1;

	LocSeriesPP[1].NC = 5;
	LocSeriesPP[1].NL = 1;

	LocSeriesPP[2].NC = 4;
	LocSeriesPP[2].NL = 2;

	LocSeriesPP[3].NC = 3;
	LocSeriesPP[3].NL = 3;

	LocSeriesPP[4].NC = 5;
	LocSeriesPP[4].NL = 3;
}

void CreerTableauInitialPP(int NbCarteJeu) {
	
	SaisirLocTasPP();
	
	/* Creation du talon avec un jeu de 32 ou 52 cartes */
	CreerJeuNeuf(NbCarteJeu, LocTalonPP, &TalonPP);
	BattreTas(&TalonPP);
	
	/* Creation des tas de la ligne de jeu */
	int i;
	NbTas = 5;
	for (i = 0 ; i < NbTas ; i++) {
		CreerTasVide(LocSeriesPP[i], empile, &(LignePP[i]));
		DeplacerHautSur(&TalonPP, &(LignePP[i]));
		DeplacerHautSur(&TalonPP, &(LignePP[i]));
		RetournerCarteSur(&(LignePP[i]));
	}

	/* Creation du rebut */
	CreerTasVide(LocRebutPP, empile, &RebutPP);
}


void ReformerTableauInitialPP() {

	int i;
	for (i = 0 ; i < NbTas ; i++) {
		PoserTasSurTas(&(LignePP[i]), &RebutPP);
	}
	
	struct adCarte * ptC;
	ptC = RebutPP.tete;
	while (ptC != NULL) {
		(*ptC).elt.VC = vrai;
		ptC = (*ptC).suiv;
	}

	RetournerTas(&RebutPP);
	PoserTasSurTas(&RebutPP, &TalonPP);
	BattreTas(&TalonPP);

	int j;
	NbTas = 5;
	for (j = 0 ; j < NbTas ; j++) {
		CreerTasVide(LocSeriesPP[j], empile, &(LignePP[j]));
		DeplacerHautSur(&TalonPP, &(LignePP[j]));
		DeplacerHautSur(&TalonPP, &(LignePP[j]));
		RetournerCarteSur(&(LignePP[j]));
	}

}

void AfficherPP() {

	EffacerGraphique();
	AfficherTas(TalonPP, "Talon");
	AfficherTas(RebutPP, "Rebut");
	
	int i;
	for (i=0 ; i < NbTas ; i++) {
		AfficherTas(LignePP[i], "");
	}

	AttendreCliquer();

}



int ComparerTasPP(int indice, ModeTrace MT, int *jIndice) {
	booleen pareil = faux;
	*jIndice = indice + 1 ;
	if (!TasVide(LignePP[indice])) {
		while ( (*jIndice<NbTas) && (!pareil) ) {		
			if (!TasVide(LignePP[*jIndice])) {
				if ( !(MemeRang(CarteSur(LignePP[indice]),CarteSur(LignePP[*jIndice])))){
					*jIndice = *jIndice + 1 ;
				}
				else {
					pareil = vrai;
				}
			}
			else {
				*jIndice = *jIndice + 1 ;
			}
		}
	}
	return pareil;
}

void ParcourirTasPP(booleen * ptBloc, booleen * ptFini, ModeTrace MT) {
	int nbRetourne = 0;
	int i ;
	int k;
	int j;
	int *ptj = &j;
	booleen toutVide;

	while ( (nbRetourne <= NbTas*2) && (!(*ptFini) )) {
		i = 0 ;
		*ptj = i + 1;

		while ( (i < NbTas) && (!(ComparerTasPP(i, MT, ptj))) ) {
			i = i + 1 ;
			*ptj = i + 1;
		}

		if (i<NbTas) {
			if (TalonPP.HT >= 2) {
				DeplacerHautSur(&(LignePP[i]), &RebutPP);
				DeplacerHautSur(&(LignePP[*ptj]), &RebutPP);
				if (MT==AvecTrace) {AfficherPP();}
				DeplacerHautSur(&TalonPP, &(LignePP[i]));
				RetournerCarteSur(&(LignePP[i]));
				if (MT==AvecTrace) {AfficherPP();}
				DeplacerHautSur(&TalonPP, &(LignePP[*ptj]));
				RetournerCarteSur(&(LignePP[*ptj]));
				if (MT==AvecTrace) {AfficherPP();}
			}
			else if (TalonPP.HT == 1) {
				DeplacerHautSur(&(LignePP[i]), &RebutPP);
				DeplacerHautSur(&(LignePP[*ptj]), &RebutPP);
				if (MT==AvecTrace) {AfficherPP();}
				DeplacerHautSur(&TalonPP, &(LignePP[i]));
				RetournerCarteSur(&(LignePP[i]));
				if (MT==AvecTrace) {AfficherPP();}
				RetournerCarteSur(&(LignePP[*ptj]));
				if (MT==AvecTrace) {AfficherPP();}
			}
			else {
				DeplacerHautSur(&(LignePP[i]), &RebutPP);
				DeplacerHautSur(&(LignePP[*ptj]), &RebutPP);
				if (MT==AvecTrace) {AfficherPP();}
				if (!(TasVide(LignePP[i]))) {
					RetournerCarteSur(&(LignePP[i]));
					if (MT==AvecTrace) {AfficherPP();}
				}
				if (!(TasVide(LignePP[*ptj]))) {
					RetournerCarteSur(&(LignePP[*ptj]));
					if (MT==AvecTrace) {AfficherPP();}
				}
			}

			toutVide = TasVide(LignePP[0]);
			for (k = 1 ; k < NbTas ; k++) {
				toutVide = toutVide && TasVide(LignePP[k]);
			}
			if ( toutVide ) {
				*ptFini = vrai;		
			}
			else {
				i = 0;
				nbRetourne = 0;
			}

		}	
		else {
			nbRetourne = nbRetourne + 1;
			if (nbRetourne <= NbTas) {
				RetournerTas(&(LignePP[nbRetourne-1]));
				if (MT==AvecTrace) {
					AfficherPP();
				}
			}
			else if (nbRetourne > NbTas && nbRetourne <= NbTas*2) {
				RetournerTas(&(LignePP[nbRetourne-1-NbTas]));
				if (MT==AvecTrace) {
					AfficherPP();
				}
			}
		}
	}
	if (nbRetourne > NbTas) {
		*ptBloc = vrai;
	}
}



void JouerUnePP(ModeTrace MT, int NbCarteJeu) {
	booleen bloquer = faux;
	booleen *ptBloquer = &bloquer;
	booleen terminer = faux;
	booleen *ptTerminer = &terminer;
	

	if (MT==AvecTrace) {
		AfficherPP();
	}

	ParcourirTasPP(ptBloquer, ptTerminer, MT);
	
	if (MT==AvecTrace) {
		if (terminer) {
			printf("Vous avez gagné !\n");
		}
		else {
			printf("Vous avez perdu ! \n");
		}
	}
}

void ObserverPP(int NP, int NbCarteJeu) {

	int i;
	
	CreerTableauInitialPP(NbCarteJeu);
	JouerUnePP(AvecTrace, NbCarteJeu);
	for (i = 1 ; i < NP ; i++) {
		ReformerTableauInitialPP();
		JouerUnePP(AvecTrace, NbCarteJeu);
	}
	
}


void AnalyserPP(int NP, int NbCarteJeu) {

	int i;
	int k;
	CreerTableauInitialPP(NbCarteJeu);
	
	int nbP = 0 ; /* Nombre de parties perdues */
	int nbG = 0 ; /* Nombre de parties gagnées */

	booleen toutVide;

	for (i = 1 ; i <= NP ; i++) {
		JouerUnePP(SansTrace, NbCarteJeu);

		toutVide = TasVide(LignePP[0]);
		for (k = 1 ; k < NbTas ; k++) {
			toutVide = toutVide && TasVide(LignePP[k]);
		}

		if (toutVide) {
			nbG = nbG + 1 ;
		}
		else {
			nbP = nbP + 1;
		}
		ReformerTableauInitialPP();
	}
	
	float pct, rg, rp;
	pct = 100.0/(double)NP;
	rg = nbG*pct;
	rp = nbP*pct;

	printf("Nombre de parties jouées : %d \nPourcentage total de parties gagnées : %.2f %% \nPourcentage total de parties perdues : %.2f %% \n",NP, rg, rp);
}









