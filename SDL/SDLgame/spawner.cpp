#include "spawner.h"
#include "global.h"
#include "enemy.h"
spawner::spawner() {

}
spawner::spawner(int xPos, int yPos) {
	posX = xPos;
	posY = yPos;
	for (int i = 0; i < 8; i++) {
		spawnerClips[i].x = 0;
		spawnerClips[i].y = 306 * i;
		spawnerClips[i].w = 213;
		spawnerClips[i].h = 306;
	}
}
void spawner::render(int frame) {
	SDL_Rect* currentClip;
	currentClip = &spawnerClips[frame / 8];
	gSpawnerTexture.render(posX, posY, currentClip);
}
void spawner::spawnEnemy(enemy enemies[20], node nodes[]) {
	bool found = false;
	int num = 0;
	do{
		if (enemies[num].getAlive() == true) {
			num++;
		}
		else {
			found = true;
		}
	} while (found == false);
	livingEnemies = 0;
	for (int i = 0; i < 20; i++) {
		if (enemies[i].getAlive() == true) {
			livingEnemies++;
		}
	}
	for (int i = 0; i < 6; i++) {
		if (nodes[i].getHealth() > 0) {
			gActiveNodes[i] = true;
		}
		else {
			gActiveNodes[i] = false;
		}
	}
	if (livingEnemies != 20) {
		enemies[num] = { posX + 56, posY + 153 , gActiveNodes};
	}
}