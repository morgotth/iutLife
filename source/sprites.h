#ifndef SPRITES_H
#define SPRITES_H

#include "structures.h"

// initialisation d'une structure Boss avec le boss demandé (par l'entier numBoss
//void initialisationBoss(Boss boss, int numBoss);
int bi(int y);
unsigned int getTicks();
int nouveauTir (Tir* tabTir,int nbTir,int directionTirSouhaite,int xlanceurDuTir,int yLancementDuTir);

void preparationBoss(Tir* tabSprite);
void destructionBoss(Tir* tabSprite);

#endif

