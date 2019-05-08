#include "gui.h"
gui::gui()
{
}

void gui::renderTileInfo(tile tile) {
	//draw background box
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 0);
	SDL_Rect background = { xLoc, yLoc, boxWidth, boxHeight };
	SDL_RenderFillRect(gRenderer, &background);
	SDL_SetRenderDrawColor(gRenderer, 20, 20, 20, 0);
	SDL_RenderDrawRect(gRenderer, &background);
	//draw outline flourish
	SDL_SetRenderDrawColor(gRenderer, 150, 150, 250, 0);
	SDL_Rect outline = { xLoc + 10, yLoc + 10, boxWidth - 20, boxHeight - 20 };
	SDL_RenderDrawRect(gRenderer, &outline);
	drawText(tile);
}
void gui::setFontSize(int fontSize) {
	gFont = TTF_OpenFont("resource/font1.ttf", fontSize);
}
void gui::drawText(tile tile) {
	std::ostringstream strs;
	strs << "Tile type: ";
	switch (tile.getNoise()) {
	case 0: strs << "Water"; break;
	case 1: strs << "Plains"; break;
	case 2: strs << "Hills"; break;
	case 3: strs << "Rocks"; break;
	case 4: strs << "Mountains"; break;
	}
	setFontSize(28);
	SDL_Color textColor = { 255, 255 , 255 };
	std::string str = strs.str();
	gTextTexture.loadFromRenderedText(str, textColor);
	gTextTexture.render(xLoc + 20, yLoc + 20);
	setFontSize(40);
}