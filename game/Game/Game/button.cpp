#include "button.h"
button::button() {
	for (int i = 0; i < 2; i++) {
		buttonClips[i].x = 159 * i;
		buttonClips[i].y = 0;
		buttonClips[i].w = 159;
		buttonClips[i].h = 139;
	}
	xCoord = 1761;
	yCoord = 940;
}
void button::render() {
	SDL_Rect* currentClip;
	currentClip = &buttonClips[buttonType];
	gButtonTexture.render(xCoord, yCoord, currentClip);
}