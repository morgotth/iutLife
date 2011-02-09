#include "sprites.h"

// initialisation d'une structure Boss avec le boss demandé (par l'entier numBoss
/*
void initialisationBoss(Boss* boss, int numBoss)
{
	if(numBoss==1)// si le 1e boss est demandé
	{
		// pour la structure sprite de la structure Boss
		// le numEcran et le numSprite ne sont pas affectés car dépendent de l'envie du programmeur
		boss->sprite1.x=100;// abscisse du boss
		boss->sprite1.y=100;// ordonnée du boss
		// boss.coordonnees->typeSprite devra être affecté par le programmeur
		
		// pour la structure Boss en elle même
		boss->nombredeSprite=4;
		boss->sprite1.nbPV=300;		 // nombre de point de vie du boss
		boss->typeTir=0;  		 // 0=miniTir, 1=salveTir, 2=tir
		boss->typeTir2=1; 		 // -1=pas de tir, 0=miniTir, 1=salveTir, 2=tir
	}
	
	if(numBoss==2)// si le 2e boss est demandé
	{
		// pour la structure sprite de la structure Boss
		// le numEcran et le numSprite ne sont pas affectés car dépendent de l'envie du programmeur
		boss->sprite1.x=100;// abscisse du boss
		boss->sprite1.y=100;// ordonnée du boss
		// boss.coordonnees->typeSprite devra être affecté par le programmeur
		
		// pour la structure Boss en elle même
		boss->nombredeSprite=4;
		boss->sprite1.nbPV=300;		 // nombre de point de vie du boss
		boss->typeTir=1;  		 // 0=miniTir, 1=salveTir, 2=tir
		boss->typeTir2=2; 		 // -1=pas de tir, 0=miniTir, 1=salveTir, 2=tir
	}
}
//*/

int bi(int y)
// sert juste à savoir si une année est bissextile ou pas
{
    if((!(y%4)&&!(y%1000))||(!(y%4)&&(y%100)))
        return 1;
    else
        return 0;
}

unsigned int getTicks()
// renvoie la durée en secondes depuis le 1er Janvier 1970
{
    unsigned int ret=0;
	int i;
	unsigned int mois[12]={31,0,31,30,31,30,31,31,30,31,30,31};
    for(i=0;i<30+PA_RTC.Year;i++)
        ret+=(bi(1970+i)?366:365)*24*3600;
    for(i=0;i<PA_RTC.Month-1;i++)
    {
        mois[1]=(bi(2000+PA_RTC.Year)?29:28);
        ret+=mois[i]*24*3600;
    }
    ret+=(PA_RTC.Day-1)*24*3600;
	ret+=PA_RTC.Seconds+PA_RTC.Minutes*60+(PA_RTC.Hour-1)*3600;
    return ret;
}

int nouveauTir (Tir* tabTir, int nbTir, int directionTirSouhaite, int xlanceurDuTir, int yLancementDuTir)
// renvoie si un tir a été tiré ou pas
{
	int tirAffecte=0, cpt=0, valRetour=0;
	while(!tirAffecte && cpt<nbTir)
	{
		if(!tabTir[cpt].tirActif)// si un Tir non actif
		{
			tirAffecte=1;
			tabTir[cpt].tirActif=1;
			tabTir[cpt].directionTir=directionTirSouhaite;
			valRetour=1;
			
			// X
			tabTir[cpt].coordonnees.x=xlanceurDuTir;
			if(tabTir[cpt].typeTir==2)
			{	tabTir[cpt].coordonnees.x=(xlanceurDuTir+8);	}
			
			// Y
			tabTir[cpt].coordonnees.y=yLancementDuTir;
		}
		cpt++;
	}
	return valRetour;
}

void preparationBoss(Tir* tabTir)
{
	int i;
	for(i=51;i<62;i++)// destruction de tout les ennemis du bas
	{
		PA_DeleteSprite(0,i);
	}
	for(i=63;i<80;i++)// destruction de tout les ennemis en haut
	{
		PA_DualDeleteSprite(i);
	}
	
	/* 			CREATION DES TIRS DU BOSS 		*/
	PA_DualCreateSprite(tabTir[30].coordonnees.numSprite,(void*)miniTir_Sprite,OBJ_SIZE_8X8,1,2,tabTir[30].coordonnees.x,tabTir[30].coordonnees.y);
	int spriteReference=tabTir[30].coordonnees.numSprite;
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
	for(i=51;i<60;i++)
	{
		PA_DualCloneSprite((tabTir[i].coordonnees.numSprite),spriteReference);	
		PA_DualSetSpriteXY(tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
	}
}

void destructionBoss(Tir* tabTir)
{
	int i;
	for(i=124;i<128;i++)// destruction de toutes les parties du boss
	{
		PA_DualDeleteSprite(i);
	}
	for(i=81;i<111;i++)// destruction de tout les tirs du boss
	{
		PA_DualSetSpriteXY(i,257,393);
		PA_DualDeleteSprite(i);
	}
	PA_WaitForVBL();
}

//void 
/*
int initialisationTabSprite(int nbEcran, int numSpriteDepartint nbcree, 
for(i=0;i<10;i++)
	{
		tabTir[i].coordonnees.numEcran=0;
		tabTir[i].coordonnees.numSprite=(10+i);
		tabTir[i].coordonnees.x=256;
		tabTir[i].coordonnees.y=192;
		tabTir[i].tirActif=false;
		tabTir[i].vitesseTir=2;
		tabTir[i].puissanceTir=2;
		tabTir[i].typeTir=0;
		tabTir[i].coordonnees.typeSprite=&tabTS[6];
		if(i==0)
			PA_CreateSprite(tabTir[i].coordonnees.numEcran,tabTir[i].coordonnees.numSprite,(void*)miniTir_Sprite,OBJ_SIZE_8X8,1,2,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
		else
			PA_CloneSprite(tabTir[0].coordonnees.numEcran,(((tabTir[i].coordonnees.numSprite))),tabTir[0].coordonnees.numSprite);	
		PA_SetSpriteXY(tabTir[i].coordonnees.numEcran,tabTir[i].coordonnees.numSprite,tabTir[i].coordonnees.x,tabTir[i].coordonnees.y);
		// pour l'instant, vitesse et puissance = 2
	}
*/

