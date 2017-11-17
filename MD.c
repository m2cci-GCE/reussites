/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Le relais des 7 */

#include <stdio.h>
#include "MD.h"



char TexteCouleurMD[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};


/* Tableau de jeu */

typedef Tas SerieCouleurMD;
SerieCouleurMD LigneMD[DerniereCouleur+1];

Tas TalonMD;
Tas TStockMD[4];

/* localisation des tas */
Localisation LocSeriesMD[DerniereCouleur+1];
Localisation LocTalonMD;
Localisation LocTStockMD[4];



/* Formation du tableau de jeu initial */

void SaisirLocTasMD(){

  int i, j;	  


  LocTalonMD.NC = 1;
  LocTalonMD.NL = 1;


  for(j=0; j<4; j++){
  	LocTStockMD[j].NC = 2*j+4;
  	LocTStockMD[j].NL = 4;
  }


  for (i=PremiereCouleur; i<=DerniereCouleur; i++)
    {
      LocSeriesMD[i].NC = 2*i+2;
      LocSeriesMD[i].NL = 1;
    }
}



void CreerTableauInitialMD(){

  int j;
  Couleur Co;

  SaisirLocTasMD();

  /* Création du talon avec un jeu de 32 cartes*/
  CreerJeuNeuf(32, LocTalonMD, &TalonMD);
  BattreTas(&TalonMD);


  /*Création des tas de stockage vides*/
  for(j=0; j<4; j++){
  	CreerTasVide(LocTStockMD[j], empile, &(TStockMD[j]));
  }

  /* Création des séries de chaque couleur vides*/
  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++){
	CreerTasVide(LocSeriesMD[Co], empile, &(LigneMD[Co]));
    }
}



void ReformerTableauInitialMD(){

  CreerTableauInitialMD();

  /*int j;
  Couleur Co;
  struct adCarte *i;*/


  /* On reforme le talon, en empilant les cartes des tas de stockage et des séries croissantes */ 
  /*for(j=0; j<4; j++){	  
	RetournerTas(&(TStockMD[j]));
  	PoserTasSurTas(&(TStockMD[j]), &TalonMD);
  }

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++){
	RetournerTas(&(LigneMD[Co]));
	PoserTasSurTas(&(LigneMD[Co]), &TalonMD);
  }

  BattreTas(&TalonMD);

  
  i = TalonMD.tete;

  while(i != NULL){
	(*i).elt.VC = faux;
	i = (*i).suiv;
  }*/
}




/* Visualisation des états du jeu */

void AfficherMD(){

  int j;
  Couleur Co;

  EffacerGraphique();
  AfficherTas(TalonMD, "Talon");

  for(j=0; j<4; j++){
	AfficherTas(TStockMD[j], "Stockage");
  }

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++){
	AfficherTas(LigneMD[Co], TexteCouleurMD[Co]);
  }	

  AttendreCliquer();
}





void PlacerStockMD(Tas *T, booleen *OK){

  int j;
  booleen b = faux;
  Rang RT, RSurTS;

  RT = LeRang(CarteSur(*T));
  j=0;
  

  while(j<=4 && !b){

	if(TasVide(TStockMD[j])){
		DeplacerHautSur(T, &(TStockMD[j]));
		b = vrai;
	}else{
		RSurTS = LeRang(CarteSur(TStockMD[j]));
		if(RT <= RSurTS){
			DeplacerHautSur(T, &(TStockMD[j]));
			b = vrai;
		}else{
			j = j+1;
  		}
	}
  }

  if(j>=4){
	*OK = faux;
  }
}



