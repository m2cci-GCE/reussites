
#include "Tas.h"

#include <stdio.h>

#include <stdlib.h>

#include <time.h>


int main() {

/* Carte */

	Carte c1;
	c1.CC = Trefle;
	c1.RC = Quatre;
	c1.VC = vrai;

	Carte c2;
	c2.CC = Carreau;
	c2.RC = Quatre;
	c2.VC = faux;

	Carte c3;
	c3.CC = Trefle;
	c3.RC = Cinq;
	c3.VC = vrai;

	Carte c4;
	c4.CC = Pique;
	c4.RC = Dame;
	c4.VC = faux;

/* Fonctions d'appel */

	Couleur res1 = CouleurSuivante(c1.CC);
	printf("Couleur Suivante = %d (Th=Carreau/2)\n", res1);

	Rang res2 = RangSuivant(c2.RC);
	printf("Rang Suivant = %d (Th=Cinq)\n", res2);
	
	Rang res3 = LeRang(c2);
	printf("Le Rang = %d (Th=Quatre)\n", res3);

	Couleur res4 = LaCouleur(c1);
	printf("La Couleur = %d (Th=Trefle/1)\n", res4);

	Visibilite res5 = EstCachee(c1);
	printf("EstCachee = %d (Th=0/faux)\n", res5);

	Visibilite res6 = EstDecouverte(c3);
	printf("EstDecouverte = %d (Th=1/vrai)\n", res6);

	booleen res7 = RangInferieur(c1, c2);
	printf("Rang Inferieur = %d (Th=faux/0) \n", res7);

	booleen res8 = RangInferieur(c2, c3);
	printf("Rang Inferieur = %d (Th=vrai/1) \n", res8);

	booleen res9 = MemeRang(c1, c2);
	printf("Meme Rang = %d (Th=vrai/1) \n", res9);

	booleen res10 = MemeRang(c2, c4);
	printf("Meme Rang = %d (Th=faux/0) \n", res10);

	booleen res11 = CouleurInferieure(c1, c2);
	printf("Couleur Inferieure = %d (Th=vrai/1) \n", res11);

	booleen res12 = CouleurInferieure(c1, c1);
	printf("Couleur Inferieure = %d (Th=faux/0) \n", res12);

	booleen res13 = MemeCouleur(c1, c2);
	printf("Meme Couleur = %d (Th=faux/0) \n", res13);

	booleen res14 = MemeCouleur(c1, c3);
	printf("Meme Couleur = %d (Th=vrai/1) \n", res14);

	booleen res15 = EstCarteAvant(c1, c3);
	printf("EstCarteAvant = %d (Th=vrai/1) \n", res15);

	booleen res16 = EstCarteAvant(c2, c4);
	printf("EstCarteAvant = %d (Th=vrai/1) \n", res16);


/* Tas */

	struct adCarte *adC1;
	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	struct adCarte *adC2;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	struct adCarte *adC3;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	struct adCarte *adC4;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	

	Tas T1;
	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	Tas T2;
	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;


	Tas T3;
	T3.LT.NL = 3 ;
	T3.LT.NC = 3 ; 
	T3.RT = inactif;
	T3.MT = empile;
	T3.HT = 0;


/* Fonctions d'appel pour les tas */

	
	booleen res17 = TasActif(T1);
	printf("TasActif = %d (Th=vrai/1) \n", res17);
 
	booleen res18 = TasActif(T3);
	printf("TasActif = %d (Th=faux/0) \n", res18);

	booleen res19 = TasVide(T1);
	printf("TasVide = %d (Th=faux/0) \n", res19);

	booleen res20 = TasVide(T3);
	printf("TasVide = %d (Th=vrai/1) \n", res20);

	booleen res21 = TasEmpile(T1);
	printf("TasEmpile = %d (Th=vrai/1) \n", res21);

	booleen res22 = TasEmpile(T2);
	printf("TasEmpile = %d (Th=faux/0) \n", res22);

	booleen res23 = TasEtale(T1);
	printf("TasEtale = %d (Th=faux/0) \n", res23);

	booleen res24 = TasEtale(T1);
	printf("TasEtale = %d (Th=vrai/1) \n", res24);

	int res25 = LaHauteur(T1);
	printf("LaHauteur = %d (Th=2) \n", res25);

	int res26 = LaHauteur(T3);
	printf("LaHauteur = %d (Th=0) \n", res26);

	Localisation res27 = LaPlace(T1);
	printf("LaPlace = %d / %d (Th=1,1) \n", res27.NL, res27.NC);


/* Constructeurs */


	Tas T4;
	Localisation Loc;
	Loc.NL = 4;
	Loc.NC = 4;
	CreerTasVide(Loc, empile, &T4);
	printf("Hauteur T4 test CreerTasVide = %d (Th=0)\n",T4.HT);

	SupprimerTasVide(&T4);
	printf("Coord = %d %d (Th=0 / 0)\n",T4.LT.NL, T4.LT.NC);

	Tas T6;
	Localisation Loc2;
	Loc2.NL = 3;
	Loc2.NC = 1;
	CreerJeuNeuf(32, Loc2, &T6);
	printf("Hauteur T6 test CreerJeuNeuf = %d (Th=32)\n",T6.HT);



/* Consultation des cartes d'un tas: ne deplace pas la carte */

	Carte res28 = CarteSur(T1);
	printf("CarteSur = %d %d (Th=12 4)\n", res28.RC, res28.CC);

	Carte res29 = CarteSous(T1);
	printf("CarteSous = %d %d (Th=4 1)\n", res29.RC, res29.CC);

	Carte res30 = IemeCarte(T1, 1);
	printf("IemeCarte = %d %d (Th=4 1)\n", res30.RC, res30.CC);	


/* Retournement d'une carte sur un tas */


	printf("Test RetournerCarteSur Av = %d (Th=c4visible/0)\n", ((*T1.queue).elt).VC);
	RetournerCarteSur(&T1);
	printf("Test RetournerCarteSur Ap = %d (Th=c4visible/1)\n", ((*T1.queue).elt).VC);

	printf("Test RetournerCarteSous Av = %d (Th=c1nonvisible/1)\n", ((*T1.tete).elt).VC);
	RetournerCarteSous(&T1);
	printf("Test RetournerCarteSous Ap = %d (Th=c1nonvisible/0)\n", ((*T1.tete).elt).VC);



/* Modification d'un tas */

	EmpilerTas(&T2);
	printf("Test EmpilerTas %d (Th=T2emplile/0)\n", T2.MT);

	EtalerTas(&T1);
	printf("Test EtalerTas %d (Th=T1etale/1)\n", T1.MT);

	EchangerCartes(2, 3, &T1);
	printf("Test EchangerCartes %d (Th=Carreau/2)\n", ((*T1.tete).elt).CC);

	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;

	InitAlea();	
	BattreTas(&T1);
	printf("Test BattreTas %d (Th=nonPique/4)\n", ((*T1.queue).elt).CC);

	InitAlea();	
	BattreTas(&T1);
	printf("Test BattreTas %d (Th=nonPique/4)\n", ((*T1.queue).elt).CC);

	printf("Test RetournerTas couleur Av c1 = %d \n", ((*T1.tete).elt).CC);	
	printf("Test RetournerTas couleur Av c4 = %d \n", ((*T1.queue).elt).CC);
	RetournerTas(&T1);
	printf("Test RetournerTas couleur Ap c1 = %d (Th=celle de c4 Av/2)\n", ((*T1.tete).elt).CC);
	printf("Test RetournerTas couleur Ap c4 = %d (Th=celle de c1 Av/2)\n", ((*T1.queue).elt).CC);



/* Deplacements de cartes d'un tas sur un autre */


	struct adCarte *ptc;
	ptc = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*ptc).elt = c2;
	
	printf("Test AjouterCarteSurTas Av tete = %d \n", ((*T2.tete).elt).CC);
	printf("Test AjouterCarteSurTas Av queue = %d \n", ((*T2.queue).elt).CC);
	AjouterCarteSurTas (ptc, &T2);
	printf("Test AjouterCarteSurTas Ap tete = %d \n", ((*T2.tete).elt).CC);
	printf("Test AjouterCarteSurTas Ap queue = %d \n", ((*T2.queue).elt).CC);


	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;
	
	printf("Test AjouterCarteSousTas Av tete = %d \n", ((*T2.tete).elt).CC);
	printf("Test AjouterCarteSousTas Av queue = %d \n", ((*T2.queue).elt).CC);	
	AjouterCarteSousTas (ptc, &T2);
	printf("Test AjouterCarteSousTas Ap tete = %d \n", ((*T2.tete).elt).CC);
	printf("Test AjouterCarteSousTas Ap queue = %d \n", ((*T2.queue).elt).CC);


	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC2 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;


	printf("Test DeplacerHautSur Av queue = %d \n", ((*T2.queue).elt).CC);
	DeplacerHautSur(&T1, &T2);
	printf("Test DeplacerHautSur Ap queue = %d \n", ((*T2.queue).elt).CC);



	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;


	printf("Test DeplacerHautSous Av tete = %d \n", ((*T2.tete).elt).CC);
	DeplacerHautSous(&T1, &T2);
	printf("Test DeplacerHautSous Ap tete = %d \n", ((*T2.tete).elt).CC);


	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;


	printf("Test DeplacerBasSur Av queue = %d \n", ((*T2.queue).elt).CC);
	DeplacerBasSur(&T1, &T2);
	printf("Test DeplacerBasSur Ap queue = %d \n", ((*T2.queue).elt).CC);



	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC2 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;

	
	printf("Test DeplacerBasSous Av tete = %d \n", ((*T2.tete).elt).CC);
	DeplacerBasSous(&T1, &T2);
	printf("Test DeplacerBasSous Ap tete = %d \n", ((*T2.tete).elt).CC);



	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = etale;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC4 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;
	
	printf("Test DeplacerCarteSur Av queue = %d \n", ((*T2.queue).elt).CC);
	DeplacerCarteSur(c1.CC, c1.RC, &T1, &T2);
	printf("Test DeplacerCarteSur Ap queue = %d \n", ((*T2.queue).elt).CC);



	adC1 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC1).elt = c1;
	adC2 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC2).elt = c2;
	adC3 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC3).elt = c3;
	adC4 = (struct adCarte *) malloc(sizeof(struct adCarte)); 
	(*adC4).elt = c4;

	T1.LT.NL = 1 ;
	T1.LT.NC = 1 ; 
	T1.RT = actif;
	T1.MT = empile;
	T1.HT = 4;
	T1.tete = adC1 ;
	(*(T1.tete)).suiv = adC2;
	(*(T1.tete)).prec = NULL;
	(*(*T1.tete).suiv).suiv = adC3;
	(*(*T1.tete).suiv).prec = T1.tete;
	(*(*(*T1.tete).suiv).suiv).suiv = T1.queue;
	(*(*(*T1.tete).suiv).suiv).prec = adC2;
	T1.queue = adC4 ;
	(*(T1.queue)).suiv = NULL;
	(*(T1.queue)).prec = adC3;


	T2.LT.NL = 2 ;
	T2.LT.NC = 2 ; 
	T2.RT = actif;
	T2.MT = empile;
	T2.HT = 2;
	T2.tete = adC3 ;
	(*T2.tete).suiv = T2.queue;
	(*T2.tete).prec = NULL;
	T2.queue = adC2 ;
	(*T2.queue).suiv = NULL;
	(*T2.queue).prec = T2.tete;

	T3.LT.NL = 2 ;
	T3.LT.NC = 2 ; 
	T3.RT = actif;
	T3.MT = empile;
	T3.HT = 2;
	T3.tete = adC1 ;
	(*T3.tete).suiv = T3.queue;
	(*T3.tete).prec = NULL;
	T3.queue = adC4 ;
	(*T3.queue).suiv = NULL;
	(*T3.queue).prec = T3.tete;


	printf("Test PoserTasSurTas Av queueT3 = %d \n", ((*T3.queue).elt).CC);
	printf("Test PoserTasSurTas Av queueT2 = %d \n", ((*T2.queue).elt).CC);
	PoserTasSurTas(&T3, &T2);
	printf("Test PoserTasSurTas Ap queueT2 = %d \n", ((*T2.queue).elt).CC);


}










