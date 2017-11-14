
/*--------------------------*/
/* A la queue leu leu (QLL) */
/*--------------------------*/

#include <stdio.h>

#include "QLL.h"

#define c 2

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
		LocSeriesQLL[i].NL = c ; 
	}
}

void CreerTableauInitialQLL(int NbCarteJeu) {
	
	SaisirLocTasQLL();
	
	/* Création du talon avec un jeu de 32 ou 52 cartes */
	CreerJeuNeuf(NbCarteJeu, LocTalonQLL, &TalonQLL);
	BattreTas(&TalonQLL);
	
	/* Création des tas de la ligne de jeu */
	int i;
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
	printf("Tableau vidé \n");
	PoserTasSurTas(&(LigneQLL[0]), &TalonQLL);
	RetournerTas(&TalonQLL);

	/* Création des tas de la ligne de jeu */
	int i;
	for (i = 0 ; i < L ; i++) {
		CreerTasVide(LocSeriesQLL[i], empile, &(LigneQLL[i]));
		DeplacerHautSur(&TalonQLL, &(LigneQLL[i]));
		RetournerCarteSur(&(LigneQLL[i]));
	}
	printf("Création ligne neuve \n");

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
	LocSeriesQLL[L].NC = LocSeriesQLL[L-1].NC + 1 ;
	LocSeriesQLL[L].NL = c;
	printf("Localisation Carte tirée : %d -- %d \n", LocSeriesQLL[L].NC, LocSeriesQLL[L].NL);
	CreerTasVide(LocSeriesQLL[L], empile, &(LigneQLL[L]));
	DeplacerHautSur(T, &(LigneQLL[L]));
	RetournerCarteSur(&(LigneQLL[L]));
	L = L+1 ;
	if ( MT == AvecTrace ) {
		AfficherQLL(); /* */
	}
}

int ComparerTas(Tas Tdroite, Tas Tgauche) {
	printf("ComparerTas \n");
	booleen OK = faux;
	if ( MemeRang(CarteSur(Tdroite), CarteSur(Tgauche)) || MemeCouleur(CarteSur(Tdroite), CarteSur(Tgauche)) ) {
		OK = vrai ;
	}
	return OK;
}

void ParcourirTas(Tas *TabT, ModeTrace MT){
	printf("ParcourirTas \n");
	printf("L = %d \n",L);
	booleen stable = faux;
	int k;
	int i;
	i=1;
	while (!stable) {
		booleen mouv = faux;
		printf("i = %d \n",i);
		while ( (L-i) >= 2 && !(ComparerTas(TabT[L-i], TabT[L-2-i])) ) {
			i = i+1;
			printf("i = %d \n",i);
		}

		printf("L-i = : %d \n", L-i);
		if ( (L-i) >= 2 ) {
			printf("rentre \n");
			for (k = 0 ; k < L-1 ; k++) {
		
				printf("k = %d \n", k);
				printf("L = %d \n",L);
				PoserTasSurTas(&(TabT[L-1-i+k]), &(TabT[L-2-i+k]));
			}
			L = L-1;
			mouv = vrai;
		}
		
		if ( MT == AvecTrace ) {
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
		AfficherQLL(); /* */
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

}



