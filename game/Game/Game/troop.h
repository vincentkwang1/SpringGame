#pragma once
#include "global.h"
#include "tile.h"
#ifndef troop_h_
#define troop_h
class troop {
public:
	static const int panSpeed = 5;
	troop();
	troop(int xPos, int yPos, int type, tile tiles[]); //constructor with type of troop and position
	void move(); //moves the troop when panning
	void moveTroop(tile tiles[], int direction); //actually moves the tile the troop is on
	//0 is with w, 1 is with a, 2 is with s, 3 is with d
	void attack();
	void updatePos(tile tiles[]); //updates the position to match the coordinate
	void render(); //draws the troop
	void handleEvent(SDL_Event& e);
	int * getPos();
private:
	//FRAME COUNTER
	int frame = 0;
	SDL_Rect troopClips[20];
	bool attacking = false; //determines whether the troop is in its attack animation
	int tPosX, tPosY;
	int xCoord, yCoord;
	int velX = 0, velY = 0;
	int type; //1 = infantry
};
#endif 
