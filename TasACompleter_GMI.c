/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              
   modifie par F. Carrier, juillet 2012
   --> types enumeres : Couleur, Rang
   --> tas representes par des listes chainees
----------------------------------------------------------------*/

#include "Tas.h"
#include "Alea.h"

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs et rangs */

/* Couleurs */
/* Ordre croissant sur les couleurs: trefle, carreau, coeur, pique */

Couleur CouleurSuivante(Couleur C) {
	C<DerniereCouleur?C++:C=PremiereCouleur;
return C;
}

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

Rang RangSuivant(Rang R) {
	C<DerniereRang?R++:R=PremierRang;
return R;
}

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

	/* Testeurs et selecteurs */
	
Rang LeRang(Carte C) {
return C.RC;
}

Couleur LaCouleur(Carte C) {
return C.CC;
}

Visibilite EstCachee(Carte C) {
return C.VC == faux;
}

Visibilite EstDecouverte(Carte C) {
return C.VC == vrai;
}

	/* Comparaison de cartes */
/*compare si le rang de C1 est plus petit que C2*/	
booleen RangInferieur(Carte C1, Carte C2) {
return LeRang(C1) < LeRang(C2);
}
/*compare si le rang de C1 est le meme que C2*/
booleen MemeRang(Carte C1, Carte C2) {
return LeRang(C1) == LeRang(C2;
}
/*compare si le couleur de C1 est plus petit que C2*/
booleen CouleurInferieure(Carte C1, Carte C2) {
return LaCouleur(C1) < LaCouleur(C2);
}

booleen MemeCouleur(Carte C1, Carte C2) {
return LaCouleur(C1) == Lacouleur(C2);
}

booleen EstCarteAvant(Carte C1, Carte C2) {
return	CouleurInferieure(C1,C2) || (MemeCouleur (C1,C2) && RangInferieur(C1,C2)); 
}

/* Representation des tas */
	
	/* Testeurs et selecteurs */
	
booleen TasActif(Tas T) {
return T.RT == actif;
}

booleen TasVide(Tas T) {
return T.HT == 0;
}

booleen TasEmpile(Tas T) {
return T.MT == empile;
}

booleen TasEtale(Tas T) {
return T.MT == etale;
}

int LaHauteur(Tas T) {
return T.HT;
}

Localisation LaPlace(Tas T) {
return T.LT;
}

	/* Constructeurs */
	
/* *************************************************************
void CreerTasVide(Localisation L, Mode M, Tas *T)
associe � T un tas vide actif plac� en L et de mode d'�talement M.
Pr�-condition : l'emplacement L est disponible
**************************************************************** */
void CreerTasVide(Localisation L, Mode M, Tas *T) {
	T = (Tas *) malloc (sizeof(tas));
	T->LT = L;
	T->MT = M;
	T->RT = actif;
	T->HT = 0;
	T->tete = NULL;
	T->queue= NULL;
}

/* *************************************************************
void SupprimerTasVide(Tas *T)
rend le tas vide inactif. En particulier, la place qu'il occupait
devient libre pour un autre tas.
Pr�-condition : le tas T est vide et actif
**************************************************************** */
void SupprimerTasVide(Tas *T) {
	T->LT = 0;
	T->RT = inactif;
	/*free(T); ????*/
}

/* *************************************************************
void CreerJeuNeuf(int N, Localisation L, Tas *T)
forme en L le tas empil� T avec l'ensemble des N cartes du jeu dans
l'ordre des cartes et faces cach�es.
Donne leur valeur aux variables globales NbCartes et PremierRang.
Pr�-condition : l'emplacement L est libre
                N==52 ou N==32
**************************************************************** */
void CreerJeuNeuf(int N, Localisation L, Tas *T) {
	Mode M;
	Couleur C;
	Rang R;
	int i;
	struct adCarte* AC;
	M=empile;
	CreerTasVide(L, M , &T); 
	T->HT = N;
	if (N==52)
	{
		PremierRang = deux;
		NbCartes = 52;
	}
	else
	{
		PremierRang = sept;
		NbCartes = 32;
	}
	for (C=PremiereCouleur ; C<=DerniereCouleur ; C++)
	{
		for (R=PremierRang; R<=DerniereRang ; R++)
		{ 			
				AC = (struct adCarte *) malloc (sizeof(struct adCarte));
				T->queue->suiv=AC;
				AC->prec=T->queue;
				AC->suiv=NULL;
				(AC->elt).VC= faux;
				(AC->elt).RC= R;
				(AC->elt).CC= C;
				T->queue=AC;					
		}	
	}
	T->tete=AC;
	i=1;
	while (i<=N)
	{
		T->tete=T->tete->prec;
		i++;
	} 
	T->tete->prec=NULL;
}

	/* Consultation des cartes d'un tas: ne deplace pas la carte */
	
/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T) {
return T.queue.elt;
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T) {
return T.tete.elt;
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Pr�condition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i) {
	if (i<=(T.HT))
	{	
		n=1;
		struct adCarte * AC;
		AC=T.tete;
		while (n<i)
		{
			AC=AC->suiv;
		}
	}
return AC.elt;
}

	/* Retournement d'une carte sur un tas */
	
