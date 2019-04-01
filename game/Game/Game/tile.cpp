#include "tile.h"

//tile::tile() {

//}
tile::tile(int noise, int temp, bool trees, bool river, int x, int y, int dev, int buildings[10]){
	noiseScale = noise;
	tempScale = temp;
	hasTrees = trees;
	hasRiver = river;
	xLoc = x;
	yLoc = y;
	devScale = dev;
	for (int i = 0; i < 10; i++) {
		buildingSlots[i] = buildings[i];
	}


}

void tile::render() {
	gTile.render(xLoc, yLoc);
	
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
