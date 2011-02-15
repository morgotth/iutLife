/**
 * iutLife O.6
 * \file tirdeplacement.c
 * \author morgotth
 * \date 2009
 **/
#include "tirdeplacement.h"

void deplacementSpritePad (int numEcran, int numSprite, int* x, int* y)
// permet de deplacer le sprite num�ro numSprite de l'�cran numEcran gr�ce aux coordonnees fournis
// les x et y en param�tres sont des pointeurs d'entiers pour �tre mis � jour
// le d�placement s'effectuera lorsque l'utilisateur se servira des touches HAUT,BAS,GAUCHE et DROITE de la DS
{
	if(Pad.Newpress.Up || Pad.Held.Up && (*y)>0)
	{
		PA_SetSpriteXY(numEcran,numSprite,*x,--(*y));
	}
	if(Pad.Newpress.Down || Pad.Held.Down && (*y)<(192-30))
	{
		PA_SetSpriteXY(numEcran,numSprite,*x,++(*y));
	}
	if(Pad.Newpress.Left || Pad.Held.Left && (*x)>0)
	{
		PA_SetSpriteXY(numEcran,numSprite,--(*x),*y);
	}
	if(Pad.Newpress.Right || Pad.Held.Right && (*x)<(256-30))
	{
		PA_SetSpriteXY(numEcran,numSprite,++(*x),*y);
	}
}

void deplacementSpriteStylet (int numEcran, int numSprite, int* x, int* y)
// permet de deplacer le sprite num�ro numSprite de l'�cran numEcran gr�ce aux coordonnees fournis
// les x et y en param�tres sont des pointeurs d'entiers pour �tre mis � jour
// le d�placement s'effectuera en fonction des coordonnees du stylet de la DS
{
	// si le stylet est appuy� ou maintenu
	if(Stylus.Held || Stylus.Newpress)
	{
		int X=Stylus.X, Y=Stylus.Y;
		if(!((X>((*x)-1) && X<((*x)+1))&&(Y>((*y)-1) || Y<((*y)+1))))
		// si non(le stylet se trouve presque pr�s du sprite (d�risoire))
		{
			if(X<(*x))
			{
				if(Y<(*y))
					PA_SetSpriteXY(numEcran,numSprite,--(*x),--(*y));
				else
				{
					if(Y==(*y))
						PA_SetSpriteXY(numEcran,numSprite,--(*x),*y);
					else
						PA_SetSpriteXY(numEcran,numSprite,--(*x),++(*y));
				}
			}
			else
			{// donc X>*x
				if(Y<(*y))
					PA_SetSpriteXY(numEcran,numSprite,++(*x),--(*y));
				else
				{
					if(Y==(*y))
						PA_SetSpriteXY(numEcran,numSprite,++(*x),(*y));
					else
						PA_SetSpriteXY(numEcran,numSprite,++(*x),++(*y));
				}
			}
		}
	}
}

void deplacementSpriteHorizontalStylet (int numEcran, int numSprite, int* x, const int y, int vitesse)
/*// permet de deplacer le sprite num�ro numSprite de l'�cran numEcran gr�ce aux coordonnees fournis
// le x en param�tre est un pointeur d'entier pour �tre mis � jour
// le y est un entier, il n'est pas suppos� �tre modifi�
// la vitesse est un entier indiquant de combien de pixels se d�placera le sprite
// le d�placement s'effectuera en fonction des coordonnees du stylet de la DS
// le d�placement ne peut �tre qu'horizontal
*/
{
	// si le stylet est appuy� ou maintenu
	if(Stylus.Held || Stylus.Newpress)
	{
		int X=Stylus.X;
		if(!(X>((*x)-1) && X<((*x)+1)))
		{
			if(X<(*x) && (*x)>(-15))// (*x)>(-5) pour ne pas trop sortir de l'�cran
			{
				(*x)-=vitesse;
				PA_SetSpriteXY(numEcran,numSprite,(*x),y);
			}
			else
			{// donc X>x
				if((*x)<(256-15))// pour ne pas sortir � droite de l'�cran
				{
					(*x)+=vitesse;
					PA_SetSpriteXY(numEcran,numSprite,(*x),y);
				}
			}
		}
	}
}

