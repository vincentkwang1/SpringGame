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
	gTile.loadFromFile("resource/Tile.png");
	gGrassTexture.loadFromFile("resource/grass.png");
	gWaterTexture.loadFromFile("resource/TempTiles/water.png");
	gHillTexture.loadFromFile("resource/TempTiles/hill.png");
	gMountainRockTexture.loadFromFile("resource/TempTiles/mountain1.png");
	gImpassableTexture.loadFromFile("resource/TempTiles/impassable.png");
	gHills.loadFromFile("resource/hills.png");
	gEnemyTexture.loadFromFile("resource/enemy.png");
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
		}
		SDL_RenderClear(gRenderer);
		//GAME THINGS HAPPENING, PUT ALL GAME THINGS HERE

		for (int i = tileX  * 4 - 1; i >= 0; i--) {
			hillTile[i].handleEvent(e);
			hillTile[i].move();
			hillTile[i].render(false);
		}
		for (int i = 0; i < gameMap.getHeight(); i++)
		{
			for (int j = 0; j < gameMap.getWidth(); j++) {

				tiles[i*mapHeight + j].handleEvent(e);
				tiles[i*mapHeight + j].move();
				tiles[i*mapHeight + j].render(false);
			}
		}
		for (int i = 0; i < gameMap.getHeight(); i++)
		{
			for (int j = 0; j < gameMap.getWidth(); j++) {
				tiles[i*mapHeight + j].render(true);
			}
		}
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
		strs << turn;
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(100, 100);

		//GAME THINGS HAPPENING END
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}