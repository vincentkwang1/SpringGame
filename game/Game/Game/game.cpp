#include "LTexture.h"
#include "global.h"
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//METHODS: init, load_image, close, loadSurface
bool init();
void close();
void loadMedia();

//METHODS DEFINED
bool init() {
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("Vincent's Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags) & imgFlags;
	TTF_Init();
	return success;
}
void loadMedia() {
	gFont = TTF_OpenFont("resource/font1.ttf", 40);
	gTestTexture.loadFromFile("resource/2.png");
}
void close() {
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
	bool pause = false;
	SDL_Event e;
	srand(time(NULL));

	//GAME MAIN LOOP
	while (!quit) {
		//ALLOWS QUITTING
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {//HANDLES KEYPRESSES
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: quit = true; break;
				}
			}
		}
		//GAME THINGS HAPPENING
		SDL_RenderClear(gRenderer);
		gTestTexture.render(0, 0);
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