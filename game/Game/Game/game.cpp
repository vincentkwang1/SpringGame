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
	gWaterTexture.loadFromFile("resource/water.png");
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
	Perlin perlin;

	//MAKE MAP////////////////////////////
	int mapWidth = 12, mapHeight = 12;
	std::vector<int> heightArray = perlin.createArray(); //array containing the randomized heights
	map gameMap = { mapWidth, mapHeight, heightArray, heightArray }; //2D vector containing the tiles
	//////////////////////////////////////


	//Generate Armies//
	troop troop = { 0, 0, 1, gameMap.getMapContainer() };
	

	
	
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


				//Handles Moving troops in the four cardinal directions based on keypress////////////////////////////////
				case SDLK_w: if (troop.getPos()[0] > 0)troop.moveTroop(gameMap.getMapContainer(), 0); break;
				case SDLK_a: if (troop.getPos()[1] > 0)troop.moveTroop(gameMap.getMapContainer(), 1); break; 
				case SDLK_s: if (troop.getPos()[0] < mapWidth- 1)troop.moveTroop(gameMap.getMapContainer(), 2); break; 
				case SDLK_d: if (troop.getPos()[1] < mapHeight - 1)troop.moveTroop(gameMap.getMapContainer(), 3); break; 
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			}
		}
		SDL_RenderClear(gRenderer);
		//GAME THINGS HAPPENING, PUT ALL GAME THINGS HERE

		/*//Vinny Testing////
		for (int i = 0; i < number; i++) {
			tile[i].handleEvent(e);
			tile[i].move();
			tile[i].render();
		}
		///////////////////*/
		for (int i = 0; i < gameMap.getHeight(); i++)
		{
			for (int j = 0; j < gameMap.getWidth(); j++) {
				
				gameMap.getMapContainer()[i][j].handleEvent(e);
				gameMap.getMapContainer()[i][j].move();
				gameMap.getMapContainer()[i][j].render();
			}
		}
		//*/
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