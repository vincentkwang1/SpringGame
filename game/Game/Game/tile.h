#pragma once
#include "global.h"
#ifndef tile_h_
#define tile_h
class tile {
public:
	 
	//Constants
	static const int tileHight = 10;
	static const int tileWidth = 10;

	//Constructor
	tile() {};
	tile(int noise, int temp, bool trees, bool river, int x, int y, int dev, int buildings[]);


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



private:
	
	//Manage Terrain Type
	int noiseScale; // 0- Ocean, 1- flat, 2- hills, 3- mountains, 4- entirely immpassible
	int tempScale; //1- Ex cold, 2- cool, 3- temperate, 4- warm, 5- Ex hot
	bool hasTrees;
	bool hasRiver;
	
	//Manage Position 
	int xLoc;
	int yLoc;

	//Manage Extra stuff
	int devScale; // 0- no development, 10- metropolis
	int buildingSlots[10]; //tracks what infastructure is built in a given tile

	//Texture Ver
	SDL_Rect tileClip;

};
#endif 
