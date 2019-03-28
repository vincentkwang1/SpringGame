#ifndef ship_h_
#include "ship.h"
#include <SDL.h>
#include "global.h"
#define ship_h_

ship::ship() {
	pPosX = -1+(1920 - ship_width) / 2;//677, 345
	pPosY = -3+(1080 - ship_height) / 2;
	pVelX = 0;
	pVelY = 0;
	sCollider[0].x = pPosX + 103 + 20;
	sCollider[0].y = pPosY + 40 + 40;
	sCollider[0].w = 180 - 40;
	sCollider[0].h = 264 - 80;

	sCollider[1].x = sCollider[0].x + sCollider[0].w;
	sCollider[1].y = pPosY + 60 + 40;
	sCollider[1].w = 385 - 40;
	sCollider[1].h = 224 - 80;

	nodeTypes[0] = 1;
	nodeTypes[1] = 0;
	nodeTypes[2] = 0;
	nodeTypes[3] = 0;
	nodeTypes[4] = 0;
	nodeTypes[5] = 0;
	nodeTypes[6] = 3;
}
void ship::reward(int type, int which, node nodes[]) {
	int i = -1;
	if (type == 1) {

	}
	else if (type == 2) {
		do {
			i++;
		} 
		while (nodeTypes[i] != 0);
		setNodePositions(i, which, nodes);
	}
}
void ship::setNodePositions(int nodeLoc, int newNodeType, node nodes[]) {
	nodeTypes[nodeLoc] = newNodeType;
	nodes[nodeLoc].updatePosition(getNodeTypes()[nodeLoc]);
}
int * ship::getNodeTypes() {
	return nodeTypes;
}
void ship::render() {
	gShipTexture.render(pPosX, pPosY);
}
SDL_Rect * ship::getSCollider() {
	return sCollider;
}
#endif // !ship_h_