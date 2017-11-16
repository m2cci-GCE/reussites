
/*--------------------------*/
/* A la queue leu leu (QLL) */
/*--------------------------*/

#include <stdio.h>

#include "QLL.h"

/* Tableau de jeu */

int L=2 ;
Tas TalonQLL ;
Tas LigneQLL[52] ;
Localisation LocTalonQLL;
Localisation LocSeriesQLL[52];

/* Formation du tableau de jeu initial */

void SaisirLocTasQLL() {
	int i;

	LocTalonQLL.NC = 1;
	LocTalonQLL.NL = 1;

	for (i = 0 ; i < L ; i++) {
		LocSeriesQLL[i].NC = i+2 ;
		LocSeriesQLL[i].NL = 2 ; 
	}
}

void CreerTableauInitialQLL(int NbCarteJeu) {
	
	SaisirLocTasQLL();
	
	/* Création du talon avec un jeu de 32 ou 52 cartes */
	CreerJeuNeuf(NbCarteJeu, LocTalonQLL, &TalonQLL);
	BattreTas(&TalonQLL);
	
	/* Création des tas de la ligne de jeu */
	int i;
	L = 2;
	for (i = 0 ; i < L ; i++) {
		CreerTasVide(LocSeriesQLL[i], empile, &(LigneQLL[i]));
		DeplacerHautSur(&TalonQLL, &(LigneQLL[i]));
		RetournerCarteSur(&(LigneQLL[i]));
	}
}


void ReformerTableauInitialQLL() {
	
	int j;
	for (j = 1 ; j < L ; j ++) {
		PoserTasSurTas(&(LigneQLL[L-j]), &(LigneQLL[L-j-1]));
	}
	PoserTasSurTas(&(LigneQLL[0]), &TalonQLL);
	RetournerTas(&TalonQLL);
	L = 2;
	int i;
	for (i = 0 ; i < 2 ; i++) {
		CreerTasVide(LocSeriesQLL[i], empile, &(LigneQLL[i]));
		DeplacerHautSur(&TalonQLL, &(LigneQLL[i]));
		RetournerCarteSur(&(LigneQLL[i]));
	}

}

void AfficherQLL(){

	EffacerGraphique();
	AfficherTas(TalonQLL, "Talon");

	int i;
	for (i = 0 ; i < L ; i++) {
		AfficherTas(LigneQLL[i], "");
	}

	AttendreCliquer();

}


void JouerTasQLL(Tas *T, ModeTrace MT){

	if ( LocSeriesQLL[L-1].NC == 13 ) {
		LocSeriesQLL[L].NC = 2 ;
		LocSeriesQLL[L].NL = LocSeriesQLL[L-1].NL + 1;
	}
	else {
		LocSeriesQLL[L].NC = LocSeriesQLL[L-1].NC + 1 ;
		LocSeriesQLL[L].NL = LocSeriesQLL[L-1].NL;
	}

	CreerTasVide(LocSeriesQLL[L], empile, &(LigneQLL[L]));
	DeplacerHautSur(T, &(LigneQLL[L]));
	RetournerCarteSur(&(LigneQLL[L]));
	L = L+1 ;
	if ( MT == AvecTrace ) {
		AfficherQLL();
	}
}

int ComparerTas(Tas Tdroite, Tas Tgauche) {
	booleen OK = faux;
	if ( MemeRang(CarteSur(Tdroite), CarteSur(Tgauche)) || MemeCouleur(CarteSur(Tdroite), CarteSur(Tgauche)) ) {
		OK = vrai ;
	}
	return OK;
}

void ParcourirTas(Tas *TabT, ModeTrace MT){
	booleen stable = faux;
	int k;
	int i;
	i=1;
	while (!stable) {
		booleen mouv = faux;
		while ( (L-i) >= 2 && !(ComparerTas(TabT[L-i], TabT[L-2-i])) ) {
			i = i+1;
		}

		if ( (L-i) >= 2 ) {
			for (k = 0 ; k < L-1 ; k++) {
				PoserTasSurTas(&(TabT[L-1-i+k]), &(TabT[L-2-i+k]));
			}
			L = L-1;
			mouv = vrai;
		}
		
		if ( MT == AvecTrace && mouv == vrai ) {
			AfficherQLL();
		}

		if ( L == 2 || !(mouv) ) {
			stable = vrai;
		}
	}
}



void FinPartieQLL(ModeTrace MT) {
	Tas tmp0, tmp1;
	tmp0 = LigneQLL[0];
	tmp1 = LigneQLL[1];
	int i;
	for (i = 2 ; i < L ; i++){
		LigneQLL[i-2] = LigneQLL[i];
	}
	LigneQLL[L-2] = tmp0;
	LigneQLL[L-1] = tmp1;
	
	ParcourirTas(LigneQLL, MT);	
}


void JouerUneQLL(ModeTrace MT, int NbCarteJeu){

	if ( MT == AvecTrace ) {
		AfficherQLL();
	}
	while ( !TasVide(TalonQLL) ) {
		JouerTasQLL(&TalonQLL, MT);
		ParcourirTas(LigneQLL, MT);
	}
	
	if ( TasVide(TalonQLL) && L > 2 ) {
		FinPartieQLL(MT);
		if ( MT == AvecTrace) {
			if ( L <= 2 ) {
				printf("Vous avez gagné !\n");
			}
			else {
				printf("Vous avez perdu !\n");
			}
		}
	}
	else {
		if (MT==AvecTrace) {
			printf("Vous avez gagné !\n");
		}	
	}
}



void ObserverQLL(int NP, int NbCarteJeu){

	int i;
	
	CreerTableauInitialQLL(NbCarteJeu);
	JouerUneQLL(AvecTrace, NbCarteJeu);
	for (i = 1 ; i < NP ; i++) {
		ReformerTableauInitialQLL();
		JouerUneQLL(AvecTrace, NbCarteJeu);
	} 

}

void AnalyserQLL(int NP, int NbCarteJeu){

	int i;
	CreerTableauInitialQLL(NbCarteJeu);
	
	int nbP = 0 ; /* Nombre de parties perdues */
	int nbG = 0 ; /* Nombre de parties gagnées */

	for (i = 1 ; i <= NP ; i++) {
		JouerUneQLL(SansTrace, NbCarteJeu);
		if (L==2) {
			nbG = nbG + 1 ;
		}
		else {
			nbP = nbP + 1;
		}
		ReformerTableauInitialQLL();
	}
	
	float pct, rg, rp;
	pct = 100.0/(double)NP;
	rg = nbG*pct;
	rp = nbP*pct;

	printf("Nombre de parties jouées : %d \nPourcentage total de parties gagnées : %.2f %% \nPourcentage total de parties perdues : %.2f %% \n",NP, rg, rp);

}







