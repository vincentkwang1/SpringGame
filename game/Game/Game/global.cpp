#ifndef global_h_
#define global_h_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
//dimensions of tiles
static const int tileX = 12;
static const int tileY = 12;
static const int number = (tileX) * (tileY);
typedef int32_t s32;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font *gFont;
LTexture gTextTexture;
LTexture gSwordsmanTexture;

LTexture gTile;
LTexture gWaterTexture;
LTexture gHillTexture;
LTexture gMountainTexture;
LTexture gImpassableTexture;
LTexture gHills;
LTexture gTestTexture;
LTexture gGrassTexture;
#endif // !global_h_