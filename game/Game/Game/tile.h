#pragma once
#include "global.h"
#include <time.h>
#ifndef tile_h_
#define tile_h
class tile {
public:
	 
	//Constants
	static const int tileHight = 10;
	static const int tileWidth = 10;
	static const int panSpeed = 5;

	//Constructor
	tile() {};
	tile(int noise, int temp, bool trees, bool river, int x, int y, int dev, int buildings[]);
	tile(int side, int i); //hills constructor

	void move();
	//handle panning
	void handleEvent(SDL_Event& e);

	//Rendering Function
	void render(int noise);

	void checkDist(int x, int y);
	//Get Functions
	int getX();
	int getY();

	int getNoise();
	int getTemp();
	bool getTrees();
	bool getRiver();

	int getDev();
	int getBuildSlot(int slotNum);

	//Set Functions
	void setX(int x);
	void setY(int y);

	void setHighlight(int newHighlight);
	void setNoise(int noise);
	void setTemp(int temp);
	void setTrees(bool trees);
	void setRiver(bool river);

	SDL_Rect getCollider();
	void setDev(int dev);
	void setBuildSlot(int slot, int building);

	bool getPassable();
	void setPosition(); //determines position based on coordinates
	void setHillPosition(int borderType); //determines positions of hills
	//0 is x = 0, 1 is x = max, 2 is y = 0, 3 is y = max

private:
	int highlight = 0; //0 is empty, 1 is mouse, 2 is next to troop
	SDL_Rect tCollider;
	bool sideHill = false; //remembers if its a border hill or not
	int hillClip = 0;
	bool showCoords = false; //debugging

	int velX = 0, velY = 0;

	int random; // random integer used to make variety in the tiles 

	//Manage Terrain Type
	int noiseScale; // 0- Ocean, 1- flat, 2- hills, 3- mountains, 4- entirely immpassible
	int tempScale; //1- Ex cold, 2- cool, 3- temperate, 4- warm, 5- Ex hot
	bool hasTrees;
	bool hasRiver;
	
	//Manage Position 
	int xLoc;
	int yLoc;

	//Manage Coordinates
	int xCoord;
	int yCoord;

	//Manage Extra stuff
	int devScale; // 0- no development, 10- metropolis
	int buildingSlots[10]; //tracks what infastructure is built in a given tile

	//Texture Ver
	SDL_Rect grassClips[4];
	SDL_Rect hillClips[8];
	SDL_Rect mountainClips[12];
	SDL_Rect waterClips[3];
};
#endif 
