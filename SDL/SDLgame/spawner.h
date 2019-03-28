#pragma once
#include "global.h"
#include "enemy.h"
#include "node.h"
class spawner {
public:
	spawner();
	spawner(int xPos, int yPos);
	void render(int frame);
	void spawnEnemy(enemy enemies[20], node nodes[]);
private:
	bool gActiveNodes[6];
	int livingEnemies = 0;
	int posX;
	int posY;
	SDL_Rect spawnerClips[8];
};