/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte situ�e au dessus du tas T.
Pr�-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T) {
	if ((T->HT)!=0)
	{	
		Carte C;
		C=CarteSur(&T);
		C.VC=vrai;
	}
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte situ�e au dessous du tas T.
Pr�-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T) {
	if ((T->HT)!=0)
	{	
		Carte C;
		C=CarteSous(&T);
		C.VC=vrai;
}

	/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T) {
	int i;
	Localisation=LocCarte[T->HT];
	for (i=1; i<=T->HT; i++)
	{
		LocCarte[i].NL=(T->LT).NL;
		LocCarte[i].NC=(T->LT).NC;
	}
}

void EtalerTas(Tas *T) {
	int i;
	Localisation=LocCarte[T->HT];
	for (i=1; i<=T->HT; i++)
	{
		LocCarte[i].NL=(T->LT).NL+0.4*i;
		LocCarte[i].NC=(T->LT).NC+0.4*i;
	}

}

	
/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T) {
	struct adCarte * Ai, Aj, tmp;
	if (((T->HT != i)&(T->HT != j))&(i != j))
	{
		Ai = T->tete;
		Aj = T->queue;	
		while ((Ai!=NULL)&&((Ai->elt).RC!=i))
		{
			Ai=Ai->suiv;
		}
		while ((Aj!=NULL)&&((Aj->elt).RC!=j))
		{
			Aj=Aj->prec;
		}
	tmp = (struct adCarte *) malloc (sizeof(struct adCarte));
	tmp->elt=Ai->elt;
	Ai->elt=Aj->elt;
	Aj->elt=tmp->elt;
	free(tmp);
	}
}

/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
**************************************************************** */
void BattreTas(Tas *T) {
	int k,n,i,j;
	n=T->HT;
	for (k=1; k<=n; k++)
	{
		i=UnEntier(n);
		j=UnEntier(n);
		EchangerCartes(i,j, &T);
	}
}

/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T) {
	struct adCarte * tmp, AC;
	tmp=T->tete;
	T->tete=T->queue;
	T->queue=tmp;
	while (tmp!=NULL)
	{
		AC=tmp->prec;
		tmp->prec=tmp->suiv;
		tmp->suiv=AC
		tmp->elt.VC=!(tmp->elt.VC);
		tmp=tmp->prec;
	}
}

	/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (struct adCarte *ac, Tas *T) {
	ac->prec=T->queue;
	ac->suiv=NULL;
	T->queue->suiv=ac;
	T->queue=ac;
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (struct adCarte *ac, Tas *T) {
	ac->suiv=T->tete;
	ac->prec=NULL;
	T->tete->prec=ac;
	T->tete=ac;
}

/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessus de T2
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2) {
	struct adCarte *ac;
	ac=T1->queue;
	T1->queue=T1->queue->prec;
	T1->queue->suiv=NULL;
	AjouterCarteSurTas(&ac, &T2);
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessus de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2) {
	struct adCarte *ac;
	ac=T1->queue;
	T1->queue=T1->queue->prec;
	T1->queue->suiv=NULL;
	AjouterCarteSousTas (&ac, &T2);
	
	
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enl�ve la carte situ�e au dessous de T1 et la place au dessus de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2) {
	struct adCarte * ac;
	ac=T1->tete;
	T1->tete=T->tete->suiv;
	T1->tete->prec=NULL;
	AjouterCarteSurTas(&ac, &T2);
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enl�ve la carte situ�e au dessous de T1 et la place au dessous de T2.
Pr�-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2) {
	struct adCarte * ac;
	ac=T1->tete;
	T1->tete=T->tete->suiv;
	T1->tete->prec=NULL;
	AjouterCarteSousTas (&ac, &T2);
	
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enl�ve du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pr�-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2) {
	struct adCarte * ac;
	ac=T1->tete:
	while ((ac!=NULL)&&(ac->elt.CC!=C)&(ac->elt.RC!=R))
	{
		ac=ac->suiv;
	}
	if (ac!=NULL)
	{
		AjouterCarteSurTas(&ac, &T2);
	}
	/*else cette carte n'existe pas dans le tas*/
}

/* ******************************************************************************
void PoserTasSurTas(Tas *T1, Tas *T2)
pose le tas T1 sur le tas T2.
Les deux tas doivent avoir le m�me mode d'�talement.
A l'�tat final, le tas T1 est vide mais toujours actif, et le tas T2 comporte (de bas en
haut) toutes les cartes qu'il avait au d�part puis toutes les cartes de T1 dans l'ordre
qu'elles avaient au d�part dans chacun des tas.
Cette op�ration ne modifie ni la visibilit� des cartes, ni la localisation des tas T1 et T2,
ni leur mode d'�talement.
********************************************************************************* */
void PoserTasSurTas(Tas *T1, Tas *T2) {
	if ((T1->MT)=(T2->MT))
	{
		T1->tete->prec=T2->queue;
		T2->queue->suiv=T1->tete;
		T2->tete=T1->tete;
		T1->tete=NULL;
		T1->queue=NULL;
		
	}
}


