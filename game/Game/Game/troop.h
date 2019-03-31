#pragma once
#include "global.h"
#ifndef troop_h_
#define troop_h
class troop {
public:
	troop() {};
	troop(int xPos, int yPos, int type); //constructor with type of troop and position
	void move(); //moves the troop
	void render(int frame); //draws the troop
private:
	int tPosX, tPosY;
	int type; //1 = infantry
};
#endif 
