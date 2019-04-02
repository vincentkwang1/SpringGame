#pragma once
#include "global.h"
#include "tile.h"
#ifndef map_h_
#define map_h
class map {
public:
	static const int mapHeight = 100;
	static const int mapWidth = 100;
	//Constructors
	map() {};

	map(int width, int height, int mapdata[]);

	//display map on screen
	void render();

private:

	int mapWidth, mapHeight;

	//tile mapContainer[][];

};
#endif 
