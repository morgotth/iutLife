/**
 * iutLife O.6
 * \file collision.c
 * \author morgotth
 * \date 2009
 **/
#include "collision.h"

int sousPosition(int x,int y)
/*

MODELISATION :
!!!zone!!!			0-64	64-128	128-192		192-256		=X
0-64				1		2		3			4
64-128				5		6		7			8
128-192				9		10		11			12		
=Y

*/
{
	int i,j,zoneRetour; // moyen de simplifier la recherche
	// POUR LES X
	if(x>128)
	{
		if(x>192)
		{
			// appartient à la zone 4,8 ou 12
			i=4;
		}
		else// x<192
		{
			// appartient à la zone 3,7 ou 11
			i=3;
		}
	}
	else // x<=128
	{
		if(x>64)
		{
			// appartient à la zone 2,6 ou 10
			i=2;
		}
		else
		{
			// appartient à la zone 1,5 ou 9
			i=1;
		}
	}
	
	// pour les Y
	if(y>128)
	{
		// appartient à la zone 9,10,11 ou 12
		j=3;
	}
	else // x<=128
	{
		if(y>64)
		{
			// appartient à la zone 5,6,7 ou 8
			j=2;
		}
		else
		{
			// appartient à la zone 1,2,3 ou 4
			j=1;
		}
	}
	
	// opération pour trouver la zone :
	zoneRetour=(i*10)+j;
	switch(zoneRetour)
	{
		case 11:zoneRetour=1;break;
		case 12:zoneRetour=5;break;
		case 13:zoneRetour=9;break;
		case 21:zoneRetour=2;break;
		case 22:zoneRetour=6;break;
		case 23:zoneRetour=10;break;
		case 31:zoneRetour=3;break;
		case 32:zoneRetour=7;break;
		case 33:zoneRetour=11;break;
		case 41:zoneRetour=4;break;
		case 42:zoneRetour=8;break;
		case 43:zoneRetour=12;break;
		default:/*PA_OutputText(1,2,2,"Problème avec collision");*/break;
	}
	return zoneRetour;
}

