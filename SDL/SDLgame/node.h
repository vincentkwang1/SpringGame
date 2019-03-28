#pragma once
#include "global.h"
#include "bullet.h"
//#include "enemy.h"
class node {
public:
	static const int node_height = 100;
	static const int node_width = 100;
	static const int rotSpd = 2;
	node();
	void move(bullet bullets[], bool eAlive[], bool eVisible[], SDL_Point eCenter[]);
	void setPosition(int position, int nodeType);
	void render(int selectedCrew);
	int getHealth();
	void renderBeam();
	void updatePosition(int nodeType);
	bool checkCollision(SDL_Rect* a, int dmg);
	bool handleEvent(SDL_Event& e);
	SDL_Rect getCollider();
	int getAngle();
	int getType();
	bool checkVisible(SDL_Point eCenter[], bool eVisible[], bool eAlive[]);
	void setAngle(bool eVisible[], SDL_Point eCenter[]);
	int getClosest(bool eAlive[], bool eVisible[], SDL_Point eCenter[]);
	void fire(bullet bullets[]);
	void setAngle(int direction);
	double findAngle(SDL_Point* center);
	double findDistance(SDL_Point* center);
	bool getOccupied();
	bool getReloading();
	void renderHealth();
	void setOccupied(bool newOccupied, bool switching);
	SDL_Point getPoint();
private:
	double targetAngle;
	int closest = 0;
	int bulletnumber;
	int frame = 0;
	int explosionFrame = 0;
	int health = 5;
	int alive;
	int healthIncrements = health / 5;
	int direction;
	int beamAlpha = 0;
	SDL_Rect nodeClips[6];
	SDL_Rect shieldClips[6];
	SDL_Rect explosionClips[7];
	int reloadSpd = 5;
	int reloadProgress = 0;
	bool occupied = false;
	bool firing = false;
	bool reloading = true;
	int nPosX, nPosY;
	SDL_Rect nCollider;
	int type = 1; 
	//1 = quick shooty, 1dmg
	//2 = slow shooty, 5dmg
	//3 = light
	//4 = shield
	int pPosition = 0;
	int angle = 0;
	int rotVel = 0;
};