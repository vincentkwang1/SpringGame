#pragma once
#include "global.h"
#ifndef troop_h_
#define troop_h
class troop {
public:
	troop();
	troop(int xPos, int yPos, int type); //constructor with type of troop and position
	void move(); //moves the troop, not yet implemented
	void attack();
	void render(); //draws the troop
private:
	//FRAME COUNTER
	int frame = 0;
	SDL_Rect troopClips[20];
	bool attacking = false; //determines whether the troop is in its attack animation
	int tPosX, tPosY;
	int type; //1 = infantry
};
#endif 
