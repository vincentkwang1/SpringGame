#pragma once
#include "global.h"
#ifndef bullet_h_
#define bullet_h
class bullet {
public:
	static const int bullet_height = 6;
	static const int bullet_width = 15;
	bullet() {};
	bullet(SDL_Point* point, int angle, int type);
	void move(SDL_Rect ship []);
	bool checkShipCollision(SDL_Rect* ship);
	int getType();
	void render(int frame);
	bool getAlive();
	int getDamage();
	void setAlive(bool newAlive);
	SDL_Rect getCollider();
	bool checkCollision(SDL_Rect* a, SDL_Rect* b);
private:
	int pAngle;
	int bulletType;//1 is 1dmg, 2 is 5 dmg, 3 is enemies shots
	int dmg = 0;
	SDL_Rect bulletClips[5];
	bool alive = true;
	int bPosX, bPosY;
	int bVelX, bVelY;
	SDL_Rect bCollider;
};
#endif 
