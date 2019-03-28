#pragma once
#ifndef ship_h_
#define ship_h_
#include "node.h"
#include <SDL.h>
class ship {
public:
	static const int ship_height = 345;
	static const int ship_width = 677;
	ship();
	void reward(int type, int which, node nodes[]);
	//type:
	//1 = money
	//2 = weapon. which: 1 = fast boi, 2 = slow boi
	void render();
	void setNodePositions(int nodeLoc, int newNodeType, node nodes[]);
	SDL_Rect * getSCollider();
	int * getNodeTypes();
private:
	int nodeTypes[7] = { 0,0,0,0,0,0,0 };
	int pPosX, pPosY;
	SDL_Rect sCollider[2];
	int pVelX, pVelY;
	int angle = 0;
	int rotVel = 0;
};
#endif // !ship_h_

