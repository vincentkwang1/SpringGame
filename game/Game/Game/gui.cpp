#include "gui.h"
gui::gui()
{
}

void gui::render() {
	SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 0);
	//map is 840x840
	SDL_Rect background = { xLoc, yLoc, boxWidth, boxHeight };
	SDL_RenderFillRect(gRenderer, &background);
}