int initialisationTableauTypeSpriteGlobal(TypeSprite tab[])
// initialise le tableau de TypeSprite donné avec tout les TypeSprite connu
// ils sont necessaires à la detection des collisions
// il y a un ordre précis d'initialisation pour les indices du tableau qui sera connu par le programmeur
// renvoie le nombre de cases du tableau qui a été affecté par une affectation
/*
0  : Crab frame 0
1  : Crab frame 1

2  : Octopus frame 0
3  : Octopus frame 1

4  : Squid frame 0
5  : Squid frame 1

6  : miniTir
7  : salveTir
8  : Tir
9  : Laser

10 : Asteroide
11 : Joueur
*/
{
	// Crab frame 0
	tab[0].xCollision=0;
	tab[0].yCollision=0; 
	tab[0].hauteurCollision=15;
	tab[0].largeurCollision=22;
	tab[0].point2=0;
	tab[0].xCollision2=5;
	tab[0].yCollision2=1;
	tab[0].hauteurCollision2=16;
	tab[0].largeurCollision2=14;
	
	// Crab frame 1
	tab[1].xCollision=0;
	tab[1].yCollision=4; 
	tab[1].hauteurCollision=10;
	tab[1].largeurCollision=22;
	tab[1].point2=1;
	tab[1].xCollision2=5;
	tab[1].yCollision2=1;
	tab[1].hauteurCollision2=14;
	tab[1].largeurCollision2=12;
	
	// Octopus frame 0
	// 2
	tab[2].xCollision=0;
	tab[2].yCollision=1; 
	tab[2].hauteurCollision=15;
	tab[2].largeurCollision=15;
	tab[2].point2=0;
	tab[2].xCollision2=5;
	tab[2].yCollision2=1;
	tab[2].hauteurCollision2=12;
	tab[2].largeurCollision2=4;
	
	// Octopus frame 1
	// 3
	tab[3].xCollision=0;
	tab[3].yCollision=1; 
	tab[3].hauteurCollision=15;
	tab[3].largeurCollision=16;
	tab[3].point2=0;
	tab[3].xCollision2=5;
	tab[3].yCollision2=1;
	tab[3].hauteurCollision2=12;
	tab[3].largeurCollision2=4;
	
	// Squid frame 0
	// 4
	tab[4].xCollision=0;
	tab[4].yCollision=0; 
	tab[4].hauteurCollision=15;
	tab[4].largeurCollision=20;
	tab[4].point2=1;
	tab[4].xCollision2=5;
	tab[4].yCollision2=1;
	tab[4].hauteurCollision2=14;
	tab[4].largeurCollision2=12;
	
	// Squid frame 1
	// 5
	tab[5].xCollision=0;
	tab[5].yCollision=2; 
	tab[5].hauteurCollision=13;
	tab[5].largeurCollision=20;
	tab[5].point2=0;
	tab[5].xCollision2=4;
	tab[5].yCollision2=1;
	tab[5].hauteurCollision2=12;
	tab[5].largeurCollision2=18;
	
	// miniTir
	// 6
	tab[6].xCollision=0;
	tab[6].yCollision=0; 
	tab[6].hauteurCollision=10;
	tab[6].largeurCollision=14;
	tab[6].point2=0;
	tab[6].xCollision2=0;
	tab[6].yCollision2=0;
	tab[6].hauteurCollision2=10;
	tab[6].largeurCollision2=14;
	
	// salveTir
	// 7
	tab[7].xCollision=0;
	tab[7].yCollision=0; 
	tab[7].hauteurCollision=28;
	tab[7].largeurCollision=10;
	tab[7].point2=0;
	tab[7].xCollision2=0;
	tab[7].yCollision2=0;
	tab[7].hauteurCollision2=28;
	tab[7].largeurCollision2=10;
	
	// Tir
	// 8
	tab[8].xCollision=0;
	tab[8].yCollision=0; 
	tab[8].hauteurCollision=24;
	tab[8].largeurCollision=24;
	tab[8].point2=0;
	tab[8].xCollision2=0;
	tab[8].yCollision2=0;
	tab[8].hauteurCollision2=24;
	tab[8].largeurCollision2=24;
	
	// Laser
	// 9
	tab[9].xCollision=0;
	tab[9].yCollision=1; 
	tab[9].hauteurCollision=54;
	tab[9].largeurCollision=20;
	tab[9].point2=0;
	tab[9].xCollision2=4;
	tab[9].yCollision2=0;
	tab[9].hauteurCollision2=16;
	tab[9].largeurCollision2=20;
	
	// Astéroide
	// 10
	tab[10].xCollision=0;
	tab[10].yCollision=2; 
	tab[10].hauteurCollision=43;
	tab[10].largeurCollision=55;
	tab[10].point2=1;
	tab[10].xCollision2=4;
	tab[10].yCollision2=0;
	tab[10].hauteurCollision2=16;
	tab[10].largeurCollision2=14;
	
	// Joueur
	// 11
	tab[11].xCollision=6;
	tab[11].yCollision=2; 
	tab[11].hauteurCollision=22;
	tab[11].largeurCollision=18;
	tab[11].point2=0;
	tab[11].xCollision2=0;
	tab[11].yCollision2=0;
	tab[11].hauteurCollision2=0;
	tab[11].largeurCollision2=0;
	
	// boss partie 1
	// 15
	tab[15].xCollision=0;
	tab[15].yCollision=0;
	tab[15].hauteurCollision=32;
	tab[15].largeurCollision=64;
	tab[15].point2=0;
	tab[15].xCollision2=4;
	tab[15].yCollision2=0;
	tab[15].hauteurCollision2=16;
	tab[15].largeurCollision2=14;
	
	// boss partie 2
	// 16
	tab[16].xCollision=0;
	tab[16].yCollision=0;
	tab[16].hauteurCollision=32;
	tab[16].largeurCollision=64;
	tab[16].point2=0;
	tab[16].xCollision2=4;
	tab[16].yCollision2=0;
	tab[16].hauteurCollision2=16;
	tab[16].largeurCollision2=14;
	
	// boss partie 3
	// 17
	tab[17].xCollision=0;
	tab[17].yCollision=0;
	tab[17].hauteurCollision=28;
	tab[17].largeurCollision=64;
	tab[17].point2=0;
	tab[17].xCollision2=4;
	tab[17].yCollision2=0;
	tab[17].hauteurCollision2=16;
	tab[17].largeurCollision2=14;
	
	// boss partie 4
	// 18
	tab[18].xCollision=0;
	tab[18].yCollision=0;
	tab[18].hauteurCollision=28;
	tab[18].largeurCollision=64;
	tab[18].point2=0;
	tab[18].xCollision2=4;
	tab[18].yCollision2=0;
	tab[18].hauteurCollision2=16;
	tab[18].largeurCollision2=14;
	
	/*
	tab[].xCollision=0;
	tab[].yCollision=6; 
	tab[].hauteurCollision=8;
	tab[].largeurCollision=22;
	tab[].point2=1;
	tab[].xCollision2=4;
	tab[].yCollision2=0;
	tab[].hauteurCollision2=16;
	tab[].largeurCollision2=14;
	
	tab[].xCollision=0;
	tab[].yCollision=6; 
	tab[].hauteurCollision=8;
	tab[].largeurCollision=22;
	tab[].point2=1;
	tab[].xCollision2=4;
	tab[].yCollision2=0;
	tab[].hauteurCollision2=16;
	tab[].largeurCollision2=14;
	
	tab[].xCollision=0;
	tab[].yCollision=6; 
	tab[].hauteurCollision=8;
	tab[].largeurCollision=22;
	tab[].point2=1;
	tab[].xCollision2=4;
	tab[].yCollision2=0;
	tab[].hauteurCollision2=16;
	tab[].largeurCollision2=14;
	*/
	
	
	return 0;
}

