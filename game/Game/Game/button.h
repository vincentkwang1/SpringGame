#pragma once
#include "global.h"
#ifndef button_h_
#define button_h
class button
{
public:
	button();
	void render();
private:
	int buttonType = 0; //1 is unit needs orders, 0 is next turn
	int xCoord;
	int yCoord;
	SDL_Rect buttonClips[2];
};
#endif