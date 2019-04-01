#include "LTexture.h"
#include "global.h"
#include "troop.h"
#include "tile.h"
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
	gTestTexture.loadFromFile("resource/2.png");
	gSwordsmanTexture.loadFromFile("resource/sword.png");
	gTile.loadFromFile("resource/Tile.jpg");
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

	troop troop = {500, 500, 1};

	//Robert Testing
	int building[10] = { 1,0,0,0,0,0,0,0,0,0 };
	tile tile = {1,1,true,true,1000,700,1,building};
	///////////////

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
				case SDLK_a: troop.attack(); break; //MAKES TROOP ATTACK WHEN A IS PRESSED, FOR TESTING PURPOSES
				}
			}
		}
		SDL_RenderClear(gRenderer);
		//GAME THINGS HAPPENING, PUT ALL GAME THINGS HERE

		//gTestTexture.render(0, 0);
		troop.render();

		//Robert Testing////
		tile.render();
		///////////////////

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