#pragma once
#include "bullet.h"
#include "node.h"
class enemy {
public:
	enemy() {};
	enemy(int xpos, int ypos, bool gActiveNodes[]);
	void move(SDL_Rect* a, node nodes[], SDL_Rect ship [], bullet bullets[100]);
	void render(int frame);
	bool checkCollision(SDL_Rect* a, int dmg);
	bool getVisible();
	bool getAlive();
	double getmoveAngle();
	bool checkVisible(bool lightOn, int angle);
	SDL_Point getCenter();
	void setNewTargetNode(bool gActiveNodes[]);
	double * getVel();
	int getHealth();
	void fire(bullet bullets[100]);
	SDL_Point createTargetPoint(node nodes[]);
private:
	bool activeNodes[6];
	int possibleTargets[6];
	int frame = 0;
	int stage = -2; //-3 is moving to orbit radius, -2 is moving to center, 0 is moving to point, 1 is orbiting point, -1 is orbiting ship
	int eSpd = 3;
	double pi = 3.141592;
	SDL_Point targetPoint;
	double nodeAngle;
	double moveAngle;
	bool clockwise = true;
	int health;
	bool readyToFire = false;
	int healthIncrements;
	double distance;
	int targetNode;
	double enemyAngle;
	int alive = true;
	SDL_Rect enemyClips[4];
	SDL_Rect healthClips[5];
	SDL_Rect explosionClips[7];
	double ePosX, ePosY;
	double eVelX, eVelY;
	bool visible = false;
	SDL_Rect eCollider;
	int largeOrbitRadius = 600;
	int orbitRadius = 175 + rand() % 50;
	int reloadSpd = 350 + rand()%100;
	int firingSpd = 100;
	int firingProgress = 0;
	int reloadProgress = 0;
	bool firing = false;
	int fired = false;
};