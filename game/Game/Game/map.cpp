#include "map.h"
#include "tile.h"
#include <vector>

map::map() {
	loaded = false;
	//create placeholder troop
	alliedTroops.push_back(troop());
	enemyTroops.push_back(troop());
}
map::map(int width, int height, std::vector<int> mapdata,std::vector<int> tempdata, bool mapType, int gLocalXCoord, int gLocalYCoord) {
	loaded = true;
	mapHeight = height;
	mapWidth = width;
	if (!mapType) { //if its the regional map
		localXCoord = gLocalXCoord;
		localYCoord = gLocalYCoord;

		mapContainer.resize(height, std::vector<tile>(0));

		int j = 0;
		int k = 0;
		//for each piece of map data
		for (int i = 0; i < width * height; i++) {

			//if you hit the end of a line
			if (k >= width) {
				j++;
				k = 0;
			}

			//adds a tile to the end of the row at height k
			mapContainer[j].push_back(createTile(mapdata[i], tempdata[i], k, j));
			k++;
		}
	}
	else { //for the world map
		worldArray = mapdata;
	}
	alliedTroops.push_back(troop());
	enemyTroops.push_back(troop());
}
bool map::getLoaded() {
	return loaded;
}
void map::render(int currentMapX, int currentMapY) {
	//draw the background gray
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 0);
	//map is 840x840
	SDL_Rect background = { 600, 180, mapPixelWidth + 40, mapPixelWidth + 40 };
	SDL_RenderFillRect(gRenderer, &background);
	//draw the individual tiles
	SDL_Rect r = { 0, 0, mapPixelWidth/mapWidth, mapPixelWidth/mapHeight };
	bool highlight = false;
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			//decides whether to highlight && what color highlight
			if (x == currentMapX && y == currentMapY) {
				SDL_SetRenderDrawColor(gRenderer, 255, 211, 53, 0);
				highlight = true;
			}
			else if (x == currentMapX) {
				if (y == currentMapY - 1 || y == currentMapY + 1) {
					SDL_SetRenderDrawColor(gRenderer, 53, 255, 211, 0);
					highlight = true;
				}
			}
			else if (y == currentMapY) {
				if (x == currentMapX - 1 || x == currentMapX + 1) {
					SDL_SetRenderDrawColor(gRenderer, 53, 255, 211, 0);
					highlight = true;
				}
			}
			mapNoise = worldArray[mapWidth * y + x];
			if(highlight){
				r.x = 620 + mapPixelWidth / mapWidth * x;
				r.y = 200 + mapPixelWidth / mapHeight * y;
				r.w = mapPixelWidth / mapWidth;
				r.h = mapPixelWidth / mapHeight;
				SDL_RenderFillRect(gRenderer, &r);
				if (mapNoise >= 0 && mapNoise < 101) { //water
					SDL_SetRenderDrawColor(gRenderer, 0, 119, 190, 0);
				}
				else if (mapNoise >= 101 && mapNoise < 132) { //grass
					SDL_SetRenderDrawColor(gRenderer, 10, 168, 54, 0);
				}
				else if (mapNoise >= 132 && mapNoise < 145) { //hill
					SDL_SetRenderDrawColor(gRenderer, 12, 137, 22, 0);
				}
				else if (mapNoise >= 145 && mapNoise < 165) { //JV mountain
					SDL_SetRenderDrawColor(gRenderer, 132, 132, 132, 0);
				}
				else if (mapNoise >= 165 && mapNoise <= 255) { //real mountain
					SDL_SetRenderDrawColor(gRenderer, 229, 229, 229, 0);
				}
				r.x = 622 + mapPixelWidth / mapWidth * x;
				r.y = 202 + mapPixelWidth / mapHeight * y;
				r.w = mapPixelWidth/mapWidth - 4;
				r.h = mapPixelWidth/mapHeight - 4;
				SDL_RenderFillRect(gRenderer, &r);
				r.w = mapPixelWidth / mapWidth;
				r.h = mapPixelWidth / mapHeight;
				highlight = false;
			}
			else {
				if (mapNoise >= 0 && mapNoise < 101) { //water
					SDL_SetRenderDrawColor(gRenderer, 0, 119, 190, 0);
				}
				else if (mapNoise >= 101 && mapNoise < 132) { //grass
					SDL_SetRenderDrawColor(gRenderer, 10, 168, 54, 0);
				}
				else if (mapNoise >= 132 && mapNoise < 145) { //hill
					SDL_SetRenderDrawColor(gRenderer, 12, 137, 22, 0);
				}
				else if (mapNoise >= 145 && mapNoise < 165) { //JV mountain
					SDL_SetRenderDrawColor(gRenderer, 132, 132, 132, 0);
				}
				else if (mapNoise >= 165 && mapNoise <= 255) { //real mountain
					SDL_SetRenderDrawColor(gRenderer, 229, 229, 229, 0);
				}
				r.x = 620 + mapPixelWidth / mapWidth * x;
				r.y = 200 + mapPixelWidth / mapHeight * y;
				SDL_RenderFillRect(gRenderer, &r);
			}
		}
	}
	std::ostringstream strs;
	SDL_Color textColor = { 255, 255 , 255 };
	strs << tileType;
	std::string str = strs.str();
	gTextTexture.loadFromRenderedText(str, textColor);
	gTextTexture.render(0, 0);
}

