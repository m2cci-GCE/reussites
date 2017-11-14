/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Le relais des 7 */

#include <stdio.h>
#include "MD.h"



char TexteCouleurMD[5][8] = {"", "Trefle", "Carreau", "Coeur", "Pique"};


/* Tableau de jeu */

/*int NumTourMD;*/

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
  /*NumTourMD = 1;*/

  /* Création du talon avec un jeu de 32 cartes et du rebut avec un tas vide */
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

  int j;
  Couleur Co;

  /* On reforme le talon, en empilant les cartes des tas de stockage et des séries croissantes */ 
  for(j=0; j<4; j++){
	  
	RetournerTas(&(TStockMD[j]));
	EmpilerTas(&(TStockMD[j]));
	PoserTasSurTas(&(TStockMD[j]), &TalonMD);
	EmpilerTas(&(TStockMD[j])); 	
  }

  /*PoserTasSurTas(&RebutR7, &TalonR7);*/
  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++){

      RetournerTas(&(LigneMD[Co]));
      EmpilerTas(&(LigneMD[Co]));
      PoserTasSurTas(&(LigneMD[Co]), &TalonMD);
      EmpilerTas(&(LigneMD[Co])); 
    }

  BattreTas(&TalonMD);
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

  for (Co=PremiereCouleur; Co<=DerniereCouleur; Co++)
    AfficherTas(LigneMD[Co], TexteCouleurMD[Co]);
	
  AttendreCliquer();
}







/* Jouer Montee-Descente */

void JouerTasMD(Tas *T, booleen *OK){

  Couleur Co;
  /*Rang RT, RSous, RSur;*/
  Rang RT, RSurSC, RSurTS1, RSurTS2, RSurTS3, RSurTS4;

  Co = LaCouleur(CarteSur(*T));
  RT = LeRang(CarteSur(*T));
  /*RSous = LeRang(CarteSous(LigneMD[Co]));*/
  RSurSC = LeRang(CarteSur(LigneMD[Co]));

  /*RSurTS1 = LeRang(CarteSur(TStockMD[0]));
  RSurTS2 = LeRang(CarteSur(TStockMD[1]));
  RSurTS3 = LeRang(CarteSur(TStockMD[2]));
  RSurTS4 = LeRang(CarteSur(TStockMD[3]));*/

  *OK = vrai;

  if ((RT == RangSuivant(RSurSC)) || (RT == Sept && TasVide(LigneMD[Co])))
    DeplacerHautSur(T, &(LigneMD[Co]));
/*
  else if ((RT <= RSurTS1) || (TasVide(TStockMD[0])))
    DeplacerHautSur(T, &(TStockMD[0]));
  else if ((RT <= RSurTS2) || (TasVide(TStockMD[1])))
    DeplacerHautSur(T, &(TStockMD[1]));
  else if ((RT <= RSurTS3) || (TasVide(TStockMD[2])))
    DeplacerHautSur(T, &(TStockMD[2]));
  else if ((RT <= RSurTS4) || (TasVide(TStockMD[3])))
    DeplacerHautSur(T, &(TStockMD[3]));

  else 
    *OK = faux;
*/

  else{
	if(TasVide(TStockMD[0])){
		DeplacerHautSur(T, &(TStockMD[0]));
	}else{
		RSurTS1 = LeRang(CarteSur(TStockMD[0]));
		if(RT <= RSurTS1){
			DeplacerHautSur(T, &(TStockMD[0]));
		}else{
			if(TasVide(TStockMD[1])){
				DeplacerHautSur(T, &(TStockMD[1]));
			}else{
				RSurTS2 = LeRang(CarteSur(TStockMD[1]));
				if(RT <= RSurTS2){
					DeplacerHautSur(T, &(TStockMD[1]));
				}else{
					if(TasVide(TStockMD[2])){
						DeplacerHautSur(T, &(TStockMD[2]));
					}else{
						if(TasVide(TStockMD[2])){
							DeplacerHautSur(T, &(TStockMD[2]));
						}else{
							RSurTS3 = LeRang(CarteSur(TStockMD[2]));
							if(RT <= RSurTS3){
								DeplacerHautSur(T, &(TStockMD[2]));
							}else{
								if(TasVide(TStockMD[3])){
									DeplacerHautSur(T, &(TStockMD[3]));
								}else{
									RSurTS4 = LeRang(CarteSur(TStockMD[3]));
									if(RT <= RSurTS4){
										DeplacerHautSur(T, &(TStockMD[3]));
									}else{
										*OK = faux;
									}
								}
							}
						}
					}
				}
			}
		}
	}	
  }
}



void JouerStocksMD(Tas *T){

  Couleur Co;
  Rang RT, RSurSC;

  Co = LaCouleur(CarteSur(*T));
  RT = LeRang(CarteSur(*T));
  RSurSC = LeRang(CarteSur(LigneMD[Co]));

  if (RT == RangSuivant(RSurSC))
    DeplacerHautSur(T, &(LigneMD[Co]));
}




void JouerUnTourMD(ModeTrace MT){
  
  int j;
  booleen OK;
  
  if (MT == AvecTrace)
    AfficherMD();

  do{	/* Jeu du talon, puis des stocks*/ 
      /* On sait que le talon n'est pas vide */
      /* Jouer le talon */
      RetournerCarteSur(&TalonMD);
      JouerTasMD(&TalonMD, &OK);
      
      for(j=0; j<4; j++){

      	      JouerStocksMD(&(TStockMD[j]));
      }
/*
      if (!OK)
	      DeplacerHautSur(&TalonR7, &RebutR7);
      if (MT == AvecTrace)
	      AfficherMD();
      while (OK && !TasVide(TalonMD))	{
	      On a joué le talon. Le talon n'est pas vide: on rejoue le talon */
	      /*JouerTasMD(&RebutR7, &OK);
	      if (OK && (MT == AvecTrace))
	         AfficherMD();
	   }*/
  }
  while (OK && !TasVide(TalonMD));
}




void JouerUneMD(ModeTrace MT){

  JouerUnTourMD(MT);
  /* Jeu d'au plus NMaxT tours */
/*
  while (!(TasVide(RebutR7)) && (NumTourR7 < NMaxT))  
    {
      RetournerTas(&RebutR7);
      PoserTasSurTas(&RebutR7, &TalonR7);
      JouerUnTourR7(MT);
      NumTourR7 = NumTourR7 + 1;
    }
  N'afficher le résultat que si on est en mode AvecTrace */
  if (MT==AvecTrace) { 
    if (TasVide(TalonMD))
      {
        printf("Vous avez gagné !\n");
      }
    else
      {
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


}

