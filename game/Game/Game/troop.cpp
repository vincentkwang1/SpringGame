#include "troop.h"

troop::troop() {
	placeholder = true;

}
troop::troop(int gXCoord, int gYCoord, int type, tile* tiles, bool teamInit) {
	placeholder = false;
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
}
void troop::reset() {
	movesLeft = maxMoves;
}
void troop::updatePos(tile* tiles) {
	tPosX = tiles[tileX * xCoord + yCoord].getX() + 60;
	tPosY = tiles[tileY * xCoord + yCoord].getY() - 60;
	tCollider = { tPosX + 30, tPosY + 50, 67, 68 };
}
void troop::move() {
	tPosX += velX;
	tPosY += velY;
	tCollider = { tPosX + 30, tPosY + 50, 67, 68 };
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
SDL_Rect troop::getCollider() {
	return tCollider;
}
bool troop::getPlaceholder() {
	return placeholder;
}
void troop::setSelected(bool newSelected) {
	selected = newSelected;
}
void troop::render() {
	if (!placeholder) {
		if (selected) {
			//gSelectingTexture.render(tPosX + 50, tPosY);
		}
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
				if (clip > 13 && clip < 18) {
					gSwordsmanTexture.render(tPosX - 90, tPosY + 90, currentClip[0]);
				}
				else {
					gSwordsmanTexture.render(tPosX, tPosY, currentClip[0]);
				}
			}
			else {
				gSwordsmanTexture.render(tPosX, tPosY, currentClip[0]);
			}
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
			strs << movesLeft;
			std::string str = strs.str();
			gTextTexture.loadFromRenderedText(str, textColor);
			gTextTexture.render(tPosX, tPosY - 50);
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
		renderHealthBar();
	}
}

void troop::renderHealthBar() {
	if (Health != 100) {
		//Render outside
		fillRect = { tPosX + 20, tPosY, 100, 20 };
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderFillRect(gRenderer, &fillRect);

		//render inside
		fillRect = { tPosX + 25, tPosY + 5, 90 * Health / 100, 10 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect);
	}
}
void troop::setHp(int newhealth) { if (placeholder) { Health = 100; } else { Health = newhealth; } }
int troop::getHp() { return Health; }

int * troop::getPos() {
	int coords[2];
	coords[0] = xCoord;
	coords[1] = yCoord;
	return coords;
}
bool troop::moveTroop(tile* tiles, int direction) {
	bool success = true;
	if (movesLeft > 0) {
		switch (direction) {
		case 0:
			if (tiles[tileY * (xCoord - 1) + yCoord].getPassable()) {
				xCoord = xCoord - 1;
			}
			else {
				success = false;
			}
			break;
		case 1:
			if (tiles[tileY * xCoord + (yCoord - 1)].getPassable()) {
				yCoord = yCoord - 1;
			}
			else {
				success = false;
			}
			break;
		case 2:
			if (tiles[tileY * (xCoord + 1) + yCoord].getPassable()) {
				xCoord = xCoord + 1;
			}
			else {
				success = false;
			}
			break;
		case 3:
			if (tiles[tileY * xCoord + (yCoord + 1)].getPassable()) {
				yCoord = yCoord + 1;
			}
			else {
				success = false;
			}
			break;
		}
		if (success) {
			if (movesLeft - tiles[tileY * xCoord + yCoord].getMovementPenalty() > 0) {
				movesLeft = movesLeft - tiles[tileY * xCoord + yCoord].getMovementPenalty();
			}
			else {
				movesLeft = 0;
			}
		}
		updatePos(tiles);
	}
	if (movesLeft == 0) {
		setSelected(false);
		return true;
	}
	else {
		return false;
	}
}
void troop::attack() {
	movesLeft = 0;
	frame = 0; //resets frame counter when starting attack animation
	attacking = true;
}
bool troop::getMovesLeft() {
	if (movesLeft == 0) {
		return false;
	}
	else {
		return true;
	}
}

bool troop::getAttackRange() { return AttackingRange; }
void troop::setAttackRange(bool inRange) { AttackingRange = inRange; }