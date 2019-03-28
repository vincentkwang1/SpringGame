#pragma once
#include "global.h"
#include "ship.h"
class crew {
public:
	crew() {};
	crew(int xPos, int yPos, int gcrewNumber, int pNodeDestination);
	bool move(int selected, ship ship, node nodes[]);
	void render(int frame, int crewSelected, SDL_Point nPos, int angle, int type);
	int checkOccupied();
	int getNode();
	bool getSitting();
	bool getSwitching();
	void setCarryingNode(bool gCarryingNode, int gCarriedNodeType);
	bool checkCollision(SDL_Rect* a, SDL_Rect* b);
private:
	int cSpd = 5;
	bool carryingNode = false;
	int carriedNodeType = 0;
	SDL_Rect cCollider;
	SDL_Rect sCollider1;
	SDL_Rect sCollider;
	SDL_Point nodePositions [7];
	int nodeDestination = -1;//-1 means no destination set
	int crewNumber;
	int direction = 0; //0 is right, 1 is down, 2 is left, 3 is up
	int frameDir = 0;
	int currentNode = 0;//8 means not moving
	bool moving = true;
	bool placing = false;
	bool sitting = false;
	bool switching = false;
	SDL_Rect gCrewClips[16];
	int cPosX, cPosY;
	int carriedNPosX, carriedNPosY;
	int cVelX;
	int cVelY;
};
