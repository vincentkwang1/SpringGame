#include "tile.h"

//tile::tile() {

//}
tile::tile(int noise, int temp, bool trees, bool river, int x, int y, int dev, int buildings[10]){
	noiseScale = noise;
	tempScale = temp;
	hasTrees = trees;
	hasRiver = river;
	xCoord = x;
	yCoord = y;
	setPosition();

	devScale = dev;
	for (int i = 0; i < 10; i++) {
		buildingSlots[i] = buildings[i];
	}
	for (int i = 0; i < 4; i++) {
		grassClips[i].x = 240 * i;
		grassClips[i].y = 0;
		grassClips[i].w = 240;
		grassClips[i].h = 120;
	}
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
	random = rand() % 4; //creates the random number associated with the tile
	xLoc = 120 * (xCoord + yCoord); //initializes x and y pixel locations
	yLoc = 1080 / 2 + 60 * (xCoord - yCoord);
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
