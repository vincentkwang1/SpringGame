#include "structure.h"
structure::structure()
{
	type = 0;
	xCoord = 5;
	yCoord = 3;
	setPosition();
}
void structure::render() {
	if (type == 0) {
		gCastleTexture.render(xLoc, yLoc);
	}
}
void structure::setPosition() {
	xLoc = 120 * (xCoord + yCoord); //initializes x and y pixel locations
	yLoc = 280 + 60 * (xCoord - yCoord);
}