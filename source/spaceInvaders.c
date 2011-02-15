/**
 * iutLife O.6
 * \file spaceInvaders.c
 * \author morgotth
 * \date 2009
 **/
#include "tirdeplacement.h"
#include "gfx/all_gfx.c" 
#include "lotus.h" // inclusion de la musique de fond
#include "phoenixIngame.h"
#include "collision.h"
#include "sprites.h"

// spaceInvaders0.03

/*
initialisationTableauTypeSpriteGlobal :

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
15 : Boss
*/

void spaceInvaders()
{
	PA_Init();
    PA_InitVBL();

    PA_InitText(1,0);
	PA_InitText(0,0);
	
	PA_InitSound();
    
	PA_WaitForVBL();PA_WaitForVBL();PA_WaitForVBL();
	
	PA_SetScreenSpace(8); // ESPACE ENTRE LES 2 écrans = 8 pixels !!
	
	// des compteurs utilisables dans des boucles
	int i,cpt;
	
	// les constantes pas globales
	int nbEnnemisMax=50;
	
	PA_EasyBgLoad(0,1,espace);//declaration et initialisation du background
	PA_EasyBgLoad(1,1,espace);
	// PA_DualLoadPAGfxLargeBg(1,backg); //pour les deux écrans
	
	/*          INITIALISATION DES PALETTES      */
	PA_LoadSpritePal(1,0,(void*)sprites_Pal);//           ////        pour ecran haut
	PA_LoadSpritePal(0,0,(void*)sprites_Pal);//           ////        pour ecran bas
	PA_LoadSpritePal(1,1,(void*)ennemis_Pal);//           ////        pour ecran haut
	PA_LoadSpritePal(0,1,(void*)ennemis_Pal);//           ////        pour ecran bas
	PA_LoadSpritePal(1,2,(void*)tir_Pal);//           ////        pour ecran haut
	PA_LoadSpritePal(0,2,(void*)tir_Pal);//           ////        pour ecran bas

	PA_DualLoadSpritePal(0,(void*)sprites_Pal);
	PA_DualLoadSpritePal(1,(void*)ennemis_Pal);
	PA_DualLoadSpritePal(2,(void*)tir_Pal);
	
	/* 		 INITIALISATION TYPE-SPRITE  ET  tabParcours   	*/
	TypeSprite tabTS[19];
	initialisationTableauTypeSpriteGlobal(tabTS);
	
	int /*nbEtapes1=6, nbEtapes2= 6, nbEtapes3=6,*/ nbEtapes1Charles=4, nbEtapes2Charles=4, nbEtapes3Charles=6, nbEtapes4Charles=5, /*nbEtapes5Charles=4, nbEtapes6Charles=4, nbEtapes7Charles=5, nbEtapes8Charles=5,*/ nbEtapes9Charles=4, nbEtapes10Charles=4, vitesse1=1, vitesse2=1, vitesse3=1,
		//tabParcours1[10][4]={{0,0,5,0},{200,0,vitesse1,0},{200,100,vitesse1,0},{50,100,vitesse1,0},{50,20,vitesse1,0},{150,20,vitesse1,0},{30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // tab[i][1] == x , tab[i][2] == y , tab[i][3] == vitesse, tab[0][3] = nbPV , tab[i][4] = temps entre i et i+1
		//tabParcours2[10][4]={{0,0,5,0},{200,0,vitesse2,0},{200,100,vitesse2,0},{50,100,vitesse2,0},{50,20,vitesse2,0},{150,20,vitesse2,0},{30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
		//tabParcours3[10][4]={{0,0,5,0},{200,0,vitesse3,0},{200,100,vitesse3,0},{50,100,vitesse3,0},{50,20,vitesse3,0},{150,20,vitesse3,0},{30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
 tabParcours1Charles[10][4]={{0,0,5,0},{210,10,vitesse1,0},{210,100,vitesse1,0},{5,100,vitesse1,0},{-30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
 tabParcours2Charles[10][4]={{0,0,5,0},{256,90,vitesse1,0},{15,30,vitesse1,0},{232,30,vitesse1,0},{30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
 tabParcours3Charles[10][4]={{256,128,5,0},{32,128,vitesse1,0},{245,96,vitesse1,0},{130,64,vitesse1,0},{245,32,vitesse1,0},{3,10,vitesse1,0},{-30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
 tabParcours4Charles[10][4]={{3,32,5,0},{190,32,vitesse1,0},{32,64,vitesse1,0},{190,96,vitesse1,0},{3,126,vitesse1,0},{-30,5,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
 // tabParcours5Charles[10][4]={{117,0,5,0},{117,325,vitesse1,0},{58,245,vitesse1,0},{10,325,vitesse1,0},{-30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
// Depart Ligne rouge (117.0) haut de l'écran 1 au centre et fini sa course écran 0 a gauche en son centre (10.325)
 // tabParcours6Charles[10][4]={{256,325,5,0},{140,325,vitesse1,0},{140,110,vitesse1,0},{205,110,vitesse1,0},{30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
// Depart Ligne rouge (256.325) de l'Ecran 0 du centre droit et fini sa course ecran 1 au millieu droit (205.110)
 //tabParcours7Charles[10][4]={{0,258,5,0},{50,180,vitesse1,0},{100,180,vitesse1,0},{100,32,vitesse1,0},{0,32,vitesse1,0},{-30,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
// Depart Ligne bleu (0.258) de l'Ecran 0 du centre gauche et fini sa course ecran 1 en haut a gauche (0.32)
 //tabParcours8Charles[10][4]={{256,32,5,0},{160,32,vitesse1,0},{160,180,vitesse1,0},{205,180,vitesse1,0},{252,258,vitesse1,0},{30,20,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
// Depart Ligne bleu  (256.32) de l'Ecran 1 en haut a droite et fini sa course en haut a droite de l Ecran 0 (252.258)
 tabParcours9Charles[10][4]={{0,0,5,0},{90,167,vitesse1,0},{220,26,vitesse1,0},{70,167,vitesse1,0},{-30,30,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
// refait pour faire une étoile branche haut droite
 tabParcours10Charles[10][4]={{256,0,5,0},{152,167,vitesse1,0},{30,26,vitesse1,0},{174,167,vitesse1,0},{30,30,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
// refait pour faire une étoile branche haut gauche

	PA_CreateSprite(0,1,(void*)miniTir_Sprite,OBJ_SIZE_32X16,1,0,255,193);
	PA_SetSpriteXY(0,1,255,193);// un sprite inutile mais qui se prends un bug d'affichage ...
								// le bug apparait qu'avec le boss et doit venir d'un des trucs touchants aux tirs. Mais impossible à trouver :(
	
	/*                 SPRITE JOUEUR            */
	// initialisation du Joueur
	// la position du vaisseau au départ = {x=50} et {y=160}
	// numEcran = 0 et numSprite = 1
	Sprite Joueur;
	Joueur.numEcran = 0;
	Joueur.numSprite = 2;
	Joueur.x=50;
	Joueur.y=160;
	Joueur.nbPV=30;
	Joueur.numEtape=0;
	Joueur.temps=0;
	Joueur.typeSprite=&tabTS[11];
	
	// pas de palette pour les sprites 16bits
	// PA_Create16bitSprite(Joueur.numEcran, 	// Screen
						// Joueur.numSprite,	// Sprite number
						// (void*)ship_Sprite, // image to load, 128 pixels wide !
						// OBJ_SIZE_32X32, 	// sprite size
						// Joueur.x,   		// x
						// Joueur.y); 			//y
	PA_CreateSprite(Joueur.numEcran,Joueur.numSprite,(void*)ship_Sprite,OBJ_SIZE_32X32,1,0,Joueur.x,Joueur.y);
	PA_SetSpriteXY(Joueur.numEcran,Joueur.numSprite,(Joueur.x+=50),Joueur.y);
	// ancien : PA_CreateSprite(Joueur.numEcran,Joueur.numSprite,(void*)yata_Sprite,OBJ_SIZE_32X64,1,0,Joueur.x,Joueur.y);
	
	/*                 ENNEMIS                 */
	int nbEnnemi0=18, nbEnnemi=18, spriteReference=1; // maximum d'ennemis pour écran 0
	Sprite tabEnnemi0[nbEnnemisMax], tabEnnemi[nbEnnemisMax]; // tableau d'ennemi, nbEnnemisMax est une constante donner au début du programme
	cpt=0;
	PA_WaitForVBL();PA_WaitForVBL();
	//*
	// 45-50 : Crab
	int nbSpriteDbt=45;
	for(i=0;i<6;i++)
	{
		tabEnnemi0[i].numEcran=0;
		tabEnnemi0[i].numSprite=(i+nbSpriteDbt);
		tabEnnemi0[i].x=256;
		tabEnnemi0[i].y=192;
		tabEnnemi0[i].nbPV=0;
		tabEnnemi0[i].numEtape=0;
		tabEnnemi0[i].temps=0;
		tabEnnemi0[i].typeSprite=&tabTS[0];
		if(i==0)
		{
			PA_CreateSprite(tabEnnemi0[i].numEcran,nbSpriteDbt,(void*)Crab_Sprite,OBJ_SIZE_32X32,1,1,tabEnnemi0[i].x,tabEnnemi0[i].y);
			spriteReference=tabEnnemi0[i].numSprite;
		}
		else
			PA_CloneSprite(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,spriteReference);
		PA_SetSpriteXY(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,tabEnnemi0[i].x,tabEnnemi0[i].y);
		PA_StartSpriteAnim(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,0,1,1);
	}
	
	// 51-56 : Octopus
	for(i=6;i<12;i++)
	{
		tabEnnemi0[i].numEcran=0;
		tabEnnemi0[i].numSprite=(i+nbSpriteDbt);
		tabEnnemi0[i].x=256;
		tabEnnemi0[i].y=192;
		tabEnnemi0[i].nbPV=0;
		tabEnnemi0[i].numEtape=0;
		tabEnnemi0[i].temps=0;
		tabEnnemi0[i].typeSprite=&tabTS[2];
		if(i==6)
		{
			PA_CreateSprite(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,(void*)Octopus_Sprite,OBJ_SIZE_16X16,1,1,tabEnnemi0[i].x,tabEnnemi0[i].y);
			spriteReference=tabEnnemi0[i].numSprite;
		}
		else
			PA_CloneSprite(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,spriteReference);
		PA_SetSpriteXY(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,tabEnnemi0[i].x,tabEnnemi0[i].y);
		PA_StartSpriteAnim(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,0,1,1);
	}
	

	// 57-62 : Squid
	for(i=12;i<nbEnnemi0;i++)
	{
		tabEnnemi0[i].numEcran=0;
		tabEnnemi0[i].numSprite=(i+nbSpriteDbt);
		tabEnnemi0[i].x=256;
		tabEnnemi0[i].y=192;
		tabEnnemi0[i].nbPV=0;
		tabEnnemi0[i].numEtape=0;
		tabEnnemi0[i].temps=0;
		tabEnnemi0[i].typeSprite=&tabTS[4];
		if(i==12)
		{
			PA_CreateSprite(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,(void*)Squid_Sprite,OBJ_SIZE_32X32,1,1,tabEnnemi0[i].x,tabEnnemi0[i].y);
			spriteReference=tabEnnemi0[i].numSprite;
		}
		else
			PA_CloneSprite(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,spriteReference);
		PA_SetSpriteXY(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,tabEnnemi0[i].x,tabEnnemi0[i].y);
		PA_StartSpriteAnim(tabEnnemi0[i].numEcran,tabEnnemi0[i].numSprite,0,1,1);
	}
	//*/
	// ecran -1
	// 63-68 : Crab
	int nbSpriteDbt2=63;
	i=0;
	for(i=0;i<6;i++)
	{
		tabEnnemi[i].numEcran=-1;
		tabEnnemi[i].numSprite=(i+nbSpriteDbt2);
		tabEnnemi[i].x=256;
		tabEnnemi[i].y=392;
		tabEnnemi[i].nbPV=0;
		tabEnnemi[i].numEtape=0;
		tabEnnemi[i].temps=0;
		tabEnnemi[i].typeSprite=&tabTS[0];
		if(i==0)
		{
			PA_DualCreateSprite(nbSpriteDbt2,(void*)Crab_Sprite,OBJ_SIZE_32X32,1,1,tabEnnemi[i].x,tabEnnemi[i].y);
			spriteReference=tabEnnemi[i].numSprite;
		}
		else
			PA_DualCloneSprite(tabEnnemi[i].numSprite,nbSpriteDbt2);
		PA_DualSetSpriteXY(tabEnnemi[i].numSprite,tabEnnemi[i].x,tabEnnemi[i].y);
		PA_DualStartSpriteAnim(tabEnnemi[i].numSprite,0,1,1);
	}
	
	// 69-74 : Octopus
	for(i=6;i<12;i++)
	{
		tabEnnemi[i].numEcran=-1;
		tabEnnemi[i].numSprite=(i+nbSpriteDbt2);
		tabEnnemi[i].x=256;
		tabEnnemi[i].y=392;
		tabEnnemi[i].nbPV=0;
		tabEnnemi[i].numEtape=0;
		tabEnnemi[i].temps=0;
		tabEnnemi[i].typeSprite=&tabTS[2];
		if(i==6)
		{
			PA_DualCreateSprite(tabEnnemi[i].numSprite,(void*)Octopus_Sprite,OBJ_SIZE_16X16,1,1,tabEnnemi[i].x,tabEnnemi[i].y);
			spriteReference=tabEnnemi[i].numSprite;
		}
		else
			PA_DualCloneSprite(tabEnnemi[i].numSprite,spriteReference);
		PA_DualSetSpriteXY(tabEnnemi[i].numSprite,tabEnnemi[i].x,tabEnnemi[i].y);
		PA_DualStartSpriteAnim(tabEnnemi[i].numSprite,0,1,1);
	}
	
	// 75-80 : Squid
	for(i=12;i<nbEnnemi;i++)
	{
		tabEnnemi[i].numEcran=-1;
		tabEnnemi[i].numSprite=(i+nbSpriteDbt2);
		tabEnnemi[i].x=256;
		tabEnnemi[i].y=392;
		tabEnnemi[i].nbPV=0;
		tabEnnemi[i].numEtape=0;
		tabEnnemi[i].temps=0;
		tabEnnemi[i].typeSprite=&tabTS[4];
		if(i==12)
		{
			PA_DualCreateSprite(tabEnnemi[i].numSprite,(void*)Squid_Sprite,OBJ_SIZE_32X32,1,1,tabEnnemi[i].x,tabEnnemi[i].y);
			spriteReference=tabEnnemi[i].numSprite;
		}
		else
			PA_DualCloneSprite(tabEnnemi[i].numSprite,spriteReference);
		PA_DualSetSpriteXY(tabEnnemi[i].numSprite,tabEnnemi[i].x,tabEnnemi[i].y);
		PA_DualStartSpriteAnim(tabEnnemi[i].numSprite,0,1,1);
	}
	
	
	//PA_CreateSprite(0,102,(void*)Squid_Sprite,OBJ_SIZE_32X32,1,0,110,100);
	//PA_StartSpriteAnim(0,100,0,1,1);
	//PA_StartSpriteAnim(0,101,0,1,1);
	//PA_StartSpriteAnim(0,102,0,1,1);
	//*
	// boss test
	Boss boss;
	
	boss.nombredeSprite=4;
	
	boss.sprite1.numEcran=-1;
	boss.sprite1.numSprite=124;
	boss.sprite1.x=-124;
	boss.sprite1.y=0;
	boss.sprite1.typeSprite=&tabTS[15];
	
	boss.sprite2.numEcran=-1;
	boss.sprite2.numSprite=125;
	boss.sprite2.x=-64;
	boss.sprite2.y=0;
	boss.sprite2.typeSprite=&tabTS[16];
	
	boss.sprite3.numEcran=-1;
	boss.sprite3.numSprite=126;
	boss.sprite3.x=-124;
	boss.sprite3.y=32;
	boss.sprite3.typeSprite=&tabTS[17];
	
	boss.sprite4.numEcran=-1;
	boss.sprite4.numSprite=127;
	boss.sprite4.x=-64;
	boss.sprite4.y=32;
	boss.sprite4.typeSprite=&tabTS[18];
	
	boss.typeTir=0;
	boss.typeTir2=2;
	
	//origine des tirs
	boss.origineTir1[0]=64;
	boss.origineTir1[1]=64;
	
	boss.origineTir2[0]=8;
	boss.origineTir2[1]=32;
	
	boss.origineTir3[0]=115;
	boss.origineTir3[1]=32;
	
	PA_DualCreateSprite(boss.sprite1.numSprite,(void*)Boss_Sprite,OBJ_SIZE_64X32,1,1,boss.sprite1.x,boss.sprite1.y);
	PA_DualCreateSprite(boss.sprite2.numSprite,(void*)Boss2_Sprite,OBJ_SIZE_64X32,1,1,boss.sprite2.x,boss.sprite2.y);
	PA_DualCreateSprite(boss.sprite3.numSprite,(void*)Boss3_Sprite,OBJ_SIZE_64X32,1,1,boss.sprite3.x,boss.sprite3.y);
	PA_DualCreateSprite(boss.sprite4.numSprite,(void*)Boss4_Sprite,OBJ_SIZE_64X32,1,1,boss.sprite4.x,boss.sprite4.y);
	
	PA_DualSetSpriteXY(boss.sprite1.numSprite,boss.sprite1.x,boss.sprite1.y);
	PA_DualSetSpriteXY(boss.sprite2.numSprite,boss.sprite2.x,boss.sprite2.y);
	PA_DualSetSpriteXY(boss.sprite3.numSprite,boss.sprite3.x,boss.sprite3.y);
	PA_DualSetSpriteXY(boss.sprite4.numSprite,boss.sprite4.x,boss.sprite4.y);
	//*/
	
	/*                 TIR                     */
	// initialisation du tableau de tir et le premier tir sera impair
	int numDebutTir=5, numDebutTirBoss=81, numTir=25, numTirMax=60;
	Tir tabTir[numTirMax];
	// les tirs sont envoyés hors de l'écran. Les numéros 10 à 30 sont réservés aux Tirs. Le Tir est initialement non actif
	// les indices sont de numTir (ATTENTION : numSPrite = numTir+10)
	// typeTir : 0=miniTir, 1=salveTir, 2=tir
	// de 0 à 10 = miniTir
	for(i=0;i<10;i++)
	{
		tabTir[i].coordonnees.numEcran=-1;
		tabTir[i].coordonnees.numSprite=(numDebutTir+i);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=392;
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=2;
		tabTir[i].puissanceTir=2;
		tabTir[i].typeTir=0;
		tabTir[i].coordonnees.typeSprite=&tabTS[6];
		if(i==0)
		{
			PA_DualCreateSprite(tabTir[i].coordonnees.numSprite,(void*)miniTir_Sprite,OBJ_SIZE_8X8,1,2,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
			spriteReference=tabTir[i].coordonnees.numSprite;
		}
		else
			PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
		PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
		// pour l'instant, vitesse et puissance = 2
	}
	
	// de 10 à 15 = tir
	for(i=10;i<15;i++)
	{
		tabTir[i].coordonnees.numEcran=-1;
		tabTir[i].coordonnees.numSprite=(numDebutTir+i);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=392;
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=1;
		tabTir[i].puissanceTir=10;
		tabTir[i].typeTir=2;
		tabTir[i].coordonnees.typeSprite=&tabTS[8];
		
		if(i==10)
		{
			PA_DualCreateSprite(tabTir[i].coordonnees.numSprite,(void*)tir_Sprite,OBJ_SIZE_16X16,1,2,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
			spriteReference=tabTir[i].coordonnees.numSprite;
		}
		else
			PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
		PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
		// pour l'instant, vitesse et puissance = 2
	}
	
	// de 15 à 25 = salveTir
	for(i=15;i<numTir;i++)
	{
		tabTir[i].coordonnees.numEcran=-1;
		tabTir[i].coordonnees.numSprite=(numDebutTir+i);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=392;//192*2=384+8=392 le 8 est l'espace entre les 2 écrans
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=2;
		tabTir[i].puissanceTir=6;
		tabTir[i].typeTir=1;
		tabTir[i].coordonnees.typeSprite=&tabTS[7];
		
		//DOUBLESPRITE
		if(i==15)
		{
			PA_DualCreateSprite(tabTir[i].coordonnees.numSprite,(void*)salveTir_Sprite,OBJ_SIZE_16X16,1,2,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
			spriteReference=tabTir[i].coordonnees.numSprite;
		}
		else
			PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
		PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
		// pour l'instant, vitesse et puissance = 2
	}
	
	// LES TIRS DES BOSS
	// les structures sont initialisés mais les sprites pas encore créé
	// ils vont de numSprite=81 à 109 et ils seront créés lorsque les sprites ennemis seront detruits pour faire de la place
	for(i=30;i<40;i++)
	{
		tabTir[i].coordonnees.numEcran=-1;
		tabTir[i].coordonnees.numSprite=(numDebutTirBoss+i-30);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=392;
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=2;
		tabTir[i].puissanceTir=2;
		tabTir[i].typeTir=0;
		tabTir[i].coordonnees.typeSprite=&tabTS[6];
	}
	
	// de 10 à 20 = tir
	for(i=40;i<50;i++)
	{
		tabTir[i].coordonnees.numEcran=-1;
		tabTir[i].coordonnees.numSprite=(numDebutTirBoss+i-30);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=392;
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=1;
		tabTir[i].puissanceTir=10;
		tabTir[i].typeTir=2;
		tabTir[i].coordonnees.typeSprite=&tabTS[8];
	}
	
	// de 20 à 25 = salveTir
	for(i=50;i<numTirMax;i++)
	{
		tabTir[i].coordonnees.numEcran=-1;
		tabTir[i].coordonnees.numSprite=(numDebutTirBoss+i-30);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=392;//192*2=384+8=392 le 8 est l'espace entre les 2 écrans
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=2;
		tabTir[i].puissanceTir=6;
		tabTir[i].typeTir=1;
		tabTir[i].coordonnees.typeSprite=&tabTS[7];
	}
	
	
	// END SPRITE
	
	PA_WaitForVBL();PA_WaitForVBL();PA_WaitForVBL();	
	
	int numMusique=1, numMusiqueMax=2;
	char tabMusique[4][20]={"Pas de Musique","phoenixIngame","lotus","rien"};
	// PA_PlayMod(lotus); // lecture d'un fichier Mod
	// PA_PauseMod(u8); u8 = 0 pour enlever ou 1 pour mettre en pause NE MARCHE PAS, faut une release communautaire ...
	// PA_StopMod()
	PA_PlayMod(phoenixIngame);
	
	// la condition pour que le jeu continue
	bool sortir=false;
	
	PA_WaitForVBL();PA_WaitForVBL();PA_WaitForVBL();PA_WaitForVBL();
	
	// les variables et instructions necessaire pour gerer le temps sur la DS
	PA_VBLCounterStart(0); // le début du jeu
	PA_VBLCounterStart(1); // pour les étapes
	PA_VBLCounterStart(2);
	PA_VBLCounterStart(3);
	//PA_VBLCounterStart(10); // pour le cheat
	PA_VBLCounterStart(15); // pour les tirs aléatoires des ennemis
	PA_VBLCounterStart(16); // pour les tirs du Joueur
	
	//unsigned int debutDuJeu=getTicks(); // le début du jeu, au cas ou ...
	int cptTirActif=1, cptTirActifEnnemi=1;
	// cptTirActif est le nombre (premier, second ...) du prochain tir
	int niveauTir=0, actionTir=1, numEtape=1, numEtapeBoss1=16, numEtapeMax=17;
	int debutParcours=1,debutParcours2=1,debutParcours3=1, debutParcours4=1,propreteAffichageTir=0; // = 1 si debut, 0 si jeu en cours, 2 si fini
	int vitesseBoss=1;
	// actionTir est à 1 si le tir doit être activé, 0 sinon
	//int cheatCode=0, tpsDernierEssaiCheatCode=PA_VBLCounter[10]/15;
	//unsigned int TempsDernierChoix=getTicks();//seconde courante
	
	while(!sortir)
    {
		// sécurité pour les tirs ennemis
		if(cptTirActifEnnemi>=50)
		{
			cptTirActifEnnemi=0;
			PA_VBLCounterStart(15);
		}

		/*
		if(Pad.Newpress.A && (cheatCode==1 || cheatCode==2) && tpsDernierEssaiCheatCode!=(PA_VBLCounter[10]/15))
		{
			if(cheatCode==1 && PA_VBLCounter[10]/60!=0)
			{
				PA_VBLCounterStart(10);
			}
			cheatCode++;
			tpsDernierEssaiCheatCode=PA_VBLCounter[10]/15;
		}
		if(Pad.Newpress.B && (cheatCode==0 || cheatCode==3) && tpsDernierEssaiCheatCode!=(PA_VBLCounter[10]/15))
		{
			cheatCode++;
			tpsDernierEssaiCheatCode=PA_VBLCounter[10]/15;
		}
		if(cheatCode==4)
		{
			Joueur.nbPV+=50;
			cheatCode=0;
		}
		if(cheatCode!=0 && PA_VBLCounter[10]/60==3)
		{
			cheatCode=0;
		}
		//*/
		// numEtape nous sert à savoir à quel étape du jeu on se situe
		// cptTemps nous sert pour savoir ou en est le jeu et pour les déplacements
		
		/* 		PREMIERE ETAPE		*/
		if(numEtape==1 || numEtape==2 || numEtape==3) // Crab
		{	// première étape du jeu
			if(debutParcours==1)
			{
				debutParcours=0;
				PA_VBLCounterStart(1); // reinitialisation du compteur
				PA_VBLCounterStart(15); // pour les tirs
				tabEnnemi[0].x=tabParcours1Charles[0][0];
				tabEnnemi[0].y=tabParcours1Charles[0][1];
				tabEnnemi[0].nbPV=5;
				tabEnnemi[0].numEtape=1;
				PA_DualSetSpriteXY(tabEnnemi[0].numSprite,tabEnnemi[0].x,tabEnnemi[0].y);
				//PA_SetSpriteXY(tabEnnemi[0].numEcran,tabEnnemi0[0].numSprite,tabEnnemi0[0].x,tabEnnemi0[0].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 0, 5, tabParcours1Charles, nbEtapes1Charles, 1) && debutParcours!=2)
			{
				numEtape++;
				debutParcours=2;
			}
		}
		
		if(numEtape==1 || numEtape==2 || numEtape==3) // Octopus
		{	// première étape du jeu
			if(debutParcours2==1)
			{
				debutParcours2=0;
				PA_VBLCounterStart(2); // reinitialisation du compteur
				tabEnnemi[6].x=tabParcours2Charles[0][0];
				tabEnnemi[6].y=tabParcours2Charles[0][1];
				tabEnnemi[6].nbPV=5;
				tabEnnemi[6].numEtape=1;
				PA_DualSetSpriteXY(tabEnnemi[6].numSprite,tabEnnemi[6].x,tabEnnemi[6].y);
				//PA_SetSpriteXY(tabEnnemi0[8].numEcran,tabEnnemi0[8].numSprite,tabEnnemi0[8].x,tabEnnemi0[8].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 6, 5, tabParcours2Charles, nbEtapes2Charles, 2) && debutParcours2!=2)
			{
				numEtape++;
				debutParcours2=2;
			}
		}
		
		if(numEtape==1 || numEtape==2 || numEtape==3) // Squid
		{	// première étape du jeu
			if(debutParcours3==1)
			{
				debutParcours3=0;
				PA_VBLCounterStart(3); // reinitialisation du compteur
				tabEnnemi[12].x=tabParcours3Charles[0][0];
				tabEnnemi[12].y=tabParcours3Charles[0][1];
				tabEnnemi[12].nbPV=5;
				tabEnnemi[12].numEtape=1;
				PA_DualSetSpriteXY(tabEnnemi[12].numSprite,tabEnnemi[12].x,tabEnnemi[12].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 12, 5, tabParcours3Charles, nbEtapes3Charles, 3) && debutParcours3!=2)
			{
				numEtape++;
				debutParcours3=2;
			}
		}
		
		if(actionTir && (numEtape==1 || numEtape==2 || numEtape==3) && cptTirActifEnnemi==(PA_VBLCounter[15]/60))
		{	// première étape du jeu
			int spritealeatoire = PA_RandMinMax(0,5),
				spritealeatoire2 = PA_RandMinMax(6,11),
				spritealeatoire3 = PA_RandMinMax(12,17);
			int ylanceur=tabEnnemi[spritealeatoire].y+15,
				ylanceur2=tabEnnemi[spritealeatoire2].y+15,
				ylanceur3=tabEnnemi[spritealeatoire3].y+15;
			if(tabEnnemi[spritealeatoire].numEcran==0)
			{	ylanceur+=200;	}
			if(tabEnnemi[spritealeatoire].numEcran==0)
			{	ylanceur2+=200;	}
			
			nouveauTir(tabTir,10,2,tabEnnemi[spritealeatoire].x+5,ylanceur);
			nouveauTir(&tabTir[15],10,2,tabEnnemi[spritealeatoire2].x+5,ylanceur2);
			nouveauTir(tabTir,10,2,tabEnnemi[spritealeatoire3].x+5,ylanceur3);
			cptTirActifEnnemi++;
		}
		
		/* 		DEUXIEME ETAPE		*/
		if(numEtape==4) // initialisation de l'étape 5 et 6
		{
			if(debutParcours==2 && debutParcours2==2 && debutParcours3==2) // si les 3 etapes sont finis
			{
				PA_VBLCounterStart(1); // reinitialisation du compteur d'étapes
				debutParcours=0;
				debutParcours2=0;
				debutParcours3=0;
				PA_OutputText(0,0,10,"NIVEAU 1 TERMINE !!!");
				actionTir=false;
			}
			if((PA_VBLCounter[1]/60)==3)
			{
				PA_ClearTextBg(0);
				numEtape++;
				PA_VBLCounterStart(1);
				debutParcours=1;
				debutParcours2=1;
				PA_VBLCounterStart(1);
				PA_VBLCounterStart(15);
				PA_VBLCounterStart(16);
				cptTirActif=0;
				cptTirActifEnnemi=0;
				actionTir=true;
			}
		}
		
		if(numEtape==5 || numEtape==6) // Crab
		{	// deuxième étape du jeu
			if(debutParcours==1)
			{
				debutParcours=0;
				PA_VBLCounterStart(1); // reinitialisation du compteur
				tabEnnemi0[0].x=tabParcours9Charles[0][0];
				tabEnnemi0[0].y=tabParcours9Charles[0][1];
				tabEnnemi0[0].nbPV=5;
				tabEnnemi0[0].numEtape=1;
				PA_SetSpriteXY(tabEnnemi0[0].numEcran,tabEnnemi0[0].numSprite,tabEnnemi0[0].x,tabEnnemi0[0].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi0, 0, 6, tabParcours2Charles, nbEtapes2Charles, 1) && debutParcours!=2)
			{
				numEtape++;
				debutParcours=2;
			}
		}
		
		if(numEtape==5 || numEtape==6) // Octopus
		{	// deuxième étape du jeu
			if(debutParcours2==1)
			{
				debutParcours2=0;
				PA_VBLCounterStart(2); // reinitialisation du compteur
				tabEnnemi0[6].x=tabParcours10Charles[0][0];
				tabEnnemi0[6].y=tabParcours10Charles[0][1];
				tabEnnemi0[6].nbPV=5;
				tabEnnemi0[6].numEtape=1;
				PA_SetSpriteXY(tabEnnemi0[6].numEcran,tabEnnemi0[6].numSprite,tabEnnemi0[6].x,tabEnnemi0[6].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi0, 6, 6, tabParcours3Charles, nbEtapes3Charles, 2) && debutParcours2!=2)
			{
				numEtape++;
				debutParcours2=2;
			}
		}
		
		if(actionTir && (numEtape==5 || numEtape==6) && cptTirActifEnnemi==(PA_VBLCounter[15]/60))
		{	// deuxième étape du jeu
			int spritealeatoire = PA_RandMinMax(0,6),
				spritealeatoire2 = PA_RandMinMax(6,12);
			int ylanceur=tabEnnemi0[spritealeatoire].y+15,
				ylanceur2=tabEnnemi0[spritealeatoire2].y+15;
			if(tabEnnemi0[spritealeatoire].numEcran==0)
			{	ylanceur+=200;	}
			if(tabEnnemi0[spritealeatoire].numEcran==0)
			{	ylanceur2+=200;	}
			
			nouveauTir(tabTir,10,2,tabEnnemi0[spritealeatoire].x+5,ylanceur);
			nouveauTir(&tabTir[15],10,2,tabEnnemi0[spritealeatoire2].x+5,ylanceur2);
			cptTirActifEnnemi++;
		}
		
		if(numEtape==7)
		{
			if(debutParcours==2 && debutParcours2==2) // bricolage
			{
				PA_VBLCounterStart(1); // reinitialisation du compteur d'étapes
				debutParcours=0;
				PA_OutputText(0,0,10,"NIVEAU 2 TERMINE !!!");
				PA_StopMod();
			}
			if((PA_VBLCounter[1]/60)==3)
			{
				numMusique=2;
				PA_PlayMod(lotus);
				PA_ClearTextBg(0);
				numEtape++;
				PA_VBLCounterStart(1);
				debutParcours=1;
				debutParcours2=1;
				debutParcours3=1;
				debutParcours4=1;
				PA_VBLCounterStart(1);
				PA_VBLCounterStart(15);
				PA_VBLCounterStart(16);
				cptTirActif=0;
				cptTirActifEnnemi=0;
				actionTir=true;
			}
		}

		if(numEtape==8 || numEtape==9 || numEtape==10 || numEtape==11) // sprites en 0
		{	// troisième étape du jeu
			if(debutParcours==1)
			{
				debutParcours=0;
				PA_VBLCounterStart(1); // reinitialisation du compteur
				tabEnnemi0[0].x=tabParcours1Charles[0][0];
				tabEnnemi0[0].y=tabParcours1Charles[0][1];
				tabEnnemi0[0].nbPV=5;
				tabEnnemi0[0].numEtape=1;
				PA_SetSpriteXY(tabEnnemi0[0].numEcran,tabEnnemi0[0].numSprite,tabEnnemi0[0].x,tabEnnemi0[0].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi0, 0, 5, tabParcours1Charles, nbEtapes1Charles, 1) && debutParcours!=2)
			{
				numEtape++;
				debutParcours=2;
			}
		}
		
		if(numEtape==8 || numEtape==9 || numEtape==10 || numEtape==11)  // sprites en -1
		{	// troisième étape du jeu
			if(debutParcours2==1)
			{
				debutParcours2=0;
				PA_VBLCounterStart(2); // reinitialisation du compteur
				tabEnnemi[6].x=tabParcours3Charles[0][0];
				tabEnnemi[6].y=tabParcours3Charles[0][1];
				tabEnnemi[6].nbPV=5;
				tabEnnemi[6].numEtape=1;
				PA_SetSpriteXY(tabEnnemi[6].numEcran,tabEnnemi[6].numSprite,tabEnnemi[6].x,tabEnnemi[6].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 6, 5, tabParcours3Charles, nbEtapes3Charles, 2) && debutParcours2!=2)
			{
				numEtape++;
				debutParcours2=2;
			}
		}
		
		if(numEtape==8 || numEtape==9 || numEtape==10 || numEtape==11) // sprites en 0
		{	// troisième étape du jeu
			if(debutParcours3==1)
			{
				debutParcours3=0;
				PA_VBLCounterStart(1); // reinitialisation du compteur
				tabEnnemi0[6].x=tabParcours2Charles[0][0];
				tabEnnemi0[6].y=tabParcours2Charles[0][1];
				tabEnnemi0[6].nbPV=5;
				tabEnnemi0[6].numEtape=1;
				PA_SetSpriteXY(tabEnnemi0[6].numEcran,tabEnnemi0[6].numSprite,tabEnnemi0[6].x,tabEnnemi0[6].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi0, 6, 5, tabParcours2Charles, nbEtapes2Charles, 1) && debutParcours3!=2)
			{
				numEtape++;
				debutParcours3=2;
			}
		}
		
		if(numEtape==8 || numEtape==9 || numEtape==10 || numEtape==11)  // sprites en -1
		{	// troisième étape du jeu
			if(debutParcours4==1)
			{
				debutParcours4=0;
				PA_VBLCounterStart(2); // reinitialisation du compteur
				tabEnnemi[12].x=tabParcours4Charles[0][0];
				tabEnnemi[12].y=tabParcours4Charles[0][1];
				tabEnnemi[12].nbPV=5;
				tabEnnemi[12].numEtape=1;
				PA_SetSpriteXY(tabEnnemi[12].numEcran,tabEnnemi[12].numSprite,tabEnnemi[12].x,tabEnnemi[12].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 12, 5, tabParcours4Charles, nbEtapes4Charles, 2) && debutParcours4!=2)
			{
				numEtape++;
				debutParcours4=2;
			}
		}
		
		if(actionTir && (numEtape==8 || numEtape==9 || numEtape==10 || numEtape==11) && cptTirActifEnnemi==(PA_VBLCounter[15]/60))
		{	// troisième étape du jeu
			int spritealeatoire = PA_RandMinMax(0,5),
				spritealeatoire2 = PA_RandMinMax(6,11),
				spritealeatoire3 = PA_RandMinMax(6,11),
				spritealeatoire4 = PA_RandMinMax(12,17);
			int ylanceur=tabEnnemi0[spritealeatoire].y+15,
				ylanceur2=tabEnnemi[spritealeatoire2].y+15,
				ylanceur3=tabEnnemi0[spritealeatoire3].y+15,
				ylanceur4=tabEnnemi[spritealeatoire4].y+15;
			if(tabEnnemi0[spritealeatoire].numEcran==0)
			{	ylanceur+=200;	}
			if(tabEnnemi[spritealeatoire2].numEcran==0)
			{	ylanceur2+=200;	}
			if(tabEnnemi0[spritealeatoire3].numEcran==0)
			{	ylanceur3+=200;	}
			if(tabEnnemi[spritealeatoire4].numEcran==0)
			{	ylanceur4+=200;	}
			
			nouveauTir(tabTir,10,2,tabEnnemi0[spritealeatoire].x+5,ylanceur);
			nouveauTir(tabTir,10,2,tabEnnemi[spritealeatoire2].x+5,ylanceur2);
			nouveauTir(&tabTir[15],10,2,tabEnnemi0[spritealeatoire3].x+5,ylanceur3);
			nouveauTir(&tabTir[15],10,2,tabEnnemi[spritealeatoire4].x+5,ylanceur4);
			cptTirActifEnnemi++;
		}
		
		if(numEtape==12)
		{
			if(debutParcours==2 && debutParcours2==2 && debutParcours3==2 && debutParcours4==2) // bricolage
			{
				PA_VBLCounterStart(1); // reinitialisation du compteur d'étapes
				debutParcours=0;
				PA_OutputText(0,0,10,"NIVEAU 3 TERMINE !!!");
			}
			if((PA_VBLCounter[1]/60)==3)
			{
				PA_ClearTextBg(0);
				numEtape++;
				PA_VBLCounterStart(1);
				debutParcours=1;
				debutParcours2=1;
				PA_VBLCounterStart(1);
				PA_VBLCounterStart(15);
				PA_VBLCounterStart(16);
				cptTirActif=0;
				cptTirActifEnnemi=0;
				actionTir=true;
			}
		}

		if(numEtape==13 || numEtape==14) // Crab
		{	// quatrième étape du jeu
			if(debutParcours==1)
			{
				debutParcours=0;
				PA_VBLCounterStart(1); // reinitialisation du compteur
				tabEnnemi[0].x=tabParcours9Charles[0][0];
				tabEnnemi[0].y=tabParcours9Charles[0][1];
				tabEnnemi[0].nbPV=5;
				tabEnnemi[0].numEtape=1;
				PA_SetSpriteXY(tabEnnemi[0].numEcran,tabEnnemi[0].numSprite,tabEnnemi[0].x,tabEnnemi[0].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 0, 6, tabParcours9Charles, nbEtapes9Charles, 1) && debutParcours!=2)
			{
				numEtape++;
				debutParcours=2;
			}
		}
		
		if(numEtape==13 || numEtape==14) // Octopus
		{	// quatrième étape du jeu
			if(debutParcours2==1)
			{
				debutParcours2=0;
				PA_VBLCounterStart(2); // reinitialisation du compteur
				tabEnnemi[6].x=tabParcours10Charles[0][0];
				tabEnnemi[6].y=tabParcours10Charles[0][1];
				tabEnnemi[6].nbPV=5;
				tabEnnemi[6].numEtape=1;
				PA_SetSpriteXY(tabEnnemi[6].numEcran,tabEnnemi[6].numSprite,tabEnnemi[6].x,tabEnnemi[6].y);
			}
			
			// le premier script
			if(nouveauParcours(tabEnnemi, 6, 6, tabParcours10Charles, nbEtapes10Charles, 2) && debutParcours2!=2)
			{
				numEtape++;
				debutParcours2=2;
			}
		}
		
		if(actionTir && (numEtape==13 || numEtape==14) && cptTirActifEnnemi==(PA_VBLCounter[15]/60))
		{	// quatrième étape du jeu
			int spritealeatoire = PA_RandMinMax(0,6),
				spritealeatoire2 = PA_RandMinMax(6,12);
			int ylanceur=tabEnnemi[spritealeatoire].y+15,
				ylanceur2=tabEnnemi[spritealeatoire2].y+15;
			if(tabEnnemi[spritealeatoire].numEcran==0)
			{	ylanceur+=200;	}
			if(tabEnnemi[spritealeatoire].numEcran==0)
			{	ylanceur2+=200;	}
			
			nouveauTir(tabTir,10,2,tabEnnemi[spritealeatoire].x+5,ylanceur);
			nouveauTir(&tabTir[15],10,2,tabEnnemi[spritealeatoire2].x+5,ylanceur2);
			cptTirActifEnnemi++;
		}
		
		if(numEtape==numEtapeBoss1-1) // BOSS
		{	// cinquième étape du jeu
			if(debutParcours==2 && debutParcours2==2) // bricolage
			{
				PA_VBLCounterStart(1); // reinitialisation du compteur d'étapes
				debutParcours=0;

				PA_OutputText(0,0,10,"NIVEAU 4 TERMINE !!!");
			}
			
			if((PA_VBLCounter[1]/60)==3)
			{
				PA_ClearTextBg(0);
				numEtape++;
				debutParcours=1;
				debutParcours2=1;
				debutParcours3=1;
				debutParcours4=1;
				PA_VBLCounterStart(1);
				PA_VBLCounterStart(15);
				PA_VBLCounterStart(16);
				cptTirActif=0;
				cptTirActifEnnemi=0;
				actionTir=true;
				boss.sprite1.nbPV=90;
				boss.sprite2.nbPV=90;
				boss.sprite3.nbPV=90;
				boss.sprite4.nbPV=90;
				preparationBoss(tabTir);
				/*for(i=51;i<62;i++)// destruction de tout les ennemis du bas
				{
					PA_DeleteSprite(0,i);
				}
				for(i=63;i<80;i++)// destruction de tout les ennemis en haut
				{
					PA_DualDeleteSprite(i);
				}
				
				// 			CREATION DES TIRS DU BOSS
				PA_DualCreateSprite(tabTir[30].coordonnees.numSprite,(void*)miniTir_Sprite,OBJ_SIZE_8X8,1,2,tabTir[30].coordonnees.x,tabTir[30].coordonnees.y);
				spriteReference=tabTir[30].coordonnees.numSprite;
				PA_DualSetSpriteXY(tabTir[30].coordonnees.numSprite,tabTir[30].coordonnees.x,tabTir[30].coordonnees.y);
				for(i=31;i<40;i++)
				{
					PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
					PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
				}
				
				PA_DualCreateSprite(tabTir[40].coordonnees.numSprite,(void*)tir_Sprite,OBJ_SIZE_16X16,1,2,tabTir[40].coordonnees.x,tabTir[40].coordonnees.y);
				spriteReference=tabTir[40].coordonnees.numSprite;
				PA_DualSetSpriteXY(tabTir[40].coordonnees.numSprite,tabTir[40].coordonnees.x,tabTir[40].coordonnees.y);
				for(i=41;i<50;i++)
				{
					PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
					PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
				}
				
				PA_DualCreateSprite(tabTir[50].coordonnees.numSprite,(void*)salveTir_Sprite,OBJ_SIZE_16X16,1,2,tabTir[50].coordonnees.x,tabTir[50].coordonnees.y);
				spriteReference=tabTir[50].coordonnees.numSprite;
				PA_DualSetSpriteXY(tabTir[50].coordonnees.numSprite,tabTir[50].coordonnees.x,tabTir[50].coordonnees.y);
				for(i=51;i<numTirMax;i++)
				{
					PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
					PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
				}
				*/
			}
		}

		if(numEtape==numEtapeBoss1)
		{	// cinquième étape du jeu
			if(debutParcours2==1)
			{	// les premiers paternes (déplacements)
				switch(PA_VBLCounter[1]/60)// permet un affichage plus propre de la vie du joueur
				{	// ici debutParcours indique la direction à prendre
					case  0 : debutParcours=6;vitesseBoss=1;break;
					case  2 : debutParcours=6;vitesseBoss=1;break;
					case  4 : debutParcours=1;vitesseBoss=1;break;
					case  6 : debutParcours=3;vitesseBoss=1;break;
					case  7 : debutParcours=5;vitesseBoss=1;break;
					case 10 : debutParcours=8;vitesseBoss=2;break;
					case 11 : debutParcours=5;vitesseBoss=1;break;
					case 12 : debutParcours=5;vitesseBoss=1;break;
					case 15 : debutParcours=6;vitesseBoss=1;break;
					case 17 : debutParcours=7;vitesseBoss=1;break;
					case 19 : debutParcours=1;vitesseBoss=1;break;
					case 21 : debutParcours=6;vitesseBoss=1;break;
					case 23 : debutParcours=5;vitesseBoss=1;actionTir=2;break;
					case 28 : debutParcours=5;actionTir=1;break;
					case 30 : debutParcours2++;PA_VBLCounterStart(1);break;// 6-60 == 6 secondes. On boucle sur le parcours
					default: break;
				}
			}
			else
			{	// paternes qui se répétent
				switch(PA_VBLCounter[1]/60)// permet un affichage plus propre de la vie du joueur
				{	// ici debutParcours indique la direction à prendre
					case  0 : debutParcours=1;vitesseBoss=1;break;
					case  1 : debutParcours=8;vitesseBoss=1;break;
					case  2 : debutParcours=3;vitesseBoss=2;break;
					case  3 : debutParcours=8;vitesseBoss=1;break;
					case  4 : debutParcours=5;vitesseBoss=1;break;
					case  7 : debutParcours=7;vitesseBoss=2;actionTir=2;break;
					case  8 : debutParcours=1;vitesseBoss=1;actionTir=1;break;
					case  9 : debutParcours=5;vitesseBoss=1;break;
					case 12 : debutParcours=3;vitesseBoss=1;break;
					case 13 : debutParcours=6;vitesseBoss=1;break;
					case 14 : debutParcours=5;vitesseBoss=1;break;
					case 18 : debutParcours=6;vitesseBoss=1;break;
					case 20 : debutParcours=7;vitesseBoss=1;actionTir=2;break;
					case 22 : debutParcours=1;vitesseBoss=1;actionTir=1;break;
					case 24 : debutParcours=6;actionTir=1;break;
					case 26 : debutParcours=8;actionTir=1;actionTir=2;break;
					case 27 : debutParcours=5;actionTir=1;actionTir=1;break;
					case 30 : PA_VBLCounterStart(1);debutParcours2++;
							break;
					default: break;
				}
			}
			//*
			if(debutParcours!=5)
			{
				deplacementBoss(&boss,debutParcours,vitesseBoss);
			}
			
			if(boss.sprite1.nbPV<=0 && boss.sprite2.nbPV<=0 && boss.sprite3.nbPV<=0 && boss.sprite4.nbPV<=0)
			{
				numEtape++;//il est mort
				debutParcours=2;
			}
		}
		
		if(actionTir && numEtape==numEtapeBoss1 && cptTirActifEnnemi==(PA_VBLCounter[15]/15))
		{	// cinquième étape du jeu
			int X=boss.sprite1.x, Y=boss.sprite1.y;
			int lanceurX1=X+boss.origineTir1[0], lanceurY1=Y+boss.origineTir1[1],
				lanceurX2=X+boss.origineTir2[0], lanceurY2=Y+boss.origineTir2[1],
				lanceurX3=X+boss.origineTir3[0], lanceurY3=Y+boss.origineTir3[1];
			
			if(actionTir==1 && (cptTirActifEnnemi)%2 == 0)// tirs normaux et moment de les tirer
			{
				if(boss.sprite4.nbPV>0){nouveauTir(&tabTir[50],10,2, lanceurX3, lanceurY3);}//celui du milieu // 2 fois moins de grosse boulette
				if(boss.sprite3.nbPV>0){nouveauTir(&tabTir[30],10,2,	  	 lanceurX2, lanceurY2);}//celui à gauche
				if((cptTirActifEnnemi)%4 == 0){nouveauTir(&tabTir[40],10,2,	 lanceurX1-15, lanceurY1-15);}//celui à droite
			}
			else
			{
				if(actionTir==2)// boulettes 2 fois plus souvent
				{
					if(boss.sprite4.nbPV>0){nouveauTir(&tabTir[50],10,2, lanceurX3, lanceurY3);}//celui du milieu // 2 fois moins de grosse boulette
					if(boss.sprite3.nbPV>0){nouveauTir(&tabTir[30],10,2,	  	 lanceurX2, lanceurY2);}//celui à gauche
					if((cptTirActifEnnemi)%2 == 0){nouveauTir(&tabTir[40],10,2,	 lanceurX1-15, lanceurY1-15);}//celui à droite
				}
			}
			//*/
			cptTirActifEnnemi++;
		}
		
		if(numEtape==numEtapeBoss1+1 && debutParcours2==2)
		{
			destructionBoss(tabTir);
			debutParcours=1;
		}
		
		if(numEtape==numEtapeMax)//fin du jeu
		{
			if(debutParcours!=0) // bricolage
			{
				PA_VBLCounterStart(1); // reinitialisation du compteur d'étapes
				debutParcours=0;
				PA_OutputText(0,0,10,"DERNIER NIVEAU TERMINE !!!");
			}
			if((PA_VBLCounter[1]/60)==3)
			{
				PA_ClearTextBg(0);
				numEtape++;
				PA_VBLCounterStart(1);
				debutParcours=1;
				debutParcours2=1;
				debutParcours3=1;
				PA_VBLCounterStart(1);
				PA_VBLCounterStart(15);
				PA_VBLCounterStart(16);
				cptTirActif=0;
				cptTirActifEnnemi=0;
				actionTir=true;
				
				PA_OutputText(1,1,17,"												END GAME\nMerci d'avoir joué \nSi tu a vu des bugs-problèmes \nMerci de me les parvenir\nMail : iut.life@gmail.com\nStart -> Quitter");
			}
		}
		
		/*
		DETECTION DES COLLISIONS !!!
		*/
		
		//deplacementSprite(0,100,&(sprite1.x),&(sprite1.y));
		if(niveauTir!=0) // si peace, alors juste observation
		{
			for(i=0;i<numTir;i++)// pour tout les tirs
			{
				if(tabTir[i].tirActif)// si le tir est à l'écran
				{
					if(tabTir[i].directionTir==1)// il doit attaquer les ennemis
					{
						if(numEtape==numEtapeBoss1)//combat contre boss
						{
							if(boss.sprite1.nbPV>0)
							{	detectionCollisionSprite_tir_et_destruction(&(boss.sprite1),&(tabTir[i]));	}
							if(boss.sprite2.nbPV>0)
							{	detectionCollisionSprite_tir_et_destruction(&(boss.sprite2),&(tabTir[i]));	}
							if(boss.sprite3.nbPV>0)
							{	detectionCollisionSprite_tir_et_destruction(&(boss.sprite3),&(tabTir[i]));	}
							if(boss.sprite4.nbPV>0)
							{	detectionCollisionSprite_tir_et_destruction(&(boss.sprite4),&(tabTir[i]));	}
						}
						else//detection normale
						{
							for(cpt=0;cpt<nbEnnemi0;cpt++)// detection pour les ennemis du bas
							{
								if(tabEnnemi0[cpt].nbPV>0)
								{	detectionCollisionSprite_tir_et_destruction(&(tabEnnemi0[cpt]),&(tabTir[i]));	}
							}
							for(cpt=0;cpt<nbEnnemi;cpt++)// et du haut
							{
								if(tabEnnemi[cpt].nbPV>0)
								{	detectionCollisionSprite_tir_et_destruction(&(tabEnnemi[cpt]),&(tabTir[i]));	}
							}
						}
					}
					else 
					{
						if(tabTir[i].directionTir==2 && numEtape!=numEtapeBoss1)// il doit attaquer le Joueur et hors combat contre boss
						{	detectionCollisionSprite_tir_et_destruction(&(Joueur),&(tabTir[i]));	}
					}
				}
			}
			
			if(numEtape==numEtapeBoss1)// si combat contre boss, y'a plein d'autres tirs menaçant pour le joueur ...
			{
				int compteurDeTir;
				for(compteurDeTir=30;compteurDeTir<numTirMax;compteurDeTir++)
				{
					detectionCollisionSprite_tir_et_destruction(&(Joueur),&(tabTir[compteurDeTir]));
				}
			}
		
		}
		//*/
		switch(propreteAffichageTir)// permet un affichage plus propre de la vie du joueur
		{
			case 0 : if(Joueur.nbPV<=1000){propreteAffichageTir++;PA_ClearTextBg(1);}break;
			case 1 : if(Joueur.nbPV<=100){propreteAffichageTir++;PA_ClearTextBg(1);}break;
			case 2 : if(Joueur.nbPV<=10){propreteAffichageTir++;PA_ClearTextBg(1);}break;
			case 3 : if(Joueur.nbPV<=0){propreteAffichageTir++;PA_OutputText(1,0,0,"VIE 0",Joueur.nbPV);}break;
			case 4 : propreteAffichageTir=0;break;
			default: break;
		}
		
		PA_OutputText(1,0,0,"VIE %d",Joueur.nbPV);
		
		/*
		DETECTION DES TIRS DU JOUEUR !!!
		*/
		
		//if(PA_CheckLid()) // Checks the lid, and pauses if closed... Returns 1 when it unpauses
		//	PA_WaitForVBL();
		
		if(niveauTir==0)
		{
			PA_OutputText(0,27,23,"peace");
		}
		
		// verification des tirs pour les miniTirs
		if(actionTir && niveauTir==1 && Pad.Newpress.A && (PA_VBLCounter[16]/15)>=cptTirActif) // PA_VBLCounter[1]/30 = toutes les 1/2 secondes
		{
			nouveauTir(tabTir,10,1,Joueur.x+10,Joueur.y+200);//un tir a été tiré, +200 car joueur est dans écran du bas
			cptTirActif++;
			PA_OutputText(0,31,23,"*");
			if(cptTirActif<(PA_VBLCounter[16]/30))
			{
				cptTirActif=0;
				PA_VBLCounterStart(16);
			}
		}
		
		// verification des tirs pour les salveTirs
		if(actionTir && niveauTir==2 && Pad.Newpress.A && (PA_VBLCounter[16]/60)>=cptTirActif)// toutes les secondes
		{
			nouveauTir(&(tabTir[15]),10,1,Joueur.x+10,Joueur.y+200);//un tir a été tiré, +200 car joueur est dans écran du bas
			cptTirActif++;
			PA_OutputText(0,30,23,"**");
			if(cptTirActif<(PA_VBLCounter[16]/60))
			{
				cptTirActif=0;
				PA_VBLCounterStart(16);
			}
		}
		
		
		if(Pad.Newpress.B)
		{
			PA_ClearTextBg(0); // pour réinitialisé les indications de tirs
			PA_ClearTextBg(1);
			niveauTir++;
			PA_VBLCounterStart(16); // reinitialisation
			cptTirActif=1;
			if(niveauTir==3)
			{	niveauTir=0;	} // maximim atteint, on reprends de 0
		}

		/*
		DEPLACEMENT DE TOUT LES TIRS !!!
		*/
		// verification des tirActif de tout les tirs
		
		for(i=0;i<numTir;i++)
		{
			deplacementTir(&tabTir[i]);
		}
		if(numEtape==numEtapeBoss1)
		{
			for(i=30;i<numTirMax;i++)
			{
				deplacementTir(&tabTir[i]);
			}
		}
		/*
		DEPLACEMENT DU JOUEUR !!!
		*/
		if(Joueur.nbPV>0)
		{
			// deplacement du vaisseau grâce au stylet
			//deplacementSpriteStylet (Joueur.numEcran,Joueur.numSprite,&Joueur.x,&Joueur.y);
			// ou des touches gauches et droite de la DS
			deplacementSpritePad (Joueur.numEcran,Joueur.numSprite,&Joueur.x,&Joueur.y);
		}
		
		/*
		SORTIE DU JEU !!!
		*/
		// appuie de Start pour confirmer la fin du jeu
		if(Pad.Newpress.Start || Joueur.nbPV<=0)
		{
			PA_ClearTextBg(1);
			PA_ClearTextBg(0);
			int compteur0=PA_VBLCounter[0],
			compteur1=PA_VBLCounter[1],
			compteur2=PA_VBLCounter[2],
			compteur3=PA_VBLCounter[3],
			compteur10=PA_VBLCounter[10];
			PA_StopMod();
			// neccessaire pour quitter le jeu : 
			// verif = verifie si un choix a été effectué
			bool verif=false;
			PA_OutputText(1,2,20,"Appuyez sur A pour continuer\n B pour quitter le jeu\n X pour les options");
			if(Joueur.nbPV<=0)
			{
				for(i=0;i<60;i++)
				{
					PA_WaitForVBL();
				}
			}
			while(!verif)
			{
				PA_WaitForVBL();
				// A pour quitter
				if(Pad.Newpress.B)
				{
					PA_ClearTextBg(1);
					sortir=true;
					verif=true;
				}
				// B pour quitter
				if(Pad.Newpress.A)
				{
					PA_ClearTextBg(1);
					verif=true;
				}
				if(Pad.Newpress.X)
				{
					PA_ClearTextBg(1);
					while(!verif)
					{
						PA_OutputText(1,2,20,"Appuyez sur GAUCHE ou DROITE\n A pour sortir des options");
						if(Pad.Newpress.Left) // changement
						{
							PA_ClearTextBg(1);
							if((numMusique-1)>=0)
							{
								numMusique--;
							}
						}
						if(Pad.Newpress.Right)
						{
							PA_ClearTextBg(1);
							if((numMusique+1)<=numMusiqueMax)
							{
								numMusique++;
							}
							else
							{
								PA_OutputText(1,2,17,"Musique Max atteinte !");
							}
							
						}
						if(Pad.Newpress.A) // on sort
						{
							PA_ClearTextBg(1);
							verif=true;
						}
						if(numMusique>=0 && numMusique<=numMusiqueMax)
						{
							PA_OutputText(1,2,18,"Musique : %s", tabMusique[numMusique]);
						}
						PA_WaitForVBL();
					}
					PA_ClearTextBg(1);
					PA_OutputText(1,2,20,"Appuyez sur A pour continuer\n B pour quitter le jeu\n X pour les options");
					verif=false;
				}
			}
			
			if(Joueur.nbPV<=0 && !sortir) // nouvelle partie
			{
				// mise à jour du Joueur
				Joueur.x=100;
				Joueur.y=160;
				Joueur.nbPV=50;
				Joueur.numEtape=0;
				Joueur.temps=0;
				PA_SetSpriteXY(Joueur.numEcran,Joueur.numSprite,Joueur.x,Joueur.y);
				
				// mise à jour des tirs
				PA_ClearTextBg(0); // pour réinitialisé les indications de tirs
				PA_ClearTextBg(1);
			}
			
			// le cheat code est remis à 0
			//cheatCode=0;
			
			if(!sortir) // MUSIQUES
			{
				switch(numMusique)
				{
					case 1  : PA_PlayMod(phoenixIngame);break;
					case 2  : PA_PlayMod(lotus);break;
					default : numMusique=0;
				}
			}
			
			
			// compteur remis par défaut
			PA_VBLCounter[0]=compteur0;
			PA_VBLCounter[1]=compteur1;
			PA_VBLCounter[2]=compteur2;
			PA_VBLCounter[3]=compteur3;
			PA_VBLCounter[10]=compteur10;
			PA_VBLCounterStart(16);cptTirActifEnnemi=1;// pour les tirs des ennemis
			PA_VBLCounterStart(15);cptTirActif=0;      // pour les tirs du Joueur
			
		}
		PA_WaitForVBL();
	} // fin du while(!sortir)
	
	// suppression des sprites utilisés pour le jeu
	PA_DeleteSprite(0,1);
	for(i=0;i<128;i++)
	{
		PA_DeleteSprite(0,i);
		PA_DeleteSprite(1,i);
		PA_DualDeleteSprite(i);
		if(i%10==0)PA_WaitForVBL();
	}
	
	//sans ces WaitForVBL, on a un bug d'algo
	for(i=0;i<10;i++)
	{
		PA_WaitForVBL();
	}
	PA_StopMod();// fin de la musique
	
	//PA_OutputText(1,2,18,"Ce jeu vidéo est fini !!", tabMusique[numMusique]);
	//PA_OutputText(1,0,19,"Veuillez eteindre votre console et reprendre une activité normale ...", tabMusique[numMusique]);
}


int main(int argc, char* argv[])
{
	spaceInvaders();
	return 0;
}

