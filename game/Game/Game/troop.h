#pragma once
#include "global.h"
#include "tile.h"
#include <vector>
#ifndef troop_h_
#define troop_h
class troop {
public:
	static const int panSpeed = 5;
	troop();
	troop(int invisible);
	troop(int xPos, int yPos, int type, tile* tiles, bool teamInit); //constructor with type of troop and position
	void move(); //moves the troop when panningx
	int moveTroop(tile* tiles, int direction, std::vector<troop> enemyarmy); //actually moves the tile the troop is on, returns successful movement
	//0 is with w, 1 is with a, 2 is with s, 3 is with d
	void attack();
	void updatePos(tile* tiles); //updates the position to match the coordinate
	void render(); //draws the troop
	void handleEvent(SDL_Event& e);
	int* getPos();
	void setSelected(bool newSelected);
	void setHp(	int newhealth);
	int getHp();
	void renderHealthBar();
	SDL_Rect getCollider();
	bool getPlaceholder();
	bool getMovesLeft();
	bool getAttacking();
	void reset();
	
private:
	//FRAME COUNTER22222
	int maxMoves = 8;
	bool placeholder;

	bool selected = false;
	bool team; //true is player, false is enemy
	int movesLeft = maxMoves;
	int frame = 0;
	int Direction;
	SDL_Rect troopClips[20];
	SDL_Rect tCollider;
	bool attacking = false; //determines whether the troop is in its attack animation
	int tPosX = 0, tPosY = 0;
	int xCoord = 0, yCoord = 0;
	int velX = 0, velY = 0;
	int type; //1 = infantry
	int Health = 100;
	SDL_Rect fillRect;
};
#endif 