void deplacementSpriteHorizontalPad (int numEcran, int numSprite, int* x, const int y, int vitesse)
/*// permet de deplacer le sprite num�ro numSprite de l'�cran numEcran gr�ce aux coordonnees fournis
// le x en param�tre est un pointeur d'entier pour �tre mis � jour
// le y est un entier, il n'est pas suppos� �tre modifi�
// la vitesse est un entier indiquant de combien de pixels se d�placera le sprite
// le d�placement s'effectuera en fonction des touches GAUCHE et DROITE de la DS
// le d�placement ne peut �tre qu'horizontal
*/
{
	if((Pad.Newpress.Left || Pad.Held.Left) && (*x)>(-15))// && pour ne pas sortir � gauche de l'�cran
	{
		(*x)-=vitesse;
		PA_SetSpriteXY(numEcran,numSprite,(*x),y);
	}
	if((Pad.Newpress.Right || Pad.Held.Right) && (*x)<(256-15))// && pour ne pas sortir � droite de l'�cran
	{
		(*x)+=vitesse;
		PA_SetSpriteXY(numEcran,numSprite,(*x),y);
	}
}


void deplacementDualSprite(int numSprite, int*x, int*y)
// permet de deplacer le DualSprite num�ro numSprite gr�ce aux coordonnees fournis
// les x et y en param�tres sont des pointeurs d'entiers pour �tre mis � jour
// le d�placement s'effectuera lorsque l'utilisateur se servira des touches HAUT,BAS,GAUCHE et DROITE de la DS
{
	if(Pad.Newpress.Up || Pad.Held.Up)
	{
		PA_DualSetSpriteXY(numSprite,*x,--(*y));
	}
	if(Pad.Newpress.Down || Pad.Held.Down)
	{
		PA_DualSetSpriteXY(numSprite,*x,++(*y));
	}
	if(Pad.Newpress.Left || Pad.Held.Left)
	{
		PA_DualSetSpriteXY(numSprite,--(*x),*y);
	}
	if(Pad.Newpress.Right || Pad.Held.Right)
	{
		PA_DualSetSpriteXY(numSprite,++(*x),*y);
	}
}

void deplacementTir(Tir* tir)
/*// POUR les tirs du joueur == 1
// si le tir vient d'�tre lanc� (donc hors de l'�cran), le x du lanceur du tir est premier �l�ment connu du tir
// si le tir est � l'�cran, il doit simplement se d�placer selon la vitesse propre au tir
// si le tir arrive en haut de l'�cran, il est envoy� hors de l'�cran et cesse d'�tre actif

// POUR les tirs ennemis == 2
// si le tir vient d'�tre lanc� (donc hors de l'�cran), le x du lanceur du tir est premier �l�ment connu du tir
// le y du tir sera le yLancementDuTir
// si le tir est � l'�cran, il doit simplement se d�placer selon la vitesse propre au tir
// si le tir arrive en bas de l'�cran, il est envoy� hors de l'�cran et cesse d'�tre actif
*/
{
	if(tir->tirActif)
	{
		// deplacement des ordonn�es
		if(tir->directionTir==1)
		{
			(tir->coordonnees.y)-=(tir->vitesseTir);
			if((tir->coordonnees.y)<=3)// a fait tout l'�cran
			{
				tir->tirActif=0;
				tir->directionTir=0;// il devient inactif
				tir->coordonnees.x=256; tir->coordonnees.y=414;
			}
			PA_DualSetSpriteXY(tir->coordonnees.numSprite,
						   tir->coordonnees.x,
						   tir->coordonnees.y);
		}
		else if(tir->directionTir==2)
		{
			(tir->coordonnees.y)+=(tir->vitesseTir);
			if((tir->coordonnees.y)>=392)// a fait tout l'�cran
			{
				tir->tirActif=0;
				tir->directionTir=0;// il devient inactif
				tir->coordonnees.x=256; tir->coordonnees.y=414;
			}
			PA_DualSetSpriteXY(tir->coordonnees.numSprite,
						   tir->coordonnees.x,
						   tir->coordonnees.y);
		}
	}
}

