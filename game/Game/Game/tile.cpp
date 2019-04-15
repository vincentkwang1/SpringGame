#include "tile.h"
tile::tile(int noise, int temp, bool trees, bool river, int x, int y, int dev, int buildings[10]){
	noiseScale = noise;
	tempScale = temp;
	hasTrees = trees;
	hasRiver = river;
	xCoord = x;
	yCoord = y;
	setPosition();
	//if its an edge tile, set the adjacent hill position
	if (xCoord == 0) {
		setHillPosition(0);
	}
	else if (xCoord == tileX - 1) {
		setHillPosition(1);
	}
	else if (yCoord == 0) {
		setHillPosition(2);
	}
	else if (yCoord == tileY - 1) {
		setHillPosition(3);
	}
	devScale = dev;
	for (int i = 0; i < 10; i++) {
		buildingSlots[i] = buildings[i];
	}
	//creates the bounds for grassclips
	for (int i = 0; i < 4; i++) {
		grassClips[i].x = 240 * i;
		grassClips[i].y = 0;
		grassClips[i].w = 240;
		grassClips[i].h = 120;
	}
}
tile::tile(int side, int i) {
	setHillPosition(side);
	switch (side) {
	case 0: xCoord = -1; yCoord = i; break;
	case 1: xCoord = tileX; yCoord = i; break;
	case 2: xCoord = i; yCoord = -1; break;
	case 3: xCoord = i; yCoord = tileY; break;
	}
	setPosition();
	//bounds for hillClips
	for (int i = 0; i < 8; i++) {
		hillClips[i].x = 240 * i;
		hillClips[i].y = 0;
		hillClips[i].w = 240;
		hillClips[i].h = 240;
	}
	sideHill = true;
}

void tile::handleEvent(SDL_Event& e) { //0 is left, 1 is down, 2 is right, 3 is up
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: velX = panSpeed; break;
		case SDLK_DOWN: velY = -panSpeed; break;
		case SDLK_RIGHT: velX = -panSpeed; break;
		case SDLK_UP: velY = panSpeed; break;
		case SDLK_F1: showCoords = true; break;
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
		case SDLK_F1: showCoords = false; break;
		}
	}
}
void tile::setPosition() {
	if (!sideHill) {
		random = rand() % 4; //creates the random number associated with the tile
		xLoc = 120 * (xCoord + yCoord); //initializes x and y pixel locations
		yLoc = 1080 / 2 + 60 * (xCoord - yCoord);
	}
	else {
		xLoc = 120 * (xCoord + yCoord); //initializes x and y pixel locations
		yLoc = 1080 / 2 + 60 * (xCoord - yCoord) - 200;
	}
}

void tile::setHillPosition(int borderType) {
	switch (borderType) {
	case 0: hillClip = 6; break;
	case 1: hillClip = 2; break;
	case 2: hillClip = 1; break;
	case 3: hillClip = 7; break;
	}
}

void tile::render() {
	SDL_Rect* currentClip;


	//If water
	if (noiseScale == 0) {
		gWaterTexture.render(xLoc, yLoc);
	}
	else if (noiseScale == 1) {
		currentClip = &grassClips[random];
		gGrassTexture.render(xLoc, yLoc, currentClip);
	}
	else if(noiseScale == 2) {
		gHillTexture.render(xLoc, yLoc);
	}
	else if (noiseScale == 3) {
		gMountainTexture.render(xLoc, yLoc);
	}
	else if (noiseScale == 4) {
		gImpassableTexture.render(xLoc, yLoc);
	}

	//handles hill clipping
	if (sideHill) {
		SDL_Rect* currentHillClip;
		if (hillClip != 0) {
			currentHillClip = &hillClips[hillClip];
			gHills.render(xLoc, yLoc, currentHillClip);
		}
	}
	
	

	if (showCoords) {
		std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << xCoord << ", " << yCoord;
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(xLoc + 40, yLoc + 20);
	}
}

void tile::move() { //0 is left, 1 is down, 2 is right, 3 is up
	xLoc += velX;
	yLoc += velY;
}

//Get Functions
int tile::getX() {
	return xLoc;
}
int tile::getY() {
	return yLoc;
}
int tile::getNoise(){
	return noiseScale;
}
int tile::getTemp(){
	return tempScale;
}
bool tile::getTrees(){
	return hasTrees;
}
bool tile::getRiver(){
	return hasRiver;
}
int tile::getDev() {
	return devScale;
}
int tile::getBuildSlot(int slotNum){
	return buildingSlots[slotNum];
}

//Set Functions
void tile::setX(int x) {
	xLoc = x;
}
void tile::setY(int y) {
	yLoc = y;
}
void tile::setNoise(int noise) {
	noiseScale = noise;
}
void tile::setTemp(int temp) {
	tempScale = temp;
}
void tile::setTrees(bool trees) {
	hasTrees = trees;
}
void tile::setRiver(bool river) {
	hasRiver = river;
}
void tile::setDev(int dev) {
	devScale = dev;
}
void tile::setBuildSlot(int slot, int building) {
	buildingSlots[slot] = building;
}
