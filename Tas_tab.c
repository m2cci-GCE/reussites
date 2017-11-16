/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              
   modifie par F. Carrier, juillet 2012
   --> types enumeres : Couleur, Rang
   --> tas representes par des listes chainees
----------------------------------------------------------------*/

#include "Tas.h"
#include "Alea.h"
#include <stdio.h>

/*-----------------------------------*/
/* Specifications des objets de base */
/*-----------------------------------*/

/* Couleurs et rangs */

/* Couleurs */
/* Ordre croissant sur les couleurs: trefle, carreau, coeur, pique */

Couleur CouleurSuivante(Couleur C)
{
	if (C<DerniereCouleur) 
	{
		C++;
	} 
	else 
	{	
		C=PremiereCouleur;
	}
	return C;
}

/* Rangs */
/* Ordre croissant sur les rangs: deux, ..., dix, valet, dame, roi, as */

Rang RangSuivant(Rang R)
{
	if (R<DernierRang)
	{
		R++;
	} 
	else 
	{
		R=PremierRang;
	}
	return R;
}

/*--------------------------------------------------------------------*/
/* Representation des primitives de manipulation des cartes et des tas*/
/*--------------------------------------------------------------------*/

/* Representation des cartes */

	/* Testeurs et selecteurs */
	
Rang LeRang(Carte C)
{
	return C.RC;
}

Couleur LaCouleur(Carte C)
{
	return C.CC;
}

Visibilite EstCachee(Carte C)
{
	return !C.VC;
}

Visibilite EstDecouverte(Carte C)
{
	return C.VC;
}

	/* Comparaison de cartes */
/*compare si le rang de C1 est plus petit que C2*/	
booleen RangInferieur(Carte C1, Carte C2)
{
	return (LeRang(C1)<LeRang(C2));
}
/*compare si le rang de C1 est le meme que C2*/
booleen MemeRang(Carte C1, Carte C2)
{
	return (LeRang(C1)==LeRang(C2));
}
/*compare si le couleur de C1 est plus petit que C2*/
booleen CouleurInferieure(Carte C1, Carte C2)
{
	return (LaCouleur(C1)<LaCouleur(C2));
}

booleen MemeCouleur(Carte C1, Carte C2)
{
	return (LaCouleur(C1)==LaCouleur(C2));
}

booleen EstCarteAvant(Carte C1, Carte C2)
{
	return (CouleurInferieure(C1,C2) || (MemeCouleur (C1,C2) && RangInferieur(C1,C2))); 
}

/* Representation des tas */
	
	/* Testeurs et selecteurs */
	
booleen TasActif(Tas T)
{
	return (T.RT==actif);
}

booleen TasVide(Tas T)
{
	return (T.HT==0);
}

booleen TasEmpile(Tas T)
{
	return (T.MT==empile);
}

booleen TasEtale(Tas T)
{
	return (T.MT==etale);
}

int LaHauteur(Tas T)
{
	return T.HT;
}

Localisation LaPlace(Tas T)
{
	return T.LT;
}

	/* Constructeurs */
	
/* *************************************************************
void CreerTasVide(Localisation L, Mode M, Tas *T)
associe à T un tas vide actif placé en L et de mode d'étalement M.
Pré-condition : l'emplacement L est disponible
**************************************************************** */
void CreerTasVide(Localisation L, Mode M, Tas *T)
{
	T = (Tas *) malloc (sizeof(Tas));
	T->LT = L;
	T->MT = M;
	T->RT = actif;
	T->HT = 0;
}

/* *************************************************************
void SupprimerTasVide(Tas *T)
rend le tas vide inactif. En particulier, la place qu'il occupait
devient libre pour un autre tas.
Pré-condition : le tas T est vide et actif
**************************************************************** */
void SupprimerTasVide(Tas *T) {
	T->LT.NL = 0;
	T->LT.NC = 0;
	T->RT = inactif;
	/*free(T); ????*/
}