tile map::createTile(int noise, int temp, int i, int j){
	int noiseScale;
	

	//handele height/////////////////////////
	if (noise >= 0 && noise < 91) {
		noiseScale = 0; //water
	}
	else if (noise >= 91 && noise < 132) {
		noiseScale = 1; //grass
	}
	else if (noise >= 132 && noise < 145) {
		noiseScale = 2; //hill
	}
	else if (noise >= 145 && noise < 165) {
		noiseScale = 3; //steep hill or something?
	}
	else if (noise >= 165 && noise <= 255) {
		noiseScale = 4; //mountain
	}
	////////////////////////////////////////////
	int jay[10] = { 3,4,5,6,7,8,5,4,3,6 };
	return tile(noiseScale, temp, false, i, j, 1, jay );
}
std::vector<troop> map::createTroop(tile* tiles, int xCoord, int yCoord, bool team) {
	int x, y;
	do {
		x = 1 + rand() % 5;
		y = 1 + rand() % 5;
	} while (tiles[x * tileX + y].getPassable() == false);
	troop newTroop = {x, y, 1, tiles, team };
	if (team) {
		alliedTroops.push_back(newTroop);
		return alliedTroops;
	}
	else {
		enemyTroops.push_back(newTroop);
		return enemyTroops;
	}
}
std::vector<std::vector<tile>> map::getMapContainer() {
	return mapContainer;
}
std::vector<troop> map::getTroops(bool team) {
	if (team) {
		return alliedTroops;
	}
	else {
		return enemyTroops;
	}
}
void map::setTroops(bool team, std::vector<troop> newTroop) {
	if (team) {
		alliedTroops = newTroop;
	}
	else {
		enemyTroops = newTroop;
	}
}
int map::getTileType(int y, int x) {
	if (worldArray[x*worldWidth + y] >= 0 && worldArray[x * worldWidth + y] < 101) {
		tileType = 0; //water
	}
	else if (worldArray[x * worldWidth + y] >= 101 && worldArray[x * worldWidth + y] < 132) {
		tileType = 1; //grass
	}
	else if (worldArray[x * worldWidth + y] >= 132 && worldArray[x * worldWidth + y] < 145) {
		tileType = 2; //hill
	}
	else if (worldArray[x * worldWidth + y] >= 145 && worldArray[x * worldWidth + y] < 165) {
		tileType = 3; //steep hill or something?
	}
	else if (worldArray[x * worldWidth + y] >= 165 && worldArray[x * worldWidth + y] <= 255) {
		tileType = 4; //mountain
	}
	return tileType;
}
int map::getHeight() {
	return mapHeight;
}
int map::getWidth() {
	return mapWidth;
}





