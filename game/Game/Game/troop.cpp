#include "troop.h"
troop::troop() {
	
}
troop::troop(int xPos, int yPos, int type) {
	tPosX = xPos;
	tPosY = yPos; 
	for (int i = 0; i < 20; i++) {
		troopClips[i].x = 94 * i;
		troopClips[i].y = 0;
		troopClips[i].w = 94;
		troopClips[i].h = 86;
	}
}
void troop::render() {
	SDL_Rect* currentClip [6];
	if (attacking) { //if attacking is true, execute attack animation
		for (int i = 0; i < 6; i++) {
			currentClip[i] = &troopClips[(frame / 5 + i) % 20];
		}
		if ((frame / 5) % 20 == 19) { //stops attacking when last animation is done
			attacking = false;
		}
	}
	else { //otherwise, idle animation
		for (int i = 0; i < 6; i++) {
			currentClip[i] = &troopClips[9 + (frame / 10 + i * 2) % 4];
		}
	}
	gSwordsmanTexture.render(tPosX, tPosY, currentClip[0]);
	gSwordsmanTexture.render(tPosX + 40, tPosY, currentClip[1]);
	gSwordsmanTexture.render(tPosX - 10, tPosY + 30, currentClip[2]);
	gSwordsmanTexture.render(tPosX + 30, tPosY + 30, currentClip[3]);
	gSwordsmanTexture.render(tPosX + 50, tPosY + 60, currentClip[4]);
	gSwordsmanTexture.render(tPosX + 10, tPosY + 60, currentClip[5]);

	//UPDATING FRAME COUNTERS
	if (frame < 100) {
		frame++;
	}
	else {
		frame = 0;
	}
}
void troop::attack() {
	frame = 0; //resets frame counter when starting attack animation
	attacking = true;
}