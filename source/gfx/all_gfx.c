//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .c, for easier inclusion in a project

#ifdef __cplusplus
extern "C" {
#endif

#include "all_gfx.h"


// Sprite files : 
#include "miniTir.c"
#include "salveTir.c"
#include "tir.c"
#include "Laser.c"
#include "Octopus.c"
#include "Crab.c"
#include "Squid.c"
#include "Boss.c"
#include "Boss2.c"
#include "Boss3.c"
#include "Boss4.c"
#include "ship.c"
#include "Asteroide.c"

// Background files : 
#include "backg.c"
#include "espace.c"

// Palette files : 
#include "tir.pal.c"
#include "ennemis.pal.c"
#include "sprites.pal.c"
#include "Asteroide.pal.c"
#include "backg.pal.c"
#include "espace.pal.c"

// Background Pointers :
PAGfx_struct backg = {(void*)backg_Map, 1536, (void*)backg_Tiles, 21824, (void*)backg_Pal, (int*)backg_Info };
PAGfx_struct espace = {(void*)espace_Map, 768, (void*)espace_Tiles, 48448, (void*)espace_Pal, (int*)espace_Info };


#ifdef __cplusplus
}
#endif

