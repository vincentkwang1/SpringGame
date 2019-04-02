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

	void move();
	//handle panning
	void handleEvent(SDL_Event& e);

	//Rendering Function
	void render();

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

	void setNoise(int noise);
	void setTemp(int temp);
	void setTrees(bool trees);
	void setRiver(bool river);

	void setDev(int dev);
	void setBuildSlot(int slot, int building);

	void setPosition(); //determines position based on coordinates


private:
	int velX, velY;

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

};
#endif 
