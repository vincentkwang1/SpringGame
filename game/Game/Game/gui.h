#pragma once
#include "global.h"
#include "tile.h"
#ifndef gui_h_
#define gui_h
class gui
{
public:
	gui();
	void renderTileInfo(tile tile);
	void drawText(tile tile);
	void setFontSize(int fontSize);
private:
	int xLoc = 1620;
	int yLoc = 800;
	int boxWidth = 300;
	int boxHeight = 280;
};
#endif