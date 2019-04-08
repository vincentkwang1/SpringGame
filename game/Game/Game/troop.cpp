#include "troop.h"
troop::troop() {
	
}
troop::troop(int gXCoord, int gYCoord, int type, tile tiles[]) {
	xCoord = gXCoord;
	yCoord = gYCoord;
	updatePos(tiles);
	for (int i = 0; i < 20; i++) {
		troopClips[i].x = 94 * i;
		troopClips[i].y = 0;
		troopClips[i].w = 94;
		troopClips[i].h = 86;
	}
}
void troop::updatePos(tile tiles[]) {
	tPosX = tiles[12 * xCoord + yCoord].getX() + 60;
	tPosY = tiles[12 * xCoord + yCoord].getY() - 60;
}
void troop::move() {
	tPosX += velX;
	tPosY += velY;
}
void troop::handleEvent(SDL_Event& e){
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: velX = panSpeed; break;
		case SDLK_DOWN: velY = -panSpeed; break;
		case SDLK_RIGHT: velX = -panSpeed; break;
		case SDLK_UP: velY = panSpeed; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: velX = 0; break;
		case SDLK_DOWN: velY = 0; break;
		case SDLK_RIGHT: velX = 0; break;
		case SDLK_UP: velY = 0; break;
		}
	}
}
void troop::render() {
	SDL_Rect* currentClip [6];
	if (attacking) { //if attacking is true, execute attack animation
		for (int i = 0; i < 6; i++) {
			currentClip[i] = &troopClips[(frame / 5 + i) % 20];
		}
		if ((frame / 5) % 20 == 19) { //stops attacking when last animation is done
			attacking = false;
		}
	}
	else { //otherwise, idle animation
		for (int i = 0; i < 6; i++) {
			currentClip[i] = &troopClips[9 + (frame / 10 + i * 2) % 4];
		}
	}
	gSwordsmanTexture.render(tPosX, tPosY, currentClip[0]);
	gSwordsmanTexture.render(tPosX + 40, tPosY, currentClip[1]);
	gSwordsmanTexture.render(tPosX - 10, tPosY + 30, currentClip[2]);
	gSwordsmanTexture.render(tPosX + 30, tPosY + 30, currentClip[3]);
	gSwordsmanTexture.render(tPosX + 50, tPosY + 60, currentClip[4]);
	gSwordsmanTexture.render(tPosX + 10, tPosY + 60, currentClip[5]);

	//UPDATING FRAME COUNTERS
	if (frame < 100) {
		frame++;
	}
	else {
		frame = 0;
	}
	std::ostringstream strs;
	SDL_Color textColor = { 255, 255 , 255 };
	strs << xCoord << ", " << yCoord;
	std::string str = strs.str();
	gTextTexture.loadFromRenderedText(str, textColor);
	gTextTexture.render(40, 20);
}
int * troop::getPos() {
	int coords[2];
	coords[0] = xCoord;
	coords[1] = yCoord;
	return coords;
}
void troop::moveTroop(tile tiles[], int direction) {
	switch(direction){
	case 0: xCoord = xCoord - 1; break;
	case 1: yCoord = yCoord - 1; break;
	case 2: xCoord = xCoord + 1; break;
	case 3: yCoord = yCoord + 1; break;
	}
	updatePos(tiles);
}
void troop::attack() {
	frame = 0; //resets frame counter when starting attack animation
	attacking = true;
}