int detectionCollision(int x, int y, int hauteur, int largeur, int x2,int y2, int hauteur2, int largeur2)
// renvoie 1 si collision entre les 2 rectangles, 0 sinon
{
	x+=5;y+=5;largeur-=5;//bug étrange donc les vaisseaux ont un avantage. Le deuxième argument est tout le temps un Tir ...
	if ((x2 >= x - (largeur + largeur2)/2) && (x2 <= x + (largeur + largeur2)/2) && (y2 >= y - (hauteur + hauteur2)/2) && (y2 <= y + (hauteur + hauteur2)/2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int spritesVersDetectionCollision(Sprite* sprite, Sprite* sprite1)
// première version de la detection collision des sprites
{
	return detectionCollision(  sprite->x+(sprite->typeSprite->xCollision), 
								sprite->y+(sprite->typeSprite->yCollision),
								sprite->typeSprite->hauteurCollision,
								sprite->typeSprite->largeurCollision,
								sprite1->x+(sprite1->typeSprite->xCollision), 
								sprite1->y+(sprite1->typeSprite->yCollision), 
								sprite1->typeSprite->hauteurCollision, 
								sprite1->typeSprite->largeurCollision);
}

int detectionCollisionSprites(Sprite* s1, Sprite* s2)
// renvoie 1 si collision entre les 2 sprites, 0 sinon
// utilisation des structures TypeSprite et Sprite
{
	int x1= s1->typeSprite->xCollision, 
		x1R2= s1->typeSprite->xCollision2,
		y1= s1->typeSprite->yCollision, 
		y1R2= s1->typeSprite->yCollision2, 
		// s2
		x2= s2->typeSprite->xCollision, 
		x2R2= s2->typeSprite->xCollision2, 
		y2= s2->typeSprite->yCollision, 
		y2R2= s2->typeSprite->yCollision2, 
		// s1
		hauteur=s1->typeSprite->hauteurCollision, 
		hauteurR2=s1->typeSprite->hauteurCollision2, 
		largeur=s1->typeSprite->largeurCollision, 
		largeurR2=s1->typeSprite->largeurCollision2, 
		// s2
		hauteur2=s2->typeSprite->hauteurCollision, 
		hauteur2R2=s2->typeSprite->hauteurCollision2, 
		largeur2=s2->typeSprite->largeurCollision, 
		largeur2R2=s2->typeSprite->largeurCollision2;
	// fin déclaration de int

	if(s1->numEcran==-1)// s1 est un DualSPrite
	{
		if(s2->numEcran == 0)// et que s2 est dans l'écran du bas
		{
			y1-=200;// 192+8
			y1R2-=200;// 192+8
		}
	}
	if(s2->numEcran==-1)// s2 est un DualSPrite
	{
		if(s1->numEcran == 0)// et que s1 est dans l'écran du bas
		{
			y2-=200;// 192+8
			y2R2-=200;// 192+8
		}
	}
	
	
	if(!detectionCollision((s1->x+x1),(s1->y+y1), hauteur, largeur, (s2->x+x2),(s2->y+y2), hauteur2, largeur2))
	{
		//PA_OutputText(1, 2, 1, "                ");
		// s1->point avec s2->point
		// il n'y a pas eu collision au 1e test
		if(s1->typeSprite->point2)
		{
			// il y a un 2e rectangle pour s1
			// test de s1->point2 avec s2->point
			if(!detectionCollision((s1->x+x1R2),(s1->y+y1R2), hauteurR2, largeurR2, (s2->x+x2),(s2->y+y2), hauteur2, largeur2))
			{
				//PA_OutputText(1, 2, 2, "                ");
				// il n'y a pas eu de collision entre s1->point2 avec s2->point
				if(s2->typeSprite->point2)
				{
					// il n'y a pas de s1->point2 mais il y a un s2->point2
					// test de s1->point avec s2->point2
					if(!detectionCollision((s1->x+x1),(s1->y+y1), hauteur, largeur, (s2->x+x2R2),(s2->y+y2R2), hauteur2R2, largeur2R2))
					{
						//PA_OutputText(1, 2, 3, "                ");
						// s1->point avec s2->point2
						// pas de collision au 3e test !
						
						// il reste le test s1->point2 avec s2->point2
						if(!detectionCollision((s1->x+x1R2),(s1->y+y1R2), hauteurR2, largeurR2, (s2->x+x2R2),(s2->y+y2R2), hauteur2R2, largeur2R2))
						{
							//PA_OutputText(1, 2, 4, "                ");
							// pas de collision entre les 2 points s2
							// plus de choix de tests
							// pas de collision mais beaucoup de tests :'(
							return 0;
						}
						else
						{
							//PA_OutputText(1, 2, 4, "4Collision s1->2 s2->2");
							// collision avec les 2 points s2
							return 1;
						}//fin else
					}
					else
					{
						//PA_OutputText(1, 2, 3, "3Collision s1 s2->2");
						// une collision de s1->point avec s2->point2
						return 1;
					}//fin else
				}
				else
				{
					// pas de s2->point2 et tests déjà fait pour les autres,
					// pas de collision
					return 0;
				}//fin else
			}
			else
			{
				//PA_OutputText(1, 2, 2, "2Collision s1->2 s2->2");
				// collision entre s1->point2 et s2->point
				return 1;
			}//fin else
		}
		else
		{
			// pas de s1->point2
			// test de s2->point2
			if(s2->typeSprite->point2)
			{
				// test de s1->point avec s2->point2
				if(!detectionCollision((s1->x+x1),(s1->y+y1), hauteur, largeur, (s2->x+x2R2),(s2->y+y2R2), hauteur2R2, largeur2R2))
				{
					//PA_OutputText(1, 2, 6, "6Collision s1 s2->2");
					// pas de collision entre s1->point et s2->point2
					// fin des tests
					return 0;
				}
				else
				{
					//PA_OutputText(1, 2, 6, "                  ");
					// collision entre s1->point avec s2->point2
					return 1;
				}//fin else
			}
			else
			{
				//fin des tests, il n'y a pas de point2 pour s1 et s2
				return 0;
			}//fin else
		}//fin else
	}
	else
	{
		//PA_OutputText(1, 2, 1, "1Collision s1 s2");
		// collision entre s1->point et s2->point
		return 1;
	}
	return 1;
}

void detectionCollisionSprite_tir_et_destruction(Sprite* s1, Tir* t2)
// reçoie un sprite et un tir. Si collision, alors ejection des 2 parametres hors de 
// l'écran (en modifiant x et y)
{
	if(detectionCollisionSprites(s1, &t2->coordonnees) && t2->directionTir) 
	// si collision et le tir vient du vaisseau du joueur
	{
		// les tirs sont forcément Dual Sprite, il est donc supprimé
		t2->coordonnees.x=256;
		t2->coordonnees.y=393;
		t2->tirActif=0;
		t2->directionTir=0;
		PA_DualSetSpriteXY(t2->coordonnees.numSprite,t2->coordonnees.x,t2->coordonnees.y);
		
		s1->nbPV-=t2->puissanceTir; // le vaisseau perds donc des points de vie
		if(s1->nbPV<=0) // si le vaisseau n'a plus de point de vie, il disparait
		{
			s1->x=256;
			if(s1->numEcran!=-1) // simple sprite
			{
				s1->y=193;
				PA_SetSpriteXY(s1->numEcran,s1->numSprite,s1->x,s1->y);	
			}
			else 				// Dual Sprite
			{	
				s1->y=393;
				PA_DualSetSpriteXY(s1->numSprite,s1->x,s1->y);
			}
		}
	}
}


