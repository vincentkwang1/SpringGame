#ifndef global_h_
#define global_h_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
//dimensions of tiles

//Dimensions of Local map
static const int tileX = 12;
static const int tileY = 12;
static const int worldWidth = 30;
static const int worldHeight = 30;
static const int mapPixelWidth = 720; // size of the drawn map
static const int number = (tileX) * (tileY);

typedef int32_t s32;
extern SDL_Window* gWindow;


extern SDL_Renderer* gRenderer;
extern TTF_Font *gFont;
extern LTexture gTextTexture;
extern LTexture gSwordsmanTexture;
extern LTexture gMountainRockTexture;
extern LTexture gWaterTexture;
extern LTexture gHillTexture;
extern LTexture gEnemyTexture;
extern LTexture gHills;
extern LTexture gGrassTexture;
extern LTexture gHighlightTexture;
extern LTexture gSelectingTexture;
#endif // !global_h_