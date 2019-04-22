#include "troop.h"

troop::troop() {

}
troop::troop(int gXCoord, int gYCoord, int type, tile* tiles, bool teamInit) {
	team = teamInit;
	xCoord = gXCoord;
	yCoord = gYCoord;
	updatePos(tiles);
	for (int i = 0; i < 20; i++) {
		troopClips[i].x = 94 * i;
		troopClips[i].y = 0;
		troopClips[i].w = 94;
		troopClips[i].h = 86;
	}
	SDL_Rect tCollider = { xCoord, yCoord, 94, 86 }; 
}
void troop::updatePos(tile* tiles) {
	tPosX = tiles[tileX * xCoord + yCoord].getX() + 60;
	tPosY = tiles[tileY * xCoord + yCoord].getY() - 60;
}
void troop::move() {
	tPosX += velX;
	tPosY += velY;
}
void troop::handleEvent(SDL_Event& e) {
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
	SDL_Rect* currentClip[6];
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
	int clip = frame / 5 % 20;
	if (team) {
		if (attacking) {
			if (clip > 13 && clip < 18){
				gSwordsmanTexture.render(tPosX - 90, tPosY + 90, currentClip[0]);
			}
			else{
				gSwordsmanTexture.render(tPosX + 30, tPosY + 30, currentClip[0]);
			}
		}
		else {
			gSwordsmanTexture.render(tPosX + 30, tPosY + 30, currentClip[0]);
		}/*
		gSwordsmanTexture.render(tPosX + 40, tPosY, currentClip[1]);
		gSwordsmanTexture.render(tPosX - 10, tPosY + 30, currentClip[2]);
		gSwordsmanTexture.render(tPosX + 30, tPosY + 30, currentClip[3]);
		gSwordsmanTexture.render(tPosX + 50, tPosY + 60, currentClip[4]);
		gSwordsmanTexture.render(tPosX + 10, tPosY + 60, currentClip[5]);*/

		//UPDATING FRAME COUNTERS
		if (frame < 100) {
			frame++;
		}
		else {
			frame = 0;
		}
		std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << movesTaken;
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(40, 20);
	}
	else {
		gEnemyTexture.render(tPosX + 30, tPosY + 30, currentClip[0]);/*
		gEnemyTexture.render(tPosX + 40, tPosY, currentClip[1]);
		gEnemyTexture.render(tPosX - 10, tPosY + 30, currentClip[2]);
		gEnemyTexture.render(tPosX + 30, tPosY + 30, currentClip[3]);
		gEnemyTexture.render(tPosX + 50, tPosY + 60, currentClip[4]);
		gEnemyTexture.render(tPosX + 10, tPosY + 60, currentClip[5]);*/

		//UPDATING FRAME COUNTERS
		if (frame < 100) {
			frame++;
		}
		else {
			frame = 0;
		}
	}
}
int * troop::getPos() {
	int coords[2];
	coords[0] = xCoord;
	coords[1] = yCoord;
	return coords;
}
bool troop::moveTroop(tile * tiles, int direction) {
	bool success = true;
	switch(direction){
	case 0:
		if (tiles[tileY * (xCoord-1) + yCoord].getPassable()) {
			xCoord = xCoord - 1;
		}
		else{
			success = false;
		}
		break;
	case 1:
		if (tiles[tileY * xCoord + (yCoord-1)].getPassable()) {
			yCoord = yCoord - 1;
		}
		else {
			success = false;
		}
		break;
	case 2: 
		if (tiles[tileY * (xCoord+1) + yCoord].getPassable()) {
			xCoord = xCoord + 1;
		}
		else {
			success = false;
		}
		break;
	case 3:
		if (tiles[tileY * xCoord + (yCoord+1)].getPassable()) {
			yCoord = yCoord + 1;
		}
		else {
			success = false;
		}
		break;
	}
	if (success) {
		movesTaken++;
	}
	updatePos(tiles);
	if (movesTaken == maxMoves) {
		movesTaken = 0;
		return true;
	}
	else {
		return false;
	}
}
void troop::attack() {
	movesTaken = 0;
	frame = 0; //resets frame counter when starting attack animation
	attacking = true;
}