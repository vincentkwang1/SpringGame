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
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font *gFont;
extern LTexture gTextTexture;
extern LTexture gSwordsmanTexture;

extern LTexture gTile;
extern LTexture gHills;

extern LTexture gGrassTexture;
#endif // !global_h_