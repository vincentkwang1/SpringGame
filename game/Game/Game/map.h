#pragma once
#include "global.h"
#include "tile.h"
#include <vector>
#ifndef map_h_
#define map_h
class map {
public:
	static const int mapHeight = 100;
	static const int mapWidth = 100;
	//Constructors
	map() {};

	map(int width, int height, std::vector<int> mapdata, std::vector<int> tempdata);

	//display map on screen
	void render();

	//takes map data and pushes out a tile
	tile createTile(int noise, int temp, int i, int j);

private:

	

	//Tile container
	std::vector<std::vector<tile>> mapContainer; //[1]
};
#endif 


//[1] https://stackoverflow.com/questions/9694838/how-to-implement-2d-vector-array