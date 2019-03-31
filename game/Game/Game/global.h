#ifndef global_h_
#define global_h_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
typedef int32_t s32;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font *gFont;
extern LTexture gTextTexture;
extern LTexture gSwordsmanTexture;
//DELETE THIS
extern LTexture gTestTexture;
//DELETE THIS
#endif // !global_h_