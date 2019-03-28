#include "bullet.h"
bullet::bullet(SDL_Point* point, int angle, int type) {
	alive = true;
	bulletType = type;
	bCollider.w = 6;
	bCollider.h = 15;
	pAngle = angle;
	bVelX = 25 * cos((-90 + angle)*3.14159265 / 180.0);
	bVelY = 25 * sin((-90 + angle)*3.14159265 / 180.0);
	if (bulletType == 2) {
		dmg = 5;
		bVelX = bVelX / 2;
		bVelY = bVelY / 2;
		for (int i = 0; i < 4; i++) {
			bulletClips[i].x = 0;
			bulletClips[i].y = 30 * i;
			bulletClips[i].w = 30;
			bulletClips[i].h = 30;
		}
	}
	else if (bulletType == 3) {
		dmg = 1;
		bVelX = bVelX / 10;
		bVelY = bVelY / 10;
		for (int i = 0; i < 4; i++) {
			bulletClips[i].x = 0;
			bulletClips[i].y = 30 * i;
			bulletClips[i].w = 30;
			bulletClips[i].h = 30;
		}
	}
	else if (bulletType == 1) {
		dmg = 1;
		for (int i = 0; i < 5; i++) {
			bulletClips[i].x = 0;
			bulletClips[i].y = 30 * i;
			bulletClips[i].w = 12;
			bulletClips[i].h = 30;
		}
	}
	bPosX = point->x;
	bPosY = point->y;
	bCollider.x = bPosX;
	bCollider.y = bPosY;
}
void bullet::move(SDL_Rect ship [])
{
	checkShipCollision(&ship[0]);
	checkShipCollision(&ship[1]);
	bPosX += bVelX;
	bPosY += bVelY;
	bCollider.x = bPosX;
	bCollider.y = bPosY;
}
bool bullet::getAlive() {
	return alive;
}
void bullet::setAlive(bool newAlive) {
	alive = newAlive;
}
int bullet::getDamage() {
	return dmg;
}
bool bullet::checkShipCollision(SDL_Rect* ship) {
	if (checkCollision(&bCollider, ship) == true) {
		return true;
	}
	else {
		return false;
	}
}
int bullet::getType() {
	return bulletType;
}
void bullet::render(int frame) {
	SDL_Rect* currentClip;
	if (bulletType == 1) {
		currentClip = &bulletClips[(frame / 2) % 5];
		gBulletTexture.render(bPosX, bPosY, currentClip, pAngle);
	}
	else if (bulletType == 2) {
		currentClip = &bulletClips[(frame / 2) % 4];
		gBullet2Texture.render(bPosX, bPosY, currentClip, pAngle);
	}
	else if (bulletType == 3) {
		currentClip = &bulletClips[(frame / 2) % 4];
		gBullet3Texture.render(bPosX, bPosY, currentClip, pAngle);
	}
}
SDL_Rect bullet::getCollider() {
	return bCollider;
}
bool bullet::checkCollision(SDL_Rect* a, SDL_Rect* b) {
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
	if (bPosX < 0 || bPosX > 1920 || bPosY < 0 || bPosY > 1920) {
		alive = false;
		return false;
	}
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
	alive = false;
	return true;
}