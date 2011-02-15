/**
 * iutLife O.6
 * \file structures.h
 * \author morgotth
 * \date 2009
 **/
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "gfx/all_gfx.h"
#include <PA9.h>


// LES TYPESPRITES
/*
// Les TypeSprites sont indispensables pour pouvoir mener � bien la detection des collisions
// toutes l'utilit� des variables sont expliqu�s en commentaire
*/
typedef struct TypeSprite
{
	int xCollision; // diff�rence entre l'absicce r�el du sprite et la coordonn�e � fournir pour la detection de collision
	int yCollision; // diff�rence entre l'ordonn�e r�el du sprite et la coordonn�e � fournir pour la detection de collision
	// il faudra additionner les diff�rences au coordonn�e du sprite pour obtenir le point de d�part de la fonction de collision
	int hauteurCollision;// hauteur � fournir pour pouvoir calculer la collision de 2 sprites
	int largeurCollision;// largeur � fournir pour pouvoir calculer la collision de 2 sprites
	
	// pour les valeurs qui suivent, point2=1 si le sprite est compos� de 2 rectangles, sinon point2=0 et le sprite ne comprends qu'un seul rectangle
	int point2;
	int xCollision2; // diff�rence entre l'absicce r�el du sprite et la coordonn�e � fournir pour la detection de collision
	int yCollision2; // diff�rence entre l'ordonn�e r�el du sprite et la coordonn�e � fournir pour la detection de collision
	// m�me id�e que les 1e declaration mais utile lorsque le sprite est compos� de 2 rectangles
	int hauteurCollision2;// 2e hauteur � fournir si le sprite a �t� d�compos� en 2 rectangles
	int largeurCollision2;// 2e largeur � fournir si le sprite a �t� d�compos� en 2 rectangles
}TypeSprite;


// LES SPRITES
/*
// un sprite standart poss�dent les informations neccessaire � tout sprites :
// des coordonnees (x et y), 
// un num�ro d'�cran (1 pour �cran du haut ou 0 pour bas),
// enfin le num�ro du sprite sur l'�cran
*/
typedef struct Sprite
{
	int numEcran;// 0 = ecran du bas, 1=ecran du haut, -1=dualSprite
	int numSprite;// le num�ro du sprite
    int x;// abscisse du sprite
    int y;// ordonn�e du sprite
	int nbPV;// nombre de points de vie du sprite
	int numEtape;
	int temps;
	TypeSprite* typeSprite;// divers renseignements sur le sprite en particulier
}Sprite;


// LES TIRS
/*
// ils possedent un �l�ment de la classe sprite qui renseigne les informations standarts
// mais �galement un booleen tirActif qui indique si il est actif ou pas
// vitesseTir et puissanceTir sont des indications propre au type de tir envoy�
*/
typedef struct Tir
{
	Sprite coordonnees;
	int tirActif;
	int directionTir; // 1 pour un tir de bas en haut, 2 pour de haut en bas, 0 pour initialisation(ou divers :/)
	int vitesseTir;
	int puissanceTir;
	int tirPair;
	int typeTir; // 0=miniTir, 1=salveTir, 2=tir
}Tir;

// LES BOSS
/*
// ils possedent un �l�ment de la classe sprite qui renseigne les informations standarts
// mais �galement un booleen tirActif qui indique si il est actif ou pas
// vitesseTir et puissanceTir sont des indications propre au type de tir envoy�
*/
typedef struct Boss
{
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	Sprite sprite4;
	int nombredeSprite;// pour les autres sprites, l'id�e est que tout boss est compos� d'un nombre comme ceci :
	/*
	POUR 4 :
					sprite1				sprite2
					sprite3				sprite4
	le sprite aura comme coordonn�es celle dans coordonnees(.x et .y)
	le sprite2 aura boss.coordonnees.x+64
	le sprite3 aura boss.coordonnees.y+64
	le sprite4 aura boss.coordonnees.x+64 et boss.coordonnees.y+64
	
	POUR 3 :
					sprite1			sprite2
							sprite3
	
	POUR 2 :
							sprite1
							sprite2
	POUR 1 :
					sprite1			sprite2
	*/
	int typeTir;  		 // 0=miniTir, 1=salveTir, 2=tir
	int typeTir2; 		 // -1=pas de tir, 0=miniTir, 1=salveTir, 2=tir
	int origineTir1[2];
	int origineTir2[2];	 // toutes les origines de tir d�pendent de sprite1
	int origineTir3[2];
	/*
	1e ligne :
			origine	X
				Y					
								7	8	9
								4	5	6
								1	2	3
	7 = all� en haut � gauche (x-vitesse ET y-vitesse)
	8 = all� en haut (y-vitesse)
	9 = all� en haut � droite (x+vitesse ET y-vitesse)
	
	4 = all� � gauche (x-vitesse)
	5 = rester fixe (des explications ? :P )
	6 = all� � droite (x+vitesse)
	
	1 = all� en bas � gauche (x-vitesse ET y+vitesse)
	2 = all� en haut (y+vitesse)
	3 = all� en bas � droite (x+vitesse ET y+vitesse)
	
	2e ligne 
	*/
}Boss;


#endif