/* *************************************************************
void CreerJeuNeuf(int N, Localisation L, Tas *T)
forme en L le tas empilé T avec l'ensemble des N cartes du jeu dans
l'ordre des cartes et faces cachées.
Donne leur valeur aux variables globales NbCartes et PremierRang.
Pré-condition : l'emplacement L est libre
                N==52 ou N==32
**************************************************************** */
void CreerJeuNeuf(int N, Localisation L, Tas *T)
{
  Couleur Co;
  Rang Rg;
	int i;
  CreerTasVide(L,empile,T);

  if (N==52)
  {
    PremierRang = Deux;
    NbCartes = 52;
		T->HT = 52;
  }
  else
  {
    PremierRang = Sept;
    NbCartes = 32;
		T->HT = 32;
  }

  /* génération de la liste de carte */
	i = 0;
  for (Co=PremiereCouleur ; Co<=DerniereCouleur ; Co++)
  {
    for (Rg=PremierRang ; Rg<=DernierRang ; Rg++)
    {
			T->tabCartes[i].CC = Co;
			T->tabCartes[i].RC = Rg;
			T->tabCartes[i].VC = faux;
    }
  }
}

	/* Consultation des cartes d'un tas: ne deplace pas la carte */
	
/* *************************************************************
Carte CarteSur(Tas T) {
carte situee au dessus du tas
**************************************************************** */
Carte CarteSur(Tas T)
{
	return T.tabCarte[T.HT-1];
}

/* *************************************************************
Carte CarteSous(Tas T) {
carte situee au dessous du tas
**************************************************************** */
Carte CarteSous(Tas T)
{
	return T.tabCartes[0];
}

/* *************************************************************
Carte IemeCarte(Tas T, int i)
ieme carte dans T (de bas en haut).
Précondition : i <= LaHauteur(T)
**************************************************************** */
Carte IemeCarte(Tas T, int i)
{
	return T.tabCarte[i-1];
}

	/* Retournement d'une carte sur un tas */
	
/* *************************************************************
void RetournerCarteSur(Tas *T)
retourne la carte située au dessus du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSur(Tas *T) 
{
	T->tabCarte[T->HT-1].VC = !(T->tabCarte[T->HT-1].VC);
}

/* *************************************************************
void RetournerCarteSous(Tas *T)
retourne la carte située au dessous du tas T.
Pré-condition : T non vide
**************************************************************** */
void RetournerCarteSous(Tas *T)
{
	T->tabCarte[0].VC = !(T->tabCarte[0].VC);
}

	/* Modification d'un tas */

/* *************************************************************
void EmpilerTas(Tas *T)
void EtalerTas(Tas *T)
modification du mode d'etalement d'un tas
**************************************************************** */
void EmpilerTas(Tas *T)
{
	T->MT = empile;
}

void EtalerTas(Tas *T)
{
	T->MT = etale;
}

	
/* *************************************************************
void EchangerCartes(int i, int j, Tas *T)
echange les cartes i et j du tas T
Precondition : les deux cartes existent i,j <= LaHauteur(T)
**************************************************************** */
void EchangerCartes(int i, int j, Tas *T)
{
	Carte tmp;

	tmp = T->tabCartes[i-1];
	T->tabCartes[i-1] = T->tabCartes[j-1];
	T->tabCartes[j-1] = tmp;
}

/* *************************************************************
void BattreTas(Tas *T)
bas le tas T
**************************************************************** */
void BattreTas(Tas *T)
{
	int k,n,i,j;
	n=T->HT;
	for (k=1; k<=n; k++)
	{
		i=UnEntier(n);
		j=UnEntier(n);
		EchangerCartes(i, j, T);
	}
}

/* ******************************************************************************
void RetournerTas(Tas *T)
retourne le tas T : la premiere devient la derniere et la visibilite est inversee
********************************************************************************* */
void RetournerTas(Tas *T)
{
	int i;

	for (i=0 ; i<(T->HT)/2 ; i++)
	{
		EchangerCartes(i,(T->HT-1)-i,T);
	}
}


	/* Deplacements de cartes d'un tas sur un autre */


