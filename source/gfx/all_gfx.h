//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char miniTir_Sprite[64] __attribute__ ((aligned (4))) ;  // Pal : tir_Pal
extern const unsigned char salveTir_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : tir_Pal
extern const unsigned char tir_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : tir_Pal
extern const unsigned char Laser_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : tir_Pal
extern const unsigned char Octopus_Sprite[512] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char Crab_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char Squid_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char Boss_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char Boss2_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char Boss3_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char Boss4_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : ennemis_Pal
extern const unsigned char ship_Sprite[1024] __attribute__ ((aligned (4))) ;  // Pal : sprites_Pal
extern const unsigned char Asteroide_Sprite[4096] __attribute__ ((aligned (4))) ;  // Pal : Asteroide_Pal

// Background files : 
extern const int backg_Info[3]; // BgMode, Width, Height
extern const unsigned short backg_Map[1536] __attribute__ ((aligned (4))) ;  // Pal : backg_Pal
extern const unsigned char backg_Tiles[21824] __attribute__ ((aligned (4))) ;  // Pal : backg_Pal
extern PAGfx_struct backg; // background pointer

extern const int espace_Info[3]; // BgMode, Width, Height
extern const unsigned short espace_Map[768] __attribute__ ((aligned (4))) ;  // Pal : espace_Pal
extern const unsigned char espace_Tiles[48448] __attribute__ ((aligned (4))) ;  // Pal : espace_Pal
extern PAGfx_struct espace; // background pointer


// Palette files : 
extern const unsigned short tir_Pal[162] __attribute__ ((aligned (4))) ;
extern const unsigned short ennemis_Pal[120] __attribute__ ((aligned (4))) ;
extern const unsigned short sprites_Pal[11] __attribute__ ((aligned (4))) ;
extern const unsigned short Asteroide_Pal[158] __attribute__ ((aligned (4))) ;
extern const unsigned short backg_Pal[31] __attribute__ ((aligned (4))) ;
extern const unsigned short espace_Pal[59] __attribute__ ((aligned (4))) ;


#endif