void deplacementBoss(Boss* boss, int direction, int vitesse)
/*// deplacement du boss selon le numSprite de numSprite � numSprite+4
// x et y sont ses coordonn�es en haut � gauche, ils impactent les 4 sprites
// la direction est un entier bien pr�cis (voir structure boss) qui indique si c'est HAUT, BAS, GAUCHE ou DROITE
// vitesse est le nombre de pixels du d�placement
*/
{
	switch (direction) {
		case 1 :
			boss->sprite1.x-=vitesse;
			boss->sprite1.y+=vitesse;
			break;
		case 2 :
			boss->sprite1.y+=vitesse;
			break;
		case 3 :
			boss->sprite1.x+=vitesse;
			boss->sprite1.y+=vitesse;
			break;
		case 4 :
			boss->sprite1.x-=vitesse;
			break;
		case 6 :
			boss->sprite1.x+=vitesse;
			break;
		case 7 :
			boss->sprite1.x-=vitesse;
			boss->sprite1.y-=vitesse;
			break;
		case 8 :
			boss->sprite1.y-=vitesse;
			break;
		case 9 :
			boss->sprite1.x+=vitesse;
			boss->sprite1.y-=vitesse;
			break;
		default: // donc 5, on fait du sur place
			break;
	}
	// d�placement avec les coordon�es � jour pour les nbParties sprites
	switch (boss->nombredeSprite) {
		case 4 :
			boss->sprite2.x=boss->sprite1.x+64;
			boss->sprite2.y=boss->sprite1.y;
			boss->sprite3.x=boss->sprite1.x;
			boss->sprite3.y=boss->sprite1.y+32;
			boss->sprite4.x=boss->sprite1.x+64;
			boss->sprite4.y=boss->sprite1.y+32;
			if(boss->sprite1.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite1.numSprite,boss->sprite1.x,boss->sprite1.y);
			if(boss->sprite2.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite2.numSprite,boss->sprite2.x,boss->sprite2.y);
			if(boss->sprite3.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite3.numSprite,boss->sprite3.x,boss->sprite3.y);
			if(boss->sprite4.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite4.numSprite,boss->sprite4.x,boss->sprite4.y);
			break;
		case 3 :
			if(boss->sprite1.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite1.numSprite,boss->sprite1.x,boss->sprite1.y);
			if(boss->sprite2.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite2.numSprite,(boss->sprite1.x+64),boss->sprite1.y);
			if(boss->sprite3.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite3.numSprite,(boss->sprite1.x+32),(boss->sprite1.y+32));
			break;
		case 2 :
			if(boss->sprite1.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite1.numSprite,boss->sprite1.x,boss->sprite1.y);
			if(boss->sprite2.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite2.numSprite,(boss->sprite1.x+64),boss->sprite1.y);
			break;
		default: // par d�faut == 1
			if(boss->sprite1.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite1.numSprite,boss->sprite1.x,boss->sprite1.y);
			if(boss->sprite2.nbPV>0)
				PA_DualSetSpriteXY(boss->sprite2.numSprite,(boss->sprite1.x),(boss->sprite1.y));
			break;
	}
}

void deplacementSpriteOriginal(int numEcran, int numSprite, int*x, int*y, int direction, int vitesse)
// deplacement du Sprite selon les valeurs en param et la direction/vitesse
{
	switch (direction) {
		case 1 :
			(*x)-=vitesse;
			(*y)+=vitesse;
			break;
		case 2 :
			(*y)+=vitesse;
			break;
		case 3 :
			(*x)+=vitesse;
			(*y)+=vitesse;
			break;
		case 4 :
			(*x)-=vitesse;
			break;
		case 6 :
			(*x)+=vitesse;
			break;
		case 7 :
			(*x)-=vitesse;
			(*y)-=vitesse;
			break;
		case 8 :
			(*y)-=vitesse;
			break;
		case 9 :
			(*x)+=vitesse;
			(*y)-=vitesse;
			break;
		default: // donc 5, on fait du sur place
			break;
	}
	// d�placement avec les coordonn�es � jour
	if(numEcran!=-1)
	{
		PA_SetSpriteXY(numEcran,numSprite,(*x),(*y));
	}else{
		PA_DualSetSpriteXY(numSprite,(*x),(*y));
	}
}


