#pragma once
#include "global.h"
#ifndef structure_h_
#define structure_h
class structure
{
public:
	structure();
	void render();
	void setPosition();
private:
	int type; //0 is castle
	int xCoord;
	int yCoord;
	int xLoc;
	int yLoc;
};
#endif