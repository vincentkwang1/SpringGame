#include "LTexture.h"
#include "global.h"
#include "troop.h"
#include "tile.h"
#include "ppm.h"
#include "Perlin.h"
#include "map.h"
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//METHODS: init, close, loadMedia
bool init();
void close();
void loadMedia();
bool checkClicked(SDL_Rect a, SDL_Event* e);

//METHODS DEFINED

bool init() {
	//DON'T CHANGE, STARTS ALL NECESSARY SDL THINGS AND CREATES THE WINDOW
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags) & imgFlags;
	TTF_Init();
	return success;
}
void loadMedia() {
	//LOADS ALL TEXTURES FROM THE RESOURCE FOLDER
	gFont = TTF_OpenFont("resource/font1.ttf", 40);
	gSwordsmanTexture.loadFromFile("resource/sword.png");
	gGrassTexture.loadFromFile("resource/grass.png");
	gWaterTexture.loadFromFile("resource/TempTiles/water.png");
	gHillTexture.loadFromFile("resource/TempTiles/hill.png");
	gMountainRockTexture.loadFromFile("resource/TempTiles/mountain1.png");
	gHills.loadFromFile("resource/hills.png");
	gEnemyTexture.loadFromFile("resource/enemy.png");
	gHighlightTexture.loadFromFile("resource/highlight.png");
}
void close() {
	//DON'T CHANGE, CLOSES ALL SURFACES AND CLOSES THE PROGRAM
	gTextTexture.free();
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
bool checkClicked(SDL_Rect a, SDL_Event* e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x < a.x) {
		return false;
	}
	else if (x > a.x + a.w) {
		return false;
	}
	else if (y < a.y) {
		return false;
	}
	else if (y > a.y + a.h) {
		return false;
	}
	else {
		return true;
	}
}
void drawTileLayer(map gameMap, tile * tiles, int layer) {
	for (int i = gameMap.getHeight() - 1; i >= 0; i--)
	{
		for (int j = 0; j < gameMap.getWidth(); j++) {
			tiles[i * tileX + j].render(layer);
		}
	}
}
//MAIN FUNCTION
int main(int argc, char* args[]) {

	init();
	loadMedia();
	bool quit = false;
	SDL_Event e;
	srand(time(NULL));

	//CONSTRUCTING CLASSES
	Perlin perlin; //taken from https://github.com/sol-prog/Perlin_Noise

	//MAKE MAP////////////////////////////
	static const int mapWidth = tileX;
	static const int mapHeight = tileY;
	std::vector<int> heightArray = perlin.createArray(); //array containing the randomized heights
	map gameMap = { mapWidth, mapHeight, heightArray, heightArray }; //2D vector containing the tiles
	static const int number = mapWidth * mapHeight;
	tile tiles[number];
	for (int i = 0; i < gameMap.getHeight(); i++)
	{
		for (int j = 0; j < gameMap.getWidth(); j++) {
			tiles[mapHeight*i + j] = gameMap.getMapContainer()[i][j];
		}
	}
	//hill tiles
	tile hillTile[tileX*4];
	for (int side = 0; side < 4; side++) {
		for (int i = 0; i < tileX; i++) {
			hillTile[side * tileX + i] = { side, i };
		}
	}
	///////////////
	//keep track of turns
	int turn = 0;
	//Generate Armies//
	troop troop1 = { 0, 0, 1, tiles , true };
	//Generatres enemies
	troop enemy = { 5, 5, 1, tiles , false };
	//keeps track of selected tile
	int selectedX = 0;
	int selectedY = 0;

	
	
	//GAME MAIN LOOP
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				//ALLOWS QUITTING
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				//HANDLES KEYPRESSES
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: quit = true; break;
				case SDLK_0: troop1.attack(); turn++; break; //MAKES TROOP ATTACK WHEN A IS PRESSED, FOR TESTING PURPOSES

				//Handles Moving troops in the four cardinal directions based on keypress////////////////////////////////
				case SDLK_w: if (troop1.getPos()[0] > 0) { if(troop1.moveTroop(tiles, 0)) turn++; } break;
				case SDLK_a: if (troop1.getPos()[1] > 0) { if(troop1.moveTroop(tiles, 1)) turn++; }break;
				case SDLK_s: if (troop1.getPos()[0] < mapWidth - 1) { if(troop1.moveTroop(tiles, 2)) turn++; }break;
				case SDLK_d: if (troop1.getPos()[1] < mapHeight - 1) { if(troop1.moveTroop(tiles, 3)) turn++; }break;
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {//FOR MOUSE
				for (int x = 0; x < tileX; x++) {
					for (int y = 0; y < tileY; y++) {
						if (checkClicked(tiles[tileY * x + y].getCollider(), &e)) {
							tiles[tileY * x + y].setHighlight(true);
							selectedX = x;
							selectedY = y;
							for (int i = 0; i < (tileY * x + y); i++) {
								tiles[i].setHighlight(false);
							}
							for (int i = (tileY * x + y + 1); i < tileX * tileY; i++) {
								tiles[i].setHighlight(false);
							}
						}
					}
				}
			}
		}
		SDL_RenderClear(gRenderer);
		//GAME THINGS HAPPENING, PUT ALL GAME THINGS HERE
		for (int i = tileX * 3; i < tileX * 4; i++) {
			hillTile[i].handleEvent(e);
			hillTile[i].move();
			hillTile[i].render(false);
		}
		for (int i = tileX - 1; i >= 0; i--) {
			hillTile[i].handleEvent(e);
			hillTile[i].move();
			hillTile[i].render(false);
		}
		for (int i = tileX * 2 - 1; i >= tileX; i--) {
			hillTile[i].handleEvent(e);
			hillTile[i].move();
			hillTile[i].render(false);
		}
		for (int i = tileX * 2; i < tileX * 3; i++) {
			hillTile[i].handleEvent(e);
			hillTile[i].move();
			hillTile[i].render(false);
		}
		for (int i = 0; i < gameMap.getHeight(); i++)
		{
			for (int j = 0; j < gameMap.getWidth(); j++) {

				tiles[i * mapHeight + j].handleEvent(e);
				tiles[i * mapHeight + j].move();
				tiles[i * mapHeight + j].render(0);
			}
		}
		drawTileLayer(gameMap, tiles, 2);
		drawTileLayer(gameMap, tiles, 0);
		drawTileLayer(gameMap, tiles, 1);
		drawTileLayer(gameMap, tiles, 3);
		drawTileLayer(gameMap, tiles, 4);
		//*/
		//gTestTexture.render(0, 0);
		troop1.handleEvent(e);
		troop1.move();
		troop1.render();

		enemy.handleEvent(e);
		enemy.move();
		enemy.render();


		std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << turn << ", sel: " << selectedX << ", " << selectedY;
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(100, 100);

		//GAME THINGS HAPPENING END
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}