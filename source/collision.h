#ifndef COLLISION_H
#define COLLISION_H
#include "structures.h"
/* SOUSPOSITION DANS L'ECRAN :
Pour permettre une méthode optimale de detection des collisions, on a choisi 
de décomposer l'écran de la manière suivante :
4 carrés de largueur sur 3 carrés de hauteur = 
X= 256/4 = 64
Y= 192/3 = 64
Table de 64 : 0 64 128 192 256

MODELISATION :
!!!zone!!!			0-64	64-128	128-192		192-256		=X
0-64				1		2		3			4
64-128				5		6		7			8
128-192				9		10		11			12		
=Y

BONUS :
Autre piste pour code plus précis (à faire si trop de sprites?) :
X= 256/8 = 32
Y= 192/6 = 32
Table de 32 : 0 32 64 96 128 160 192 224 256
*/

// OUTILS DE COLLISION
int sousPosition(int,int); // renvoie la position du point à l'intérieur des "sous-zone" de la ds choisi

int initialisationTableauTypeSpriteGlobal(TypeSprite tab[]); // initialise le tableau de TypeSprite donné avec tout les TypeSprite connu
// renvoie le nombre de cases du tableau qui a été affecté par une affectation

// COLLISION EN ELLE MEME

// renvoie 1 si collision entre les 2 rectangles, 0 sinon
int detectionCollision(int x, int y, int hauteur, int largeur, int x2,int y2, int hauteur2, int largeur2);
int spritesVersDetectionCollision(Sprite* sprite, Sprite* sprite1);

// utilisation des structures TypeSprite et Sprite
// renvoie 1 si collision entre les 2 sprites, 0 sinon
int detectionCollisionSprites(Sprite* s1, Sprite* s2);
//reçoie un sprite et un tir. Si collision, alors ejection des 2 parametres hors de l'écran (en modifiant x et y)
void detectionCollisionSprite_tir_et_destruction(Sprite* s1, Tir* t2);

#endif

