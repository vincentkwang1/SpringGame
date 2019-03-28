#include "enemy.h"
#include "bullet.h"
#include "node.h"
#include <time.h>
enemy::enemy(int xpos, int ypos, bool gActiveNodes[]) {
	ePosX = xpos;
	ePosY = ypos;
	eCollider.x = ePosX;
	eCollider.y = ePosY;
	eCollider.w = 104;
	eCollider.h = 100;
	health = 25;
	healthIncrements = health / 5;
	setNewTargetNode(gActiveNodes);
	for (int i = 0; i < 4; i++) {
		enemyClips[i].x = 0;
		enemyClips[i].y = 4 + 108 * i;
		enemyClips[i].w = 104;
		enemyClips[i].h = 100;
	}
	for (int i = 0; i < 7; i++) {
		explosionClips[i].x = 0;
		explosionClips[i].y = 196 * i;
		explosionClips[i].w = 196;
		explosionClips[i].h = 196;
	}
	for (int i = 0; i < 6; i++) {
		healthClips[i].x = 0;
		healthClips[i].y = 10 * i;
		healthClips[i].w = 87;
		healthClips[i].h = 10;
	}
}
void enemy::setNewTargetNode(bool gActiveNodes[]) {
	//reset
	stage = -3;
	firingProgress = 0;
	reloadProgress = 0;
	firing = false;
	fired = false;

	int counter = 0;
	for (int i = 0; i < 7; i++) {
		if (gActiveNodes[i] == true) {
			activeNodes[i] = true;
			counter++;
		}
		else {
			activeNodes[i] = false;
		}
	}
	srand(time(0));
	if (counter != 0) {
		int nthNode = rand() % counter;
		targetNode = 0;
		int x = 0;
		if (nthNode > 0) {
			while (nthNode > 0) {
				if (activeNodes[x] == true) {
					nthNode--;
					x++;
				}
				else {
					x++;
				}
			}
			targetNode = x - 1;
		}
		else {
			for (int i = 0; i < 6; i++) {
				if (activeNodes[i] == true) {
					targetNode = i;
				}
			}
		}
	}
	else {
		targetNode = 0;
	}
}
int enemy::getHealth() {
	SDL_Rect* currentClip;
	if (health <= 0 || health > 50) {
		if (frame < 80) {
			frame++;
		}
		currentClip = &explosionClips[frame / 10];
		alive = false;
		gExplosionTexture.render(ePosX, ePosY, currentClip);
	}
	return health;
}
SDL_Point enemy::getCenter() {
	SDL_Point a = { ePosX + eCollider.w/2, ePosY + eCollider.h/2 };
	return a;
}
bool enemy::checkVisible(bool lightOn, int angle) {
	//w is therefore (ePosX + eCollider.w - 955, ePosY + eCollider.h - 529)
	visible = true;//light center: 955, 529, enemy center: ePosX + eCollider.w, ePosY + eCollider.h
	enemyAngle = 180*atan2(ePosY + eCollider.h/2 - 520, ePosX + eCollider.w/2 - 955)/3.141592;//from -3.141592 to 3.141592
	if (enemyAngle <= 0) {
		enemyAngle = -enemyAngle;
	}
	else if(enemyAngle < 180 && enemyAngle > 0) {
		enemyAngle = 360 - enemyAngle;
	}
	if (angle >= 90 && angle < 270) {
		if (enemyAngle > (angle + 90) || enemyAngle < (angle - 90)) {
			visible = false;
		}
	}
	else if (angle < 90) {
		if (enemyAngle > (angle + 90) && enemyAngle < (angle + 270)) {
			visible = false;
		}
	}
	else if (angle >= 270) {
		if (enemyAngle > (angle -270) && enemyAngle < (angle - 90)) {
			visible = false;
		}
	}
	if (lightOn == false) {
		visible = false;
	}
	return visible;
}
bool enemy::getVisible() {
	return visible;
}
SDL_Point enemy::createTargetPoint(node nodes[]) {
	if (nodes[targetNode].getHealth() == 0) {
		for (int i = 0; i < 6; i++) {
			if (nodes[i].getHealth() > 0) {
				activeNodes[i] = true;
			}
			else {
				activeNodes[i] = false;
			}
		}
		setNewTargetNode(activeNodes);
	}
	targetPoint = nodes[targetNode].getPoint();
	targetPoint = { targetPoint.x + 50, targetPoint.y + 50 };
	//overrides the target point if stage -1 or -2
	if (stage == -1 || stage == -2 || stage == -3) {
		targetPoint = { 955, 529 };
	}
	//calculates distance to the target point
	distance = sqrt(pow(targetPoint.x - ePosX - eCollider.w / 2, 2) + pow(targetPoint.y - ePosY - eCollider.h / 2, 2));
	
	/*SDL_Color textColor = { 255, 0 ,0 };
	std::ostringstream strs;
	strs << targetNode;
	std::string str = strs.str();
	gTextTexture.loadFromRenderedText(str, textColor);
	gTextTexture.render(ePosX, ePosY);*/
	
	//if no longer orbiting
	if (stage != -1 && stage != -2 && stage != -3) {
		if (distance >= orbitRadius) {
			stage = 0;
		}
		else if (distance < orbitRadius) {
			stage = 1;
		}
	}
	//if moving to center
	if(stage == -2) {
		if (distance >= largeOrbitRadius) {
			stage = -2;
		}
		else if (distance < largeOrbitRadius) {
			stage = -1;
		}
	}
	if (stage == -3) {
		targetPoint = { 955, 529 }; 
		distance = sqrt(pow(targetPoint.x - ePosX - eCollider.w / 2, 2) + pow(targetPoint.y - ePosY - eCollider.h / 2, 2));
		if (distance <= largeOrbitRadius) {
			stage = -3;
		}
		else if (distance > largeOrbitRadius) {
			stage = -2;
		}
	}
	if (stage == -1) {
		switch (targetNode) {
			case 0:
				if (nodeAngle + 1 > 300 && nodeAngle - 1 < 300) {
					stage = 0;
				}break;
			case 1:
				if (nodeAngle + 1 > 270 && nodeAngle - 1 < 270) {
					stage = 0;
				}break;
			case 2:
				if (nodeAngle + 1 > 235 && nodeAngle - 1 < 235) {
					stage = 0;
				}break;
			case 3:
				if (nodeAngle + 1 > 45 && nodeAngle - 1 < 45) {
					stage = 0;
				}break;
			case 4: 
				if (nodeAngle + 1 > 90 && nodeAngle - 1 < 90) {
					stage = 0;
				}
				break;
			case 5:
				if (nodeAngle + 1 > 135 && nodeAngle - 1 < 135) {
					stage = 0;
				}break;
			case 6:
				if (nodeAngle + 1 > 90 && nodeAngle - 1 < 90) {
					stage = 0;
				}break;
		}
	}
	return targetPoint;
}
double enemy::getmoveAngle() {
	return moveAngle;
}
double * enemy::getVel() {
	double vel[2];
	vel[0] = eVelX;
	vel[1] = eVelY;
	return vel;
}
void enemy::fire(bullet bullets[100]) {
	if (fired == false) {
		int bulletnumber = 0;
		int intNodeAngle = 450-nodeAngle;
		if (intNodeAngle > 360) {
			intNodeAngle = intNodeAngle - 360;
		}
		SDL_Point origin = { ePosX + 35, ePosY + 35 };
		do {
			bulletnumber++;
		} while (bullets[bulletnumber].getAlive() == true);
		bullets[bulletnumber] = { &origin, intNodeAngle, 3 };
		fired = true;
	}
}
void enemy::move(SDL_Rect* a, node nodes[], SDL_Rect ship [], bullet bullets[100]) {
	//check if bullets hit enemy
	for (int i = 0; i < 100; i++) {
		if (bullets[i].getAlive() == true && bullets[i].getType() != 3) {
			if (checkCollision(&bullets[i].getCollider(), bullets[i].getDamage()) == true) {
				bullets[i].setAlive(false);
			}
		}
	}
	//sets the target point and the coords to move to
	createTargetPoint(nodes);
	//calculated angle based on the target point
	//calculates angle from enemy to targetPoint
	moveAngle = -180 * atan2(ePosY + eCollider.h / 2 - targetPoint.y, ePosX + eCollider.w / 2 - targetPoint.x) / 3.141592;
	moveAngle = 180 + moveAngle;
	nodeAngle = moveAngle;
	if (stage == -3) {
		moveAngle = 180 + moveAngle;
	}
	/*SDL_Color textColor = { 255, 0 , 255 };
	std::ostringstream strs;
	strs << nodeAngle;
	std::string str = strs.str();
	gTextTexture.loadFromRenderedText(str, textColor);
	gTextTexture.render(ePosX, ePosY + 40);*/

	if (stage == -1) {
		moveAngle = moveAngle - 90;
	}
	if (stage == 1) {
		if (checkCollision(&ship[0], 0) == true) {
			clockwise = !clockwise;
		}
		else if (checkCollision(&ship[1], 0) == true) {
			clockwise = !clockwise;
		}
		if (clockwise == true) {
			moveAngle = moveAngle - 90;
		}
		else {
			moveAngle = moveAngle + 90;
		}
	}
	if (stage == -1) {
		eVelX = 2 * eSpd * cos(moveAngle * pi / 180);//.627
	}
	else {
		eVelX = eSpd * cos(moveAngle * pi / 180);//.627
	}
	eVelY = -eSpd * sin(moveAngle * pi / 180);//.777
	if (stage == 0) {
		if (checkCollision(&ship[0], 0) == true) {
			eVelX = -1;
			eVelY = -eVelY;
		}
		else if (checkCollision(&ship[1], 0) == true) {
			eVelX = -1;
			eVelY = -eVelY;
		}
	}
	if (firing == true) {
		eVelX = 0;
		eVelY = 0;
		if (firingProgress == firingSpd/2) {
			fire(bullets);
		}
	}
	ePosX += eVelX;
	ePosY += eVelY;
	eCollider.x = ePosX;
	eCollider.y = ePosY;
	if (stage < 0) {
		readyToFire = false;
	}
	if (stage == 1) {
		readyToFire = true;
	}
	if (readyToFire == true) {
		if (reloadProgress < reloadSpd) {//reloading
			reloadProgress++;
			firing = false;
		}
		else {
			firing = true;
		}
		if (firing == true) {
			if (firingProgress < firingSpd) {//firing
				firingProgress++;
				firing = true;
			}
			else {
				reloadProgress = 0;
				firing = false;
				firingProgress = 0;
				fired = false;
			}
		}
	}
}
void enemy::render(int frame) {
	SDL_Rect* currentClip;
	SDL_Rect* currentClip2;
	//if health is greater than 0, draw enemy
	if (health > 0) {
		currentClip = &enemyClips[frame / 10];
		if (visible == false) {
			gEnemyTexture.setAlpha(100);
		}
		else {
			gEnemyTexture.setAlpha(255);
		}
		gEnemyTexture.render(ePosX, ePosY, currentClip);
	}
	//draw the health bar
	if (health > 0) {
		if (health / healthIncrements >= 0 && health / healthIncrements < 6) {
			currentClip2 = &healthClips[(health) / (healthIncrements)];
			gHealthBarTexture.render(ePosX, ePosY, currentClip2);
		}
	}
	/*SDL_Color textColor = { 255, 0 ,0 };
	std::ostringstream strs;
	strs << nodeAngle;
	std::string str = strs.str();
	gTextTexture.loadFromRenderedText(str, textColor);
	gTextTexture.render(ePosX, ePosY);*/
}
bool enemy::getAlive() {
	return alive;
}
bool enemy::checkCollision(SDL_Rect* a, int dmg) {
	int leftB, rightB, topB, bottomB;
	int leftA = eCollider.x;
	int rightA = ePosX + eCollider.w;
	int topA = eCollider.y;
	int bottomA = eCollider.y + eCollider.h;
	leftB = a->x;
	rightB = a->x + a->w;
	topB = a->y;
	bottomB = a->y + a->h;
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
	health = health - dmg;
	return true;
}