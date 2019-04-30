#pragma once
#include "global.h"
#include "tile.h"
#include <vector>
#ifndef map_h_
#define map_h
class map {
public:
	
	//Constructors
	map() {};

	map(int width, int height, std::vector<int> mapdata, std::vector<int> tempdata, bool mapType, int gLocalXCoord, int gLocalYCoord);

	//display map on screen
	void render(int currentMapX, int currentMapY);

	//takes map data and pushes out a tile
	tile createTile(int noise, int temp, int i, int j);

	//Get functions
	std::vector<std::vector<tile>> getMapContainer();
	int getHeight();
	int getWidth();

private:
	int localXCoord = 0;
	int localYCoord = 0;
	std::vector<int> worldArray; //height array for th eworld map
	//Tile container
	std::vector<std::vector<tile>> mapContainer; //[1]
	int mapHeight;
	int mapWidth;
};
#endif 


//[1] https://stackoverflow.com/questions/9694838/how-to-implement-2d-vector-array