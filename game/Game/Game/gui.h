#pragma once
#include "global.h"
#ifndef gui_h_
#define gui_h
class gui
{
public:
	gui();
	void render();
private:
	int xLoc = 1300;
	int yLoc = 800;
	int boxWidth = 620;
	int boxHeight = 280;
};
#endif