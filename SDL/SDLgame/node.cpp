#include "node.h"
#include "global.h"
const static int SCREEN_WIDTH = 1920;
const static int SCREEN_HEIGHT = 1080;
node::node() {
	nPosX = 500;
	nPosY = 500;
	nCollider.x = 500;
	nCollider.y = 500;
	nCollider.h = 100;
	nCollider.w = 100; 
	alive = true;
	for (int i = 0; i < 6; i++) {
		nodeClips[i].x = 0;
		nodeClips[i].y = 10 * i;
		nodeClips[i].w = 87;
		nodeClips[i].h = 10;
	}
	for (int i = 0; i < 7; i++) {
		explosionClips[i].x = 0;
		explosionClips[i].y = 196 * i;
		explosionClips[i].w = 196;
		explosionClips[i].h = 196;
	}
	for (int i = 0; i < 6; i++) {
		shieldClips[i].x = 0;
		shieldClips[i].y = 48 * i;
		shieldClips[i].w = 72;
		shieldClips[i].h = 48;
	}
}
void node::setAngle(int nDirection) {
	direction = nDirection;
}
int node::getHealth() {
	return health;
}
void node::updatePosition(int nodeType) {
	type = nodeType;
	if (type == 1) {
		reloadSpd = 5;
	}
	else if (type == 2) {
		reloadSpd = 20;
	}
	if (type != 0) {
		switch (pPosition) {
		case 1: angle = -45; break;
		case 2: angle = 0;  break;
		case 3: angle = 45; break;
		case 4: angle = 235; break;
		case 5: angle = 180; break;
		case 6: angle = 135; break;
		case 7: angle = 235; break;
		}
	}
}
void node::setPosition(int position, int nodeType) {
	pPosition = position;
	switch (position) {
		//621, 367
	case 1: angle = -45;  type = nodeType; nPosX = 621 + 66; nPosY = 367+10; break;//draw in top left
	case 2: angle = 0;    type = nodeType; nPosX = 621 + 420; nPosY = 37 + 367; break;//draw in top mid
	case 3: angle = 45;   type = nodeType; nPosX = 621 + 577; nPosY = 367+48; break;//draw in top right
	case 4: angle = 235;  type = nodeType; nPosX = 621 + 66; nPosY = 367+235; break;//draw in bot left
	case 5: angle = 180;  type = nodeType; nPosX = 621+420; nPosY = 367+207; break;//draw in bot mid
	case 6: angle = 135;  type = nodeType; nPosX = 621 + 577; nPosY = 367+195; break;//draw in bot right
	case 7: angle = 235; type = nodeType; nPosX = 895; nPosY = 469; nCollider.w = 120; nCollider.h = 120; break; //draw in light
	}
	if (type == 1) {
		reloadSpd = 5;
	}
	else if (type == 2) {
		reloadSpd = 20;
	}
	nCollider.x = nPosX; nCollider.y = nPosY;
}
void node::setAngle(bool eVisible[], SDL_Point eCenter[]) {
	if (closest != 42 && eVisible[closest] == true) {
		firing = true;
		int targetAngle, currentAngle;
		targetAngle = findAngle(&eCenter[closest]);
		currentAngle = getAngle();
		int counterclockdif, clockdif;
		if (currentAngle - targetAngle > 0) {
			counterclockdif = currentAngle - targetAngle;
		}
		else {
			counterclockdif = currentAngle + 360 - targetAngle;
		}
		if (targetAngle - currentAngle > 0) {
			clockdif = targetAngle - currentAngle;
		}
		else {
			clockdif = targetAngle + 360 - currentAngle;
		}
		if (clockdif + 2 < counterclockdif) {
			setAngle(1);
		}
		else if (counterclockdif  + 2< clockdif) {
			setAngle(2);
		}
		else {
			setAngle(0);
		}
	}
	else {
		setAngle(0);
		firing = false;
	}
}
bool node::checkVisible(SDL_Point eCenter[], bool eVisible[], bool eAlive[]) {
	//checks if there are any valid targets
	for (int i = 0; i <= 19; i++) {//cycles through all enemies
		if (eVisible[i] == true && eAlive[i] == true) {//checks if enemy is visible
			if (findAngle(&eCenter[i]) > 0 && findAngle(&eCenter[i]) < 180) {
				return true;
			}
		}
	}
	return false;
}
int node::getClosest(bool eAlive[], bool eVisible[], SDL_Point eCenter[]){
	double closestD = 2000;
	closest = 42;
	for (int b = 0; b <= 19; b++) {
		if (eAlive[b] == true) {
			double c = findDistance(&eCenter[b]);
			if (c < closestD) {
				closestD = c;
				switch (pPosition) {
				}
				closest = b;
			}
		}
	}
	return closest;
}
void node::move(bullet bullets[], bool eAlive[], bool eVisible[], SDL_Point eCenter[]) {
	if (alive == true) {
		for (int i = 0; i < 100; i++) {
			if (bullets[i].getAlive() == true && bullets[i].getType() == 3) {
				if (checkCollision(&bullets[i].getCollider(), bullets[i].getDamage()) == true) {
					bullets[i].setAlive(false);
				}
			}
		}
		if (occupied == true) {
			getReloading();
			getClosest(eAlive, eVisible, eCenter);
			setAngle(eVisible, eCenter);
			if (firing == true && reloading == false) {
				fire(bullets);
			}
		}
		if (type == 1 || type == 2) {
			if (occupied == true) {
				if (direction == 0) {
					rotVel = 0;
				}
				else if (direction == 1) {
					rotVel = 2;
				}
				else if (direction == 2) {
					rotVel = -2;
				}
				angle = angle + rotVel;
			}
		}
		if (type == 3) {
			if (occupied == true) {
				angle = angle + rotVel;
				if (angle < 0) {
					angle = angle + 360;
				}
				else if (angle > 360) {
					angle = angle - 360;
				}
				if (beamAlpha > 0) {
					beamAlpha = beamAlpha - 5;
				}
			}
			else {
				if (beamAlpha < 255) {
					beamAlpha = beamAlpha + 5;
				}
			}
		}
	}
	else {
		firing = false;
		reloading = true;
	}
}
bool node::getReloading() {
	if (firing == true) {
		if (reloadProgress == reloadSpd) {
			reloadProgress = 0;
			reloading = false;
		}
		else {
			reloadProgress++;
			reloading = true;
		}
	}
	return reloading;
}
bool node::getOccupied() {
	return occupied;
}
bool node::handleEvent(SDL_Event &e) {
	if (pPosition == 7) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_q: rotVel = rotVel - rotSpd; return true; break;
			case SDLK_e: rotVel = rotVel + rotSpd; return true; break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_q: rotVel = rotVel + rotSpd; return true; break;
			case SDLK_e: rotVel = rotVel - rotSpd; return true; break;
			}
		}
	}
	return false;
}
void node::setOccupied(bool newOccupied, bool switching) {
	occupied = newOccupied;
	if (type == 3 || type == 4) {
		firing = false;
	}

}
void node::render(int selectedCrew) {
	if (frame < 59) {
		frame++;
	}
	else {
		frame = 0;
	}
	SDL_Rect* currentClip;
	currentClip = &shieldClips[frame / 10];
	/*if (pPosition == selected) {
		gSelectedTexture.render(nPosX - 5, nPosY - 5);
	}
	else {*/
		if (pPosition != 7) {
			rotVel = 0;
		}
	//}
	SDL_Point center = { 20, 66 };
	if (type == 0) {
		gNodeTexture.render(nPosX, nPosY);
		gEmptyNodeTexture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
	}
	else if (type == 1) {
		gNodeTexture.render(nPosX, nPosY);
		gTurretTexture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
		if (health <= 0) {
			gTurretOffTexture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
		}
	}
	else if (type ==2){
		gNodeTexture.render(nPosX, nPosY);
		gTurret2Texture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
		if (health <= 0) {
			gTurret2OffTexture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
		}
	}
	else if (type == 3) {
		if (occupied == true) {
			gLightTexture.render(890, 479, NULL, angle);// , &center);
		}
		else {
			gLightOutTexture.render(890, 479, NULL, angle);
		}
		//}
	}
	else if (type == 4) {
		//72, 48. 100, 100
		gNodeTexture.render(nPosX, nPosY);
		gShieldNodeTexture.render(nPosX + 14, nPosY + 26, currentClip, angle);
	}
	/*if (pPosition == 1) {
		SDL_Color textColor = { 255, 0 ,0 };
		std::ostringstream strs;
		strs << closest << ", " << targetAngle;
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(100, 100);
	}*/
}
void node::renderHealth() {
	SDL_Rect* currentClip1;
	SDL_Rect* currentClip2;
	if ((health) / (healthIncrements) >= 0 && (health) / (healthIncrements) < 6) {
		currentClip1 = &nodeClips[(health) / (healthIncrements)];
		gHealthBarTexture.render(nPosX + 5, nPosY, currentClip1);
	}
	if (health <= 0) {
		if (explosionFrame < 80) {
			explosionFrame++;
		}
		currentClip2 = &explosionClips[explosionFrame / 10];
		alive = false;
		gExplosionTexture.render(nPosX, nPosY, currentClip2);
	}
}
int node::getType() {
	return type;
}
void node::renderBeam() {
	SDL_Point center1 = { 1250, 1282 };
	gBeamTexture.setAlpha(255);
	gDarkTexture.setAlpha(beamAlpha);
	gBeamTexture.render(-300, -750, NULL, angle + 90, &center1);
	gDarkTexture.render(-300, -750, NULL, angle + 90, &center1);
}
double node::findDistance(SDL_Point* center) {
	double distance; 
	SDL_Point nCenter = { nPosX + 50, nPosY + 50 };
	double x, y;
	y = (double)(-center->y + nCenter.y);
	x = (double)(center->x - nCenter.x);	
	distance = sqrt(x*x+y*y);
	return distance;
}
double node::findAngle(SDL_Point* center) {
	targetAngle = 0;
	SDL_Point nCenter = { nPosX + 50, nPosY + 50 };
	double x, y;
	y = (double)(-center->y + nCenter.y);
	x = (double)(center->x - nCenter.x);
	double offset = y/x;
	targetAngle = atan(offset) * 180 / (3.14159265);
	if (x>0 && y<0){
		targetAngle = 90 - targetAngle;
	}
	else if (x > 0 && y > 0) {
		targetAngle = 90 - targetAngle;
	}
	else if (x < 0 && y>0) {
		targetAngle = -targetAngle + 270;
	}
	else if (x < 0 && y < 0) {
		targetAngle = -targetAngle + 270;
	}
	return targetAngle;
}
int node::getAngle() {
	if (angle <= 0) {
		angle = angle + 360;
	}
	int angle1 = angle % 360;
	return angle1;
}
SDL_Rect node::getCollider() {
	return nCollider;
}
SDL_Point node::getPoint() {
	int x = nPosX + 44;
	int y = nPosY + 40;
	SDL_Point point = { x,y };
	return point;
}
bool node::checkCollision(SDL_Rect* a, int dmg) {
	int leftB, rightB, topB, bottomB;
	int leftA = nCollider.x;
	int rightA = nPosX + nCollider.w;
	int topA = nCollider.y;
	int bottomA = nCollider.y + nCollider.h;
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
void node::fire(bullet bullets[]) {
	bulletnumber = 0;
	do {
		bulletnumber++;
	} while (bullets[bulletnumber].getAlive() == true);
	//Creates a bullet with nPosX, angle of gun, type
	bullets[bulletnumber] = { &getPoint(), getAngle(), getType() };
}