/* ******************************************************************************
void AjouterCarteSurTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sur le tas T
********************************************************************************* */
void AjouterCarteSurTas (Carte c, Tas *T)
{
	T->HT++;
	T->tabCartes[T->HT-1] = c;
}

/* ******************************************************************************
void AjouterCarteSousTas (adCarte *ac, Tas *T)
ajoute la carte d'adresse ac sous le tas T
********************************************************************************* */
void AjouterCarteSousTas (Carte c, Tas *T)
{
	int i;
	T->HT++;
	for (i=T->HT-1 ; i>O ; i--)
	{
		T->tabCartes[i] = T->tabCartes[i-1];
	}
	T->tabCartes[0] = c;
}

/* ******************************************************************************
void DeplacerHautSur(Tas *T1, Tas *T2)
enlève la carte située au dessus de T1 et la place au dessus de T2
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSur(Tas *T1, Tas *T2)
{
	AjouterCarteSurTas(T1->tabCartes[HT-1],T2);
	T1->HT--;
}

/* ******************************************************************************
void DeplacerHautSous(Tas *T1, Tas *T2)
enlève la carte située au dessus de T1 et la place au dessous de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerHautSous(Tas *T1, Tas *T2)
{
	AjouterCarteSousTas(T->tabCartes[HT-1],T2);
	T1->HT--;
}

/* ******************************************************************************
void DeplacerBasSur(Tas *T1, Tas *T2)
enlève la carte située au dessous de T1 et la place au dessus de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSur(Tas *T1, Tas *T2)
{
	int i;
	AjouterCarteSurTas(T1->tabCartes[0],T2);
	for (i=0 ; i<T1->HT-2 ; i++)
	{
		T1->tabCartes[i] = T1->tabCartes[i+1];
	}
	T1->HT--;
}

/* ******************************************************************************
void DeplacerBasSous(Tas *T1, Tas *T2) {
enlève la carte située au dessous de T1 et la place au dessous de T2.
Pré-condition : T1 n'est pas vide, T2 est actif.
********************************************************************************* */
void DeplacerBasSous(Tas *T1, Tas *T2)
{
	int i;
	AjouterCarteSousTas(T1->tabCartes[0],T2);
	for (i=0 ; i<T1->HT-2 ; i++)
	{
		T1->tabCartes[i] = T1->tabCartes[i+1];
	}
	T1->HT--;
}

/* ******************************************************************************
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
enlève du tas T1, la carte de couleur C et de rang R et la place au dessus de T2.
Pré-condition : T1 contient la carte et T2 est actif.
********************************************************************************* */
void DeplacerCarteSur(Couleur C, Rang R, Tas *T1, Tas *T2)
{
	int i,j;
	for (i=0 ; i<=T1->HT-1 ; i++)
	{
		if ((T1->tabCartes[i].CC == C) && (T1->tabCartes[i].RC == R))
		{
			AjouterCarteSurTas(T1->tabCartes[i],T2);
			for (j=i ; j<=T1-HT-1 ; j++)
			{
				T1->tabCartes[i] = T1->tabCartes[i+1];
			}
			T1->HT--;
			break;
		}
	}
}


/* ******************************************************************************
void PoserTasSurTas(Tas *T1, Tas *T2)
pose le tas T1 sur le tas T2.
Les deux tas doivent avoir le même mode d'étalement.
A l'état final, le tas T1 est vide mais toujours actif, et le tas T2 comporte (de bas en
haut) toutes les cartes qu'il avait au départ puis toutes les cartes de T1 dans l'ordre
qu'elles avaient au départ dans chacun des tas.
Cette opération ne modifie ni la visibilité des cartes, ni la localisation des tas T1 et T2,
ni leur mode d'étalement.
********************************************************************************* */
void PoserTasSurTas(Tas *T1, Tas *T2)
{
	int i;
	T2->HT += T1->HT;
	for (i=0 ; i<T1->HT-1 ; i++)
	{
		T2->tabCartes[T2->HT-1+i] = T1->tabCartes[i];
	}
	T1->HT = 0;
}

