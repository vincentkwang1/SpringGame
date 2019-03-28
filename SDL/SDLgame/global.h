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
extern LTexture gShipTexture;
extern LTexture gSelectedTexture;
extern LTexture gBackgroundTexture;
extern LTexture gTurret2OffTexture;
extern LTexture gTextBoxTexture;
extern 	LTexture gNodeTexture;
extern 	LTexture gTurretTexture;
extern 	LTexture gLightTexture;
extern LTexture gBeamTexture;
extern LTexture gSkipButtonTexture;
extern LTexture gMiniTextBoxTexture;
extern 	LTexture gEnemyTexture;
extern 	LTexture gBulletTexture;
extern LTexture gExplosionTexture;
extern LTexture gBullet2Texture;
extern LTexture gTurret2Texture;
extern LTexture gCrewSpriteSheetTexture;
extern LTexture gShieldNodeTexture;
extern LTexture gCarriedTurretTexture;
extern LTexture gCarriedTurret2Texture;
extern LTexture gCarriedShieldTexture;
extern LTexture gLightSittingTexture;
extern LTexture gSittingTexture;
extern LTexture gHealthBarTexture;
extern LTexture gBullet3Texture;
extern LTexture gDarkTexture;
extern LTexture gTurretOffTexture;
extern LTexture gLightOutTexture;
extern LTexture gEmptyNodeTexture;
extern LTexture gCrewSelectedTexture;
extern LTexture gSittingSelectedTexture;
extern LTexture gLightSittingSelectedTexture;
extern LTexture gSpawnerTexture;
#endif // !global_h_