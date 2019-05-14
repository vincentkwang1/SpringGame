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
	bCollider.x = xCoord;
	bCollider.y = yCoord;
	bCollider.w = 159;
	bCollider.h = 139;
}
void button::render() {
	SDL_Rect* currentClip;
	currentClip = &buttonClips[buttonType];
	gButtonTexture.render(xCoord, yCoord, currentClip);
}
SDL_Rect button::getCollider() {
	return bCollider;
}
int button::getType() {
	return buttonType;
}
void button::setType(int newType) {
	buttonType = newType;
}
void button::check(std::vector<map> localMaps) {
	for (int i = 0; i < localMaps.size(); i++) {
		//goes through all maps and checks if they've been loaded
		if (localMaps[i].getLoaded()) {
			//checks if there are any allied troops
			if (localMaps[i].getTroops(true).size() != 1) {
				for (int a = 1; a < localMaps[i].getTroops(true).size(); a++) {
					//cycles through troops to see if any have moves left
					if (localMaps[i].getTroops(true)[a].getMovesLeft()) {
						//if so, sets 'needs orders' and exits method
						buttonType = 1;
						return;
					}
				}
			}
		}
	}
	//otherwise, offers next turn
	buttonType = 0;
}