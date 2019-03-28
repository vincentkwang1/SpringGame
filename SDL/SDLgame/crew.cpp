#include "crew.h"
#include "global.h"
//#include "tiles.h"
crew::crew(int xPos, int yPos, int gcrewNumber, int pNodeDestination) {
	crewNumber = gcrewNumber;
	for (int i = 0; i < 16; i++) {
		gCrewClips[i].x = 70 * i;
		gCrewClips[i].y = 0;
		gCrewClips[i].w = 70;
		gCrewClips[i].h = 64;
	}
	cCollider.x = cPosX;
	cCollider.y = cPosY;
	cCollider.w = 70;
	cCollider.h = 64;

	nodePositions[0] = { 687 + 60,387 + 60 };
	nodePositions[1] = { 621 + 420 + 30,367 + 37 + 60 + 20};
	nodePositions[2] = { 621 + 577,367 + 48 + 60};//1198, 475
	nodePositions[3] = { 621 + 66 + 60,367 + 235};
	nodePositions[4] = { 621 + 420 + 30 ,367 + 207 - 20};
	nodePositions[5] = { 621 + 577,367 + 195};
	nodePositions[6] = { 895 + 30, 469 + 30 };

	sCollider.x = 800;
	sCollider.y = 490;
	sCollider.w = 270;
	sCollider.h = 90;

	sCollider1.x = 1071;
	sCollider1.y = 490;
	sCollider1.w = 129;
	sCollider1.h = 90;

	cPosX = xPos;
	cPosY = yPos;
	cVelX = 0;
	cVelY = 0;
}
void crew::setCarryingNode(bool gCarryingNode, int gCarriedNodeType) {
	carryingNode = gCarryingNode;
	if (carryingNode == true) {
		cSpd = 5;
	}
	else {
		cSpd = 5;
	}
	carriedNodeType = gCarriedNodeType;
}
bool crew::move(int selected, ship ship, node nodes[]) {
	moving = true;
	SDL_Point coords;
	nodeDestination = selected;
	coords = nodePositions[nodeDestination - 1];//desired point//tiles[19 * (y2 - 1) + x2-1].getCoords();
	if (cPosX > sCollider.x && cPosX < sCollider.x + sCollider.w) {
		coords = { coords.x, 500 };
	}
	else if (cPosX > sCollider1.x && cPosX < sCollider1.x + sCollider1.w) {
		coords = { coords.x, 500 };
	}
	if (coords.x -2 > cPosX) {
		cVelX = cSpd;
	}
	else if (coords.x + 2< cPosX) {
		cVelX = -cSpd;
	}
	else {
		cVelX = 0;
	}
	if (coords.y - 2 > cPosY) {
		cVelY = cSpd;
	}
	else if (coords.y + 2 < cPosY) {
		cVelY = -cSpd;
	}
	else {
		cVelY = 0;
	}
	if (cVelX == 0 && cVelY == 0) {
		currentNode = nodeDestination;
		moving = false;
		//reached destination
		if(placing == true){
			if (carryingNode == true) {
				if (nodes[nodeDestination - 1].getType() == 0) {
					carryingNode = false;
					ship.setNodePositions(nodeDestination - 1, carriedNodeType, nodes);
					setCarryingNode(false, 0);
					//placed the node
					placing = false;
					return true;
				}
				else {
					switching = true;
					int tempNode = nodes[getNode() - 1].getType();
					ship.setNodePositions(nodeDestination - 1, carriedNodeType, nodes);
					setCarryingNode(true, tempNode);
					//switching
					/*int tempNode = carriedNodeType;
					setCarryingNode(true, nodes[nodeDestination - 1].getType());
					ship.setNodePositions(nodeDestination - 1, tempNode, nodes);
					nodeDestination = currentNode;
					moving = false;
					placing = false;
					sitting = true;*/
				}
			}
		}
	}
	if (carryingNode == false) {
		switching = false;
	}
	if (carryingNode == true) {
		if (moving == true) {
			placing = true;
		}
	}
	if (cVelY > 0) {
		direction = 1;
	}
	else if (cVelY < 0){
		direction = 3;
	}
	if (cVelX > 0) {
		direction = 0;
	}
	else if (cVelX < 0){
		direction = 2;
	}
	cPosX += cVelX;
	cPosY += cVelY;
	return false;
}
int crew::checkOccupied() {
	if (moving == true) {
		currentNode = 8;
		sitting = false;
	}
	else if (moving == false) {
		currentNode = nodeDestination;
		sitting = true;
	}
	return currentNode;
}
bool crew::getSitting() {
	return sitting;
}
bool crew::getSwitching() {
	return switching;
}
int crew::getNode() {
	return currentNode;
}
void crew::render(int frame, int crewSelected, SDL_Point nPos, int angle, int type) {
	SDL_Point center = { 25, 66 };
	if (sitting == false) {
		if (cVelX != 0 || cVelY != 0) {
			SDL_Rect* currentClip;
			switch (direction) {
			case 0: frameDir = 1; break;
			case 1: frameDir = 0; break;
			case 2: frameDir = 3; break;
			case 3: frameDir = 2; break;
			}
			currentClip = &gCrewClips[(4*frameDir) + frame / 20];
			if (crewSelected == crewNumber) {
				gCrewSelectedTexture.render(cPosX, cPosY, currentClip);
			}
			else {
				gCrewSpriteSheetTexture.render(cPosX, cPosY, currentClip);
			}
		}
	}
	else if(type!= 3){
		if (crewNumber == crewSelected) {
			gSittingSelectedTexture.render(nPos.x - 44 + 30 - 4, nPos.y - 40 - 12, NULL, angle, &center);
		}
		else {
			gSittingTexture.render(nPos.x - 44 + 30 - 4, nPos.y - 40 - 12, NULL, angle, &center);
		}
	}
	else if (type == 3) {
		if (crewNumber == crewSelected) {
			gLightSittingSelectedTexture.render(890, 479, NULL, angle);
		}
		else {
			gLightSittingTexture.render(890, 479, NULL, angle);
		}
	}
	if (carryingNode == true) {
		if (sitting == true) {
			carriedNPosX = cPosX + 10; 
			carriedNPosY = cPosY;
		}
		else {
			carriedNPosX = cPosX + 30; 
			carriedNPosY = cPosY - 10;
		}
		SDL_Point carriedCenter = {0, 40};
		if (carriedNodeType == 1) {
			gCarriedTurretTexture.render(carriedNPosX, carriedNPosY, NULL, direction * 90, &carriedCenter);//90 - direction*90);
		}
		else if (carriedNodeType == 2) {
			gCarriedTurret2Texture.render(carriedNPosX, carriedNPosY, NULL, direction * 90, &carriedCenter);
		}
		else if (carriedNodeType == 4) {
			gCarriedShieldTexture.render(carriedNPosX, carriedNPosY, NULL, direction * 90, &carriedCenter);
		}
	}
}
bool crew::checkCollision(SDL_Rect* a, SDL_Rect* b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;
	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}
	return true;
}