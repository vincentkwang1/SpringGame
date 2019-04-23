#pragma once
#include "global.h"
#include "tile.h"
#include <vector>
#ifndef troop_h_
#define troop_h
class troop {
public:
	static const int maxMoves = 5;
	static const int panSpeed = 5;
	troop();
	troop(int xPos, int yPos, int type, tile * tiles, bool teamInit); //constructor with type of troop and position
	void move(); //moves the troop when panning
	bool moveTroop(tile * tiles, int direction); //actually moves the tile the troop is on, returns successful movement
	//0 is with w, 1 is with a, 2 is with s, 3 is with d
	void attack();
	void updatePos(tile * tiles); //updates the position to match the coordinate
	void render(); //draws the troop
	void handleEvent(SDL_Event& e);
	int * getPos();
	void setSelected(bool newSelected);
	void renderHealthBar();
	SDL_Rect getCollider();
private:
	//FRAME COUNTER
	bool selected = false;
	bool team; //true is player, false is enemy
	int movesTaken = 0;
	int frame = 0;
	SDL_Rect troopClips[20];
	SDL_Rect tCollider;
	bool attacking = false; //determines whether the troop is in its attack animation
	int tPosX = 0, tPosY = 0;
	int xCoord = 0, yCoord = 0;
	int velX = 0, velY = 0;
	int type; //1 = infantry
	SDL_Rect fillRect;
};
#endif 
