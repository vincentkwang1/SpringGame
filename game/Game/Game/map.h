#pragma once
#include "global.h"
#include "tile.h"
#include "troop.h"
#include <vector>
#ifndef map_h_
#define map_h
class map {
public:
	
	//Constructors
	map();
	map(int width, int height, std::vector<int> mapdata, std::vector<int> tempdata, bool mapType, int gLocalXCoord, int gLocalYCoord);

	//display map on screen
	void render(int currentMapX, int currentMapY);

	//takes map data and pushes out a tile
	tile createTile(int noise, int temp, int i, int j);

	//Get functions
	std::vector<std::vector<tile>> getMapContainer();
	int getHeight();
	int getWidth();

	int getTileType(int x, int y); //returns the type of world tile
	bool getLoaded(); //returns whether or not the map has been loaded

	std::vector<troop> createTroop(tile* tiles, std::vector<troop> troops, int xCoord, int yCoord, bool team);
	std::vector<troop> getTroops();
private:
	std::vector<troop> alliedTroops;
	std::vector<troop> enemyTroops;
	bool loaded;
	int localXCoord = 0;
	int localYCoord = 0;
	std::vector<int> worldArray; //height array for th eworld map
	//Tile container
	std::vector<std::vector<tile>> mapContainer; //[1]
	int mapHeight;
	int mapWidth;
	int mapNoise; //the perlin noise on the tile
	int tileType;
};
#endif 


//[1] https://stackoverflow.com/questions/9694838/how-to-implement-2d-vector-array