#include "map.h"
#include "tile.h"
#include <vector>



map::map(int width, int height, std::vector<int> mapdata,std::vector<int> tempdata) {

	mapHeight = height;
	mapWidth = width;

	mapContainer.resize(height, std::vector<tile>(0));

	int j = 0;
	int k = 0;
	//for each piece of map data
	for (int i = 0; i < width*height; i++) {
		
		//if you hit the end of a line
		if (k >= width) {
			j++;
			k = 0;
		}
		
		//adds a tile to the end of the row at height k
		mapContainer[j].push_back(createTile(mapdata[i], tempdata[i], k,j));
		k++;
	}
}




tile map::createTile(int noise, int temp, int i, int j){
	int noiseScale;
	

	//handele height/////////////////////////
		if (noise >= 0 && noise < 51) {
		noiseScale = 0;
	}
	else if (noise >= 51 && noise < 102) {
		noiseScale = 1;
	}
	else if (noise >= 102 && noise < 153) {
		noiseScale = 2;
	}
	else if (noise >= 153 && noise < 204) {
		noiseScale = 3;
	}
	else if (noise >= 204 && noise <= 255) {
		noiseScale = 4;
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





