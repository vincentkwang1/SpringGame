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
	gHills.loadFromFile("resource/hills.png");
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

	//Robert Testing
	int building[10] = { 1,0,0,0,0,0,0,0,0,0 };
	tile tiles[number];
	for (int x = 0; x < tileX; x++) {
		for (int y = 0; y < tileY; y++) {
			tiles[tileY * x + y] = { 1,1,true,true, x ,y ,1,building }; //8, 9
		}
	}
	//hill tiles
	tile hillTile[tileX*4];
	for (int side = 0; side < 4; side++) {
		for (int i = 0; i < tileX; i++) {
			hillTile[side * tileX + i] = { side, i };
		}
	}
	troop troop = { 0, 0, 1, tiles };
	///////////////

	std::vector<int> heightArray;
	heightArray = perlin.createArray();

	int test[9] = {1,2,3,4,5,6,7,8,9};
	map map = { 3, 3, test, test };
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
				case SDLK_0: troop.attack(); break; //MAKES TROOP ATTACK WHEN A IS PRESSED, FOR TESTING PURPOSES
				case SDLK_w:
					if (troop.getPos()[0] > 0) {
						troop.moveTroop(tiles, 0);
					}
					break;
				case SDLK_a: if (troop.getPos()[1] > 0)troop.moveTroop(tiles, 1); break; //MVOES THE TROOP
				case SDLK_s: if (troop.getPos()[0] < tileX)troop.moveTroop(tiles, 2); break; //MVOES THE TROOP
				case SDLK_d: if (troop.getPos()[1] < tileY)troop.moveTroop(tiles, 3); break; //MVOES THE TROOP
				}
			}
		}
		SDL_RenderClear(gRenderer);
		//GAME THINGS HAPPENING, PUT ALL GAME THINGS HERE

		//Robert Testing////
		for (int i = tileX  * 4 - 1; i >= 0; i--) {
			hillTile[i].handleEvent(e);
			hillTile[i].move();
			hillTile[i].render();
		}
		for (int i = 0; i < number; i++) {
			tiles[i].handleEvent(e);
			tiles[i].move();
			tiles[i].render();
		}
		///////////////////

		//gTestTexture.render(0, 0);
		troop.handleEvent(e);
		troop.move();
		troop.render();


		std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << "Hello World";
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(100, 100);

		//GAME THINGS HAPPENING END
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}