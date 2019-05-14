#include "LTexture.h"
#include "global.h"
#include "troop.h"
#include "tile.h"
#include "ppm.h"
#include "Perlin.h"
#include "map.h"
#include "gui.h"
#include "structure.h"
#include "button.h"
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
	IMG_Init(imgFlags)& imgFlags;
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
	gTreeTexture.loadFromFile("resource/tree.png");
	gHighlightTexture.loadFromFile("resource/highlight.png");
	gCastleTexture.loadFromFile("resource/castle.png");
	gButtonTexture.loadFromFile("resource/buttons.png");
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
bool checkCircleClicked(int radius, int cx, int cy, SDL_Event* e) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	int dx = cx - x;
	int dy = cy - y;
	int distance = sqrt(dx * dx + dy * dy);
	if (distance < radius) {
		return true;
	}
	else {
		return false;
	}
}
void drawTileLayer(map currentMap, tile* tiles, int layer) {
	for (int i = currentMap.getHeight() - 1; i >= 0; i--)
	{
		for (int j = 0; j < currentMap.getWidth(); j++) {
			tiles[i * tileX + j].render(layer);
		}
	}
}
std::vector<map> initMap(std::vector<map> localMaps) {
	localMaps.resize(worldWidth * worldHeight);
	return localMaps;
}
std::vector<map> createMap(std::vector<map> localMaps, std::vector<int> heightArray, int localXCoord, int localYCoord) {
	map localMap = { tileX, tileY, heightArray, heightArray, false, localXCoord, localYCoord };
	localMaps.at(localXCoord * worldWidth + localYCoord) = localMap;
	return localMaps;
}




//void Generate();