void deplacementSprite(Sprite* sprite, int direction, int vitesse)
// deplacement du Sprite en fonction de la direction et de la vitesse fourni
{
	switch (direction) {
		case 1 :
			(sprite->x)-=vitesse;
			(sprite->y)+=vitesse;
			break;
		case 2 :
			(sprite->y)+=vitesse;
			break;
		case 3 :
			(sprite->x)+=vitesse;
			(sprite->y)+=vitesse;
			break;
		case 4 :
			(sprite->x)-=vitesse;
			break;
		case 6 :
			(sprite->x)+=vitesse;
			break;
		case 7 :
			(sprite->x)-=vitesse;
			(sprite->y)-=vitesse;
			break;
		case 8 :
			(sprite->y)-=vitesse;
			break;
		case 9 :
			(sprite->x)+=vitesse;
			(sprite->y)-=vitesse;
			break;
		default: // donc 5, on fait du sur place
			break;
	}
	
	// d�placement avec les coordonn�es � jour
	if(sprite->numEcran!=-1)
	{
		PA_SetSpriteXY(sprite->numEcran,sprite->numSprite,sprite->x,sprite->y);
	}else{
		PA_DualSetSpriteXY(sprite->numSprite,sprite->x,sprite->y);
	}
}

int getDirectionOriginal(int x, int y, int xDest, int yDest)
// renvoie le num�ro indiquant la direction � prendre pour atteindre le point de destination au coordonn�es (xDest,yDest)
// si le point (x,y) est arriv� � sa destination, renvoie 0
{
	int valRetour=0;
	if(		!(xDest>(x-1) && xDest<(x+1))  ||	!(yDest>(y-1) && yDest<(y+1))	)
	// si non(le point se trouve d�j� � sa destination)
	{
		if(xDest<x)
		{
			if(yDest<y)
				valRetour=7;
			else
			{
				if(yDest==y)
					valRetour=4;
				else
					valRetour=1;
			}
		}
		else
		{// donc xDest>*x
			if(yDest<y)
				valRetour=9;
			else
			{
				if(yDest==y)
					valRetour=6;
				else
					valRetour=3;
			}
		}
	}
	return valRetour; // il vaut 0 si on n'est pas rentr� dans le if
}

int getDirection(Sprite* sprite, int xDest, int yDest)
{
	return getDirectionOriginal(sprite->x,sprite->y,xDest,yDest);
}

