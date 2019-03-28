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
LTexture gShipTexture;
LTexture gSelectedTexture;
LTexture gBackgroundTexture;
LTexture gNodeTexture;
LTexture gTurret2OffTexture;
LTexture gTurretTexture;
LTexture gLightTexture;
LTexture gMiniTextBoxTexture;
LTexture gTextBoxTexture;
LTexture gBeamTexture;
LTexture gSkipButtonTexture;
LTexture gEnemyTexture;
LTexture gBulletTexture;
LTexture gTurret2Texture;
LTexture gCrewSpriteSheetTexture;
LTexture gHealthBarTexture;
LTexture gExplosionTexture;
LTexture gShieldNodeTexture;
LTexture gBullet2Texture;
LTexture gCarriedTurret2Texture;
LTexture gCarriedShieldTexture;
LTexture gTurretOffTexture;
LTexture gLightSittingTexture;
LTexture gBullet3Texture;
LTexture gLightSittingSelectedTexture;
LTexture gCarriedTurretTexture;
LTexture gSittingTexture;
LTexture gDarkTexture;
LTexture gLightOutTexture;
LTexture gEmptyNodeTexture;
LTexture gCrewSelectedTexture;
LTexture gSpawnerTexture;
LTexture gSittingSelectedTexture;
#endif // !global_h_