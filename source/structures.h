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
// Les TypeSprites sont indispensables pour pouvoir mener à bien la detection des collisions
// toutes l'utilité des variables sont expliqués en commentaire
*/
typedef struct TypeSprite
{
	int xCollision; // différence entre l'absicce réel du sprite et la coordonnée à fournir pour la detection de collision
	int yCollision; // différence entre l'ordonnée réel du sprite et la coordonnée à fournir pour la detection de collision
	// il faudra additionner les différences au coordonnée du sprite pour obtenir le point de départ de la fonction de collision
	int hauteurCollision;// hauteur à fournir pour pouvoir calculer la collision de 2 sprites
	int largeurCollision;// largeur à fournir pour pouvoir calculer la collision de 2 sprites
	
	// pour les valeurs qui suivent, point2=1 si le sprite est composé de 2 rectangles, sinon point2=0 et le sprite ne comprends qu'un seul rectangle
	int point2;
	int xCollision2; // différence entre l'absicce réel du sprite et la coordonnée à fournir pour la detection de collision
	int yCollision2; // différence entre l'ordonnée réel du sprite et la coordonnée à fournir pour la detection de collision
	// même idée que les 1e declaration mais utile lorsque le sprite est composé de 2 rectangles
	int hauteurCollision2;// 2e hauteur à fournir si le sprite a été décomposé en 2 rectangles
	int largeurCollision2;// 2e largeur à fournir si le sprite a été décomposé en 2 rectangles
}TypeSprite;


// LES SPRITES
/*
// un sprite standart possédent les informations neccessaire à tout sprites :
// des coordonnees (x et y), 
// un numéro d'écran (1 pour écran du haut ou 0 pour bas),
// enfin le numéro du sprite sur l'écran
*/
typedef struct Sprite
{
	int numEcran;// 0 = ecran du bas, 1=ecran du haut, -1=dualSprite
	int numSprite;// le numéro du sprite
    int x;// abscisse du sprite
    int y;// ordonnée du sprite
	int nbPV;// nombre de points de vie du sprite
	int numEtape;
	int temps;
	TypeSprite* typeSprite;// divers renseignements sur le sprite en particulier
}Sprite;


// LES TIRS
/*
// ils possedent un élément de la classe sprite qui renseigne les informations standarts
// mais également un booleen tirActif qui indique si il est actif ou pas
// vitesseTir et puissanceTir sont des indications propre au type de tir envoyé
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
// ils possedent un élément de la classe sprite qui renseigne les informations standarts
// mais également un booleen tirActif qui indique si il est actif ou pas
// vitesseTir et puissanceTir sont des indications propre au type de tir envoyé
*/
typedef struct Boss
{
	Sprite sprite1;
	Sprite sprite2;
	Sprite sprite3;
	Sprite sprite4;
	int nombredeSprite;// pour les autres sprites, l'idée est que tout boss est composé d'un nombre comme ceci :
	/*
	POUR 4 :
					sprite1				sprite2
					sprite3				sprite4
	le sprite aura comme coordonnées celle dans coordonnees(.x et .y)
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
	int origineTir2[2];	 // toutes les origines de tir dépendent de sprite1
	int origineTir3[2];
	/*
	1e ligne :
			origine	X
				Y					
								7	8	9
								4	5	6
								1	2	3
	7 = allé en haut à gauche (x-vitesse ET y-vitesse)
	8 = allé en haut (y-vitesse)
	9 = allé en haut à droite (x+vitesse ET y-vitesse)
	
	4 = allé à gauche (x-vitesse)
	5 = rester fixe (des explications ? :P )
	6 = allé à droite (x+vitesse)
	
	1 = allé en bas à gauche (x-vitesse ET y+vitesse)
	2 = allé en haut (y+vitesse)
	3 = allé en bas à droite (x+vitesse ET y+vitesse)
	
	2e ligne 
	*/
}Boss;


#endif


