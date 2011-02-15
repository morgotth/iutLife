/**
 * iutLife O.6
 * \file tirdeplacement.h
 * \author morgotth
 * \date 2009
 **/
#ifndef TIRDEPLACEMENT_H
#define TIRDEPLACEMENT_H

#include "structures.h"

// deplacement 4 directions
void deplacementSpritePad (int, int, int*, int*);
void deplacementSpriteStylet (int, int, int*, int*);

// deplacement horizontal seulement
void deplacementSpriteHorizontalStylet (int numEcran, int numSprite, int* x, const int y, int vitesse);
void deplacementSpriteHorizontalPad (int numEcran, int numSprite, int* x, const int y, int vitesse);

// deplacement DualSprite avec touches directionnelles
void deplacementDualSprite(int numSprite, int*x, int*y);

// deplacement d'un tir
void deplacementTir(Tir* tir);

// deplacement du boss selon le numSprite de numSprite à numSprite+4
void deplacementBoss(Boss* boss, int direction, int vitesse);
int parcoursBoss(Boss* boss, int tabParcours[10][4], int nbEtapes, int compteurTemps);

// script de deplacement
// renvoie vrai si parcours terminé car plus personne ne peut l'effectuer, faux sinon
int parcours0Ecran0(Sprite* tabSprite, int nbSpriteMin, int nbSpriteConcerne);

//void deplacementSprite(Sprite& sprite, int direction, int vitesse=1);
void deplacementSpriteOriginal(int numEcran, int numSprite, int*x, int*y, int direction, int vitesse);
void deplacementSprite(Sprite* sprite, int direction, int vitesse);
int getDirection(Sprite* sprite, int xDest, int yDest);
int getDirectionOriginal(int x, int y, int xDest, int yDest);
int nouveauParcours(Sprite* tabSprite, int nbSpriteMin, int nbSpriteConcerne, int tabParcours[10][4], int nbEtapes, int compteurTemps);

#endif