void JouerTasMD(Tas *T, booleen *OK)
{
  Couleur Co;
  Rang RT, RSur;

  Co = LaCouleur(CarteSur(*T));
  RT = LeRang(CarteSur(*T));

  *OK = vrai;

  if (TasVide(LigneMD[Co])){
	if(RT == Sept){
	        DeplacerHautSur(T, &(LigneMD[Co]));
	}else{
		PlacerStockMD(T, OK);
	}
  }



  else{
	RSur = LeRang(CarteSur(LigneMD[Co]));
	if(RT == RangSuivant(RSur)){
		DeplacerHautSur(T, &(LigneMD[Co]));
	}else{
		PlacerStockMD(T, OK);
	}
  }	
}




void JouerStockMD(Tas *T, ModeTrace MT, booleen *b0){

  *b0 = faux;

  Couleur Co;
  Rang RT, RSurSC;

  if(!TasVide(*T)){

	RT = LeRang(CarteSur(*T));
	Co = LaCouleur(CarteSur(*T));

	if(!TasVide(LigneMD[Co])){
		RSurSC = LeRang(CarteSur(LigneMD[Co]));

		while((!TasVide(*T)) && (!TasVide(LigneMD[Co])) && (RT == RangSuivant(RSurSC))){

			DeplacerHautSur(T, &(LigneMD[Co]));

			if (MT == AvecTrace)				
				AfficherMD();

			if(!TasVide(*T)){
				RT = LeRang(CarteSur(*T));
				Co = LaCouleur(CarteSur(*T));
			}

			if(!TasVide(LigneMD[Co])){
				RSurSC = LeRang(CarteSur(LigneMD[Co]));
			}

			*b0 = vrai;
		}
	}
  }
}






void JouerUnTourMD(ModeTrace MT){
  
  int j;
  booleen b0 = vrai;
 
  booleen OK;

  
  if (MT == AvecTrace)
    AfficherMD();

  do{	/* Jeu du talon, puis des stocks*/ 
      /* On sait que le talon n'est pas vide */
      /* Jouer le talon */
	RetournerCarteSur(&TalonMD);
	if (MT == AvecTrace)
		AfficherMD();
	JouerTasMD(&TalonMD, &OK);
	if (MT == AvecTrace)
		AfficherMD();
	
	j=0;
	while(j<4){
		JouerStockMD(&(TStockMD[j]), MT, &b0);
		j=j+1;

		if(b0){
			j=0;
		}
	}
  }

  while (OK && !TasVide(TalonMD));
}




void JouerUneMD(ModeTrace MT){

  JouerUnTourMD(MT);

  int i;
  booleen b = vrai;

  for(i=0; i<4; i++){
		b = b && TasVide(TStockMD[i]);
  }

  /*N'afficher le résultat que si on est en mode AvecTrace */
  if (MT==AvecTrace) { 
	if (TasVide(TalonMD) && b){
		printf("Vous avez GAGNE !\n");
	}else{
		printf("Vous avez perdu !\n");
	}
  }
}






void ObserverMD(int NP)
{
  int j;

  CreerTableauInitialMD();
  JouerUneMD(AvecTrace);
  for (j = 1; j <= NP-1; j++)
    {
      ReformerTableauInitialMD();
      JouerUneMD(AvecTrace);
    }
}





void AnalyserMD(int NP){

	int i; /* variable pour le parcours des parties (de 1 à NP) */
	int r=0;

	int k;
	booleen b; 


	CreerTableauInitialMD();

	for (i=1 ; i<=NP ; i++) {

		b = vrai;

		JouerUneMD(SansTrace);

		for(k=0; k<4; k++){
			b = b && TasVide(TStockMD[k]);
  		}

		if (TasVide(TalonMD) && b){ /* si le Talon est vide alors c'est qu'on a gagné */
			r = r+1;
		}

		ReformerTableauInitialMD();
	}


	float rg, rp, pct;
	pct = 100.0/(double)NP ;
	rg = r*pct ; /* gagnées */
	rp = 100-rg ; /* perdues */


	printf("Nombre de parties jouées : %d \nPourcentage total de parties gagnees : %.2f %% \nPourcentage total de parties perdues : %.2f %% \n ", NP, rg, rp);
}