int parcoursBoss(Boss* boss, int tabParcours[10][4], int nbEtapes, int compteurTemps)
/* // deplace le boss (chaque sprite est espac� par 64 pixels en X ou Y) selon le parcours pr�vu
*/
{
	int completementDetruit=0, valRendu;// cpt, nbDemiSec=(PA_VBLCounter[compteurTemps]/30), impair=PA_VBLCounter[1]%10;
	// au d�part compteurDeTemps indique le temps qui s'est �coul� dans le parcours pour le 1e sprite
	// tant que tout les sprites n'ont pas �t� trait�s et qu'on a pas rencontr� un sprite pour l'instant inactif (donc tout les suivants �galement inactif)
	// inactif si y = 192 ou 392
	// deplacement
	completementDetruit=!(boss->sprite1.nbPV>0 || boss->sprite2.nbPV>0 || boss->sprite3.nbPV>0 || boss->sprite4.nbPV>0);
	if(!completementDetruit && boss->sprite1.numEtape<nbEtapes)
	{
		valRendu=getDirection(&(boss->sprite1), 
								(tabParcours[boss->sprite1.numEtape][0]),
								(tabParcours[boss->sprite1.numEtape][1]));
		deplacementBoss(boss,
						valRendu,
						tabParcours[boss->sprite1.numEtape][2]);
		if(valRendu==0)
		{
			boss->sprite1.numEtape++;
		}
	}//endIf
	
	if(completementDetruit)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int nouveauParcours(Sprite* tabSprite, int nbSpriteMin, int nbSpriteConcerne, int tabParcours[10][4], int nbEtapes, int compteurTemps)
/* // deplace les sprites de nbSpriteMin jusqu'au nbSpriteConcerne ( max = nbSpriteConcerne+nbSpriteMin)
// tabParcours contient les points successifs ou se dirigeront les points.
// nbEtapes est le nombre de points + le d�part ou se situera le 1e point au d�part
// compteurTemps est le nombre du compteur utilis�
*/
{
	int cpt=0, diffX, diffY, valRendu, nbSpriteCourant=nbSpriteMin, nbDemiSec=(PA_VBLCounter[compteurTemps]/30), impair=PA_VBLCounter[1]%10;
	// au d�part compteurDeTemps indique le temps qui s'est �coul� dans le parcours pour le 1e sprite
	// tant que tout les sprites n'ont pas �t� trait�s et qu'on a pas rencontr� un sprite pour l'instant inactif (donc tout les suivants �galement inactif)
	// inactif si y = 192 ou 392
	while(cpt<(nbSpriteConcerne) && impair && (tabSprite[nbSpriteCourant].y!=192 && tabSprite[nbSpriteCourant].y!=392)) // on parcours du premier (cpt initial) au maximum
	{
		// deplacement
		if(tabSprite[nbSpriteCourant].nbPV>0 && tabSprite[nbSpriteCourant].numEtape<nbEtapes)
		{
			if(tabSprite[nbSpriteCourant].numEtape==nbEtapes-1)
			{
				diffX=(tabParcours[tabSprite[nbSpriteCourant].numEtape+1][0])*cpt;
				diffY=(tabParcours[tabSprite[nbSpriteCourant].numEtape+1][1])*cpt;
			}
			else
			{
				diffX=0;
				diffY=0;
			}
			valRendu=getDirection(&(tabSprite[nbSpriteCourant]), 
									(tabParcours[tabSprite[nbSpriteCourant].numEtape][0])-diffX,
									(tabParcours[tabSprite[nbSpriteCourant].numEtape][1])-diffY);
			deplacementSprite(&tabSprite[nbSpriteCourant],
							valRendu,
							tabParcours[tabSprite[nbSpriteCourant].numEtape][2]);
			if(valRendu==0)
			{
				tabSprite[nbSpriteCourant].numEtape++;
			}
		}//endIf
		cpt++;
		nbSpriteCourant=nbSpriteMin+cpt;
		// activation des sprites toutes les secondes
		if((nbDemiSec/2)==(cpt) && (cpt)<nbSpriteConcerne) // activation du prochain
		{
			// activation du suivant
			tabSprite[nbSpriteCourant].x=tabParcours[0][0];
			tabSprite[nbSpriteCourant].y=tabParcours[0][1];
			tabSprite[nbSpriteCourant].nbPV=tabParcours[0][2];
			tabSprite[nbSpriteCourant].numEtape=1;
			// ind�pendemment de si c'est un Dual ou simple Sprite
			if(tabSprite[nbSpriteCourant].numEcran!=-1)
				PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,tabSprite[nbSpriteCourant].x,tabSprite[nbSpriteCourant].y);
			else
				PA_DualSetSpriteXY(tabSprite[nbSpriteCourant].numSprite,tabSprite[nbSpriteCourant].x,tabSprite[nbSpriteCourant].y);
		}
	}
	
	int nbMort=0;
	while(tabSprite[nbSpriteMin+nbMort].nbPV<=0 && nbMort<nbSpriteConcerne)
	{
		nbMort++;
	}
	
	if(nbMort>=nbSpriteConcerne)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int parcours0Ecran0(Sprite* tabSprite, int nbSpriteMin, int nbSpriteConcerne)
/*// param�tres : le tableau de sprite contenant tout le sprites (de l'indice nbSpriteMin pour nbSpriteConcerne = le nombre de sprite concern� par le parcours)
// renvoie vrai si tout est fini (aucun vaisseau ne reste), faux sinon
*/
{
	int cpt=0, nbSpriteCourant, vitesse=1, nbDemiSec=(PA_VBLCounter[1]/30), nbMort=0, impair=PA_VBLCounter[1]%2;
	// au d�part compteurDeTemps indique le temps qui s'est �coul� dans le parcours pour le 1e sprite
	// tant que tout les sprites n'ont pas �t� trait�s et qu'on a pas rencontr� un sprite pour l'instant inactif (donc tout les suivants �galement inactif)
	// inactif si y = 192 ou 392
	while(cpt<(nbSpriteConcerne) && impair) // on parcours du premier (cpt initial) au maximum
	{
		nbSpriteCourant=nbSpriteMin+cpt;
		if(tabSprite[nbSpriteCourant].nbPV>0 && (nbDemiSec)-cpt>0) // il est encore vivant
		{
			if(((nbDemiSec)-cpt)<1)
			{
				tabSprite[nbSpriteCourant].x+=vitesse;
				PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,(tabSprite[nbSpriteCourant].x),(tabSprite[nbSpriteCourant].y));
			}
			else 
			{
				if(((nbDemiSec)-cpt)<3)
				{
					tabSprite[nbSpriteCourant].x+=vitesse;
					tabSprite[nbSpriteCourant].y+=vitesse;
					PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,(tabSprite[nbSpriteCourant].x),(tabSprite[nbSpriteCourant].y));
					if(tabSprite[nbSpriteCourant+1].x>=256 && tabSprite[nbSpriteCourant+1].nbPV>0 && cpt+1<(nbSpriteConcerne)) // activation du prochain
					{
						// activation du suivant
						tabSprite[nbSpriteCourant+1].nbPV=5;
						tabSprite[nbSpriteCourant+1].x=0;
						tabSprite[nbSpriteCourant+1].y=0;
						PA_SetSpriteXY(tabSprite[nbSpriteCourant+1].numEcran,tabSprite[nbSpriteCourant+1].numSprite,tabSprite[nbSpriteCourant+1].x,tabSprite[nbSpriteCourant+1].y);
					}
				}
				else 
				{
					if(((nbDemiSec)-cpt)<(8+(nbSpriteConcerne-cpt)))
					{
						tabSprite[nbSpriteCourant].x+=vitesse;
						PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,(tabSprite[nbSpriteCourant].x),(tabSprite[nbSpriteCourant].y));
					}
					else 
					{
						if(((nbDemiSec)-cpt)<15)
						{
							tabSprite[nbSpriteCourant].x-=vitesse;
							tabSprite[nbSpriteCourant].y+=vitesse;
							PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,(tabSprite[nbSpriteCourant].x),(tabSprite[nbSpriteCourant].y));
						}
						else 
						{
							if(((nbDemiSec)-cpt)<16)
							{
								tabSprite[nbSpriteCourant].x+=vitesse;
								PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,(tabSprite[nbSpriteCourant].x),(tabSprite[nbSpriteCourant].y));
							}
							else 
							{
								if(((nbDemiSec)-cpt)<17)
								{
									tabSprite[nbSpriteCourant].x+=vitesse;
									tabSprite[nbSpriteCourant].y-=vitesse;
									PA_SetSpriteXY(tabSprite[nbSpriteCourant].numEcran,tabSprite[nbSpriteCourant].numSprite,(tabSprite[nbSpriteCourant].x),(tabSprite[nbSpriteCourant].y));
								}
							}
						}
					}
				}
			
			}
		}
		cpt++;
	}
	
	nbMort=0;
	while(tabSprite[nbSpriteMin+cpt].nbPV<=0 && nbMort<nbSpriteConcerne)
	{
		nbMort++;
	}
	
	if(nbMort>=nbSpriteConcerne || nbDemiSec>=15)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