//MAIN FUNCTION
int main(int argc, char* args[]) {

	//Basic setup DO NOT CHANGE////
	init();
	loadMedia();
	bool quit = false;
	SDL_Event e;
	button turnButton = {};
	SDL_Rect buttonBox = {1761, 940, 159, 159};
	srand(time(NULL));
	//////////////////
	gui tileGui; //creates the box that describes tiles
	//CONSTRUCTING CLASSES
	Perlin perlin; //[1]
	map worldMap = { worldWidth,worldHeight,perlin.createArray(worldWidth,worldHeight,5, 2),perlin.createArray(worldWidth,worldHeight,5, 2),true,0,0 };//creates world map with perlin noise arrays for temperature and noise
	//Placeholder for local map/////

	//MAKE WORLD MAP////////////////////////////
	//same as local map
	std::vector<int> worldArray = perlin.createArray(worldWidth, worldHeight, 5, 2); //array containing the randomized heights

	int turnCounter = 0;

	//keeps track of current local map
	int currentMapX = 20;
	int currentMapY = 20;

	//MAKE LOCAL MAP////////////////////////////
	std::vector<int> heightArray = perlin.createArray(tileX, tileY, 10, worldMap.getTileType(currentMapX, currentMapY)); //array containing the randomized heights
	std::vector<map> localMaps;
	localMaps.resize(worldWidth * worldHeight);
	localMaps = initMap(localMaps);
	localMaps = createMap(localMaps, heightArray, currentMapX, currentMapY);

	//creates first tiles
	static const int number = tileX * tileY;
	tile tiles[number];
	for (int i = 0; i < localMaps[currentMapX * worldWidth + currentMapY].getHeight(); i++)
	{
		for (int j = 0; j < localMaps[currentMapX * worldWidth + currentMapY].getWidth(); j++) {
			tiles[tileY * i + j] = localMaps[currentMapX * worldWidth + currentMapY].getMapContainer()[i][j];
		}
	}
	//hill tiles
	tile hillTile[tileX * 4];
	for (int side = 0; side < 4; side++) {
		for (int i = 0; i < tileX; i++) {
			hillTile[side * tileX + i] = { side, i };
		}
	}
	//create fort
	structure castle;

	std::vector<troop> alliedArmy; //Creates the array storing the data on the player army and puts a place hoder at the beginning
	std::vector<troop> enemyArmy;  //Creates the array storing the data on the enemy army and puts a troop on the board 

	//Generate Armies//
	//alliedArmy = localMaps[currentMapX * worldWidth + currentMapY].createTroop(tiles, 1, 1, true);

	//Generatres enemies
	enemyArmy = localMaps[currentMapX * worldWidth + currentMapY].createTroop(tiles, 1, 1, false);

	//keeps track of selected troop
	int selectedTroop = 0;
	bool selectingTroop = false; //helps separate clicking alliedArmy from clicking tiles

	//alliedArmy[0].setSelected(true); //makes the first troop selected by default

	//keeps track of selected tile
	int selectedX = 0;
	int selectedY = 0;

	//keeps track of selected world tile
	int selectedWorldX = 0;
	int selectedWorldY = 0;

	//keeps track of whether to show world map or not, toggled with 'tab'
	bool showWorldMap = false;

	//int test = 0;

	//GAME MAIN LOOP
	while (!quit) {
		alliedArmy = localMaps[currentMapX * worldWidth + currentMapY].getTroops(true);
		enemyArmy = localMaps[currentMapX * worldWidth + currentMapY].getTroops(false);
		//HANDLES EVENTS
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				//ALLOWS QUITTING
			}
			if (e.type == SDL_KEYDOWN) {
				//HANDLES KEYPRESSES
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: quit = true; break;
				case SDLK_0: alliedArmy[selectedTroop].attack(); break; //MAKES TROOP ATTACK WHEN A IS PRESSED, FOR TESTING PURPOSES
				case SDLK_1: alliedArmy = localMaps[currentMapX * worldWidth + currentMapY].createTroop(tiles, 2, 2, true); break; //CREATES NEW TROOP
				case SDLK_2: enemyArmy = localMaps[currentMapX * worldWidth + currentMapY].createTroop(tiles, 2, 2, false); break; //CREATES NEW TROOP
				case SDLK_TAB: if (e.key.repeat == 0) showWorldMap = !showWorldMap; break;
				}
				//if a button is pressed, check if the troops are done
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {//FOR MOUSE
				//handles clicking the next turn button
				if (checkClicked(buttonBox, &e)) {
					if (turnButton.getType() == 0) {
						turnCounter++;
						turnButton.setType(1);
						for (int i = 0; i < alliedArmy.size(); i++) {
							for (int i = 0; i < localMaps.size(); i++) {
								//goes through all maps and checks if they've been loaded
								if (localMaps[i].getLoaded()) {
									//checks if there are any allied troops
									if (localMaps[i].getTroops(true).size() != 1) {
										for (int a = 0; a < alliedArmy.size(); a++) {
											alliedArmy[a].reset();
										}
									}
								}
							}
						}
					}
				}
				else {
					//handles clicking troops
					for (int x = 0; x < alliedArmy.size(); x++) {
						if (checkClicked(alliedArmy[x].getCollider(), &e)) {
							alliedArmy[selectedTroop].setSelected(false); //resets the old selected troop
							selectedTroop = x;
							selectingTroop = true;
							alliedArmy[x].setSelected(true); //selected the new selected troop
						}
					}
					//handles clicking world map tiles
					if (showWorldMap) {
						for (int i = 0; i < 4; i++) {
							int x, y;
							switch (i) {
							case 0: x = currentMapX; y = currentMapY - 1; break;
							case 1: x = currentMapX; y = currentMapY + 1; break;
							case 2: x = currentMapX - 1; y = currentMapY; break;
							case 3: x = currentMapX + 1; y = currentMapY; break;
							}
							SDL_Rect worldTile = { 620 + x * mapPixelWidth / worldWidth, 200 + y * mapPixelWidth / worldWidth, mapPixelWidth / worldWidth, mapPixelWidth / worldHeight };
							//checks if clicked one of the 4 cardinal directions from current tile
							if (checkClicked(worldTile, &e)) {
								//figures out which tile was clicked
								selectedWorldX = x;
								selectedWorldY = y;
								//changes the map that is shown	
								currentMapX = selectedWorldX;
								currentMapY = selectedWorldY;
								//sets the armies to the armies of the new map
								alliedArmy = localMaps[currentMapX * worldWidth + currentMapY].getTroops(true);
								enemyArmy = localMaps[currentMapX * worldWidth + currentMapY].getTroops(false);
								//if not yet loaded, creates a new perlin array for the map according to the type of tile
								if (!localMaps[currentMapX * worldWidth + currentMapY].getLoaded()) {
									localMaps = createMap(localMaps, perlin.createArray(tileX, tileY, 10, worldMap.getTileType(currentMapX, currentMapY)), x, y);
								}
								//sets the current tiles to the newly selected one, whether a new array or not
								for (int i = 0; i < localMaps[currentMapX * worldWidth + currentMapY].getHeight(); i++)
								{
									for (int j = 0; j < localMaps[currentMapX * worldWidth + currentMapY].getWidth(); j++) {
										tiles[tileY * i + j] = localMaps[currentMapX * worldWidth + currentMapY].getMapContainer()[i][j];
									}
								}
								for (int side = 0; side < 4; side++) {
									for (int i = 0; i < tileX; i++) {
										hillTile[side * tileX + i].setPosition();
									}
								}
							}
						}
					}
					else if (!selectingTroop) {
						//handles clicking local map tiles
						for (int x = 0; x < tileX; x++) {
							for (int y = 0; y < tileY; y++) {
								if (checkCircleClicked(56, tiles[tileY * x + y].getCollider().x + 120, tiles[tileY * x + y].getCollider().y + 60, &e)) {
									tiles[selectedX * tileY + selectedY].setHighlight(0);
									tiles[tileY * x + y].setHighlight(1);

									selectedX = x;
									selectedY = y;
									int selected = selectedX * tileY + selectedY;
									if (alliedArmy[selectedTroop].getPos()[0] < selectedX) {
										if (alliedArmy[selectedTroop].moveTroop(tiles, 2)) {
											selectedTroop = 0;
										}
									}
									else if (alliedArmy[selectedTroop].getPos()[1] < selectedY) {
										if (alliedArmy[selectedTroop].moveTroop(tiles, 3)) {
											selectedTroop = 0;
										}
									}
									else if (alliedArmy[selectedTroop].getPos()[0] > selectedX) {
										if (alliedArmy[selectedTroop].moveTroop(tiles, 0)) {
											selectedTroop = 0;
										}
									}
									else if (alliedArmy[selectedTroop].getPos()[1] > selectedY) {
										if (alliedArmy[selectedTroop].moveTroop(tiles, 1)) {
											selectedTroop = 0;
										}
									}
								}

							}
						}
					}
					selectingTroop = false;

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
		for (int i = 0; i < localMaps[currentMapX * worldWidth + currentMapY].getHeight(); i++)
		{
			for (int j = 0; j < localMaps[currentMapX * worldWidth + currentMapY].getWidth(); j++) {

				tiles[i * tileY + j].handleEvent(e);
				tiles[i * tileY + j].move();
				tiles[i * tileY + j].setHighlight(0);
				if (selectedTroop < alliedArmy.size()) {
					if (!alliedArmy[selectedTroop].getPlaceholder()) {
						tiles[i * tileY + j].checkDist(alliedArmy[selectedTroop].getPos()[1], alliedArmy[selectedTroop].getPos()[0]);
					}
				}
				tiles[i * tileY + j].render(0);
			}
		}
		drawTileLayer(localMaps.at(currentMapX * worldWidth + currentMapY), tiles, 2);
		drawTileLayer(localMaps.at(currentMapX * worldWidth + currentMapY), tiles, 0);
		drawTileLayer(localMaps.at(currentMapX * worldWidth + currentMapY), tiles, 1);
		drawTileLayer(localMaps.at(currentMapX * worldWidth + currentMapY), tiles, 3);
		drawTileLayer(localMaps.at(currentMapX * worldWidth + currentMapY), tiles, 4);
		drawTileLayer(localMaps.at(currentMapX * worldWidth + currentMapY), tiles, 5);
		//*/
		//gTestTexture.render(0, 0);
		for (int i = 0; i < alliedArmy.size(); i++) {
			alliedArmy[i].handleEvent(e);
			alliedArmy[i].move();
			alliedArmy[i].render();
		}
		for (int i = 0; i < enemyArmy.size(); i++) {
			enemyArmy[i].handleEvent(e);
			enemyArmy[i].move();
			enemyArmy[i].render();
		}

		gHighlightTexture.colorMod(255, 255, 255);
		gHighlightTexture.render(tiles[selectedX * tileY + selectedY].getX(), tiles[selectedX * tileY + selectedY].getY());

		//draw world map if tab is pressed
		if (showWorldMap) {
			worldMap.render(currentMapX, currentMapY);
		}
		tileGui.renderTileInfo(tiles[selectedX * tileY + selectedY]);

		localMaps[currentMapX * worldWidth + currentMapY].setTroops(true, alliedArmy);
		localMaps[currentMapX * worldWidth + currentMapY].setTroops(false, enemyArmy);

		std::ostringstream strs;
		SDL_Color textColor = { 255, 255 , 255 };
		strs << "Turn " << turnCounter;
		std::string str = strs.str();
		gTextTexture.loadFromRenderedText(str, textColor);
		gTextTexture.render(100, 100);

		turnButton.check(localMaps);
		turnButton.render();
		//castle.render();

		//GAME THINGS HAPPENING END
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}

/*
[1] taken from https://github.com/sol-prog/Perlin_Noise
*/