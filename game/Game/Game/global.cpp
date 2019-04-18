#ifndef global_h_
#define global_h_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
typedef int32_t s32;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font *gFont;
LTexture gTextTexture;
LTexture gSwordsmanTexture;
LTexture gMountainRockTexture;
LTexture gTile;
LTexture gWaterTexture;
LTexture gHillTexture;
LTexture gImpassableTexture;
LTexture gHills;
LTexture gTestTexture;
LTexture gGrassTexture;
LTexture gEnemyTexture;
#endif // !global_h_