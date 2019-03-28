#pragma once
#include "LTexture.h"
class background {
public:
	void render();
	void loadMedia(int which);
private:
	LTexture gBackgroundTexture;
	LTexture gGalaxyMapTexture;
};
