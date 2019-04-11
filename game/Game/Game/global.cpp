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

//Robert Testing///
LTexture gTile;
LTexture gWaterTexture;
///////////////////

//DELETE THIS
LTexture gTestTexture;
LTexture gGrassTexture;
//DELETE THIS
#endif // !global_h_