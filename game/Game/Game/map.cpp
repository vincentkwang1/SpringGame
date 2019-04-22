#include "map.h"
#include "tile.h"
#include <vector>



map::map(int width, int height, std::vector<int> mapdata,std::vector<int> tempdata, bool mapType) {

	mapHeight = height;
	mapWidth = width;

	if (!mapType) { //if its the regional map
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
}

void map::render() {
	//draw the background gray
	SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 0);
	SDL_Rect background = { 540, 120, 840, 840 };
	SDL_RenderFillRect(gRenderer, &background);
	//draw the individual tiles
	SDL_Rect r = { 0, 0, 8, 8 };
	for (int x = 0; x < mapWidth; x++) {
		for (int y = 0; y < mapHeight; y++) {
			int height = worldArray[100 * y + x];
			if (height >= 0 && height < 101) { //water
				SDL_SetRenderDrawColor(gRenderer, 0, 119, 190, 0);
			}
			else if (height >= 101 && height < 132) { //grass
				SDL_SetRenderDrawColor(gRenderer, 10, 168, 54, 0);
			}
			else if (height >= 132 && height < 145) { //hill
				SDL_SetRenderDrawColor(gRenderer, 12, 137, 22, 0);
			}
			else if (height >= 145 && height < 165) { //JV mountain
				SDL_SetRenderDrawColor(gRenderer, 132, 132, 132, 0);
			}
			else if (height >= 165 && height <= 255) { //real mountain
				SDL_SetRenderDrawColor(gRenderer, 229, 229, 229, 0);
			}
			r.x = 560 + 8*x;
			r.y = 140 + 8*y;
			SDL_RenderFillRect(gRenderer, &r);
		}
	}
}

tile map::createTile(int noise, int temp, int i, int j){
	int noiseScale;
	

	//handele height/////////////////////////
	if (noise >= 0 && noise < 101) {
		noiseScale = 0; //water
	}
	else if (noise >= 101 && noise < 132) {
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
	return tile(noiseScale, temp, false, false, i, j, 1, jay );
}

std::vector<std::vector<tile>> map::getMapContainer() {
	return mapContainer;
}

int map::getHeight() {
	return mapHeight;
}
int map::getWidth() {
	return mapWidth;
}





