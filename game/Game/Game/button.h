#pragma once
#include "global.h"
#include "map.h"
#ifndef button_h_
#define button_h
class button
{
public:
	button();
	void render();
	void check(std::vector<map> localMaps);
	int getType();
	SDL_Rect getCollider();
	void setType(int newType);
private:
	int buttonType = 0; //1 is unit needs orders, 0 is next turn
	int xCoord;
	int yCoord;
	SDL_Rect bCollider;
	SDL_Rect buttonClips[2];
};
#endif