#include "LTexture.h"
#include "global.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//METHODS: init, load_image, close, loadSurface
bool init();
void close();
bool loadMedia();

//METHODS DEFINED
bool init() {
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	//gWindow = SDL_CreateWindow("Vincent's Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDO_FULLSCREEN);
	gWindow = SDL_CreateWindow("Vincent's Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags) & imgFlags;
	TTF_Init();
	return success;
}
bool loadMedia() {
	bool success = true;
	return success;
}
void close() {
	//gTextTexture.free();
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
	bool selectingDesination = false;
	SDL_Event e;
	ship ship;
	background background;
	srand(time(NULL));
	int which = rand() % 12 + 1;
	background.loadMedia(which);
	int bulletnumber;
	int frame = 0;
	int spawnerFrame = 0;
	bullet bullets[100];
	enemy enemies[20];
	int maxEnemyNumber;
	level level;
	level.skipTutorial(0, 0);
	//level.skipTutorial(8, 11);
	node nodes[7];
	int queuePos = 0;
	const int crewSize = 3;
	int selectedCrew = 1;
	int selected[crewSize] = { 1,7,3 };
	crew crew[crewSize];
	for (int i = 1; i <= crewSize; i++) {
		crew[i - 1] = { 800 + 50 * i, 500 , i, i };
	}
	for (int i = 1; i <= 7; i++) {
		nodes[i - 1].setPosition(i, ship.getNodeTypes()[i - 1]);
	}
	//GAME MAIN LOOP
	while (!quit) {
		//ALLOWS QUITTING
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			int tempNode;
			if (e.type == SDL_KEYDOWN) {//FOR CHOOSING CREWMEMBERS
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: quit = true; break;
				case SDLK_SPACE: pause = !pause;
					if (level.getCheckPoint() == 1) {
						level.setCheckPoint(level.getCheckPoint() + 1);
					}
					break;
				case SDLK_f:
					if (crew[selectedCrew - 1].getSitting() == true) {
						tempNode = nodes[crew[selectedCrew - 1].getNode() - 1].getType();
						if (tempNode != 0 && tempNode != 3) {
							ship.setNodePositions(crew[selectedCrew - 1].getNode() - 1, 0, nodes);
							crew[selectedCrew - 1].setCarryingNode(true, tempNode);
						}
					}
					break;
					//nodes[crew[selectedCrew - 1].checkOccupied() + 1].getType())
				case SDLK_TAB:
					if (selectedCrew < crewSize) {
						selectedCrew++;
					}
					else {
						selectedCrew = 1;
					}
					if (level.getCheckPoint() == 3) {
						level.setCheckPoint(level.getCheckPoint() + 1);
					}
				case SDLK_F1:
					if (selectedCrew < crewSize) {
						selectedCrew++;
					}
					else {
						selectedCrew = 1;
					}
					break;
				case SDLK_F2: selectedCrew = 2;
					break;
				case SDLK_F3:
					if (crewSize >= 3) {
						selectedCrew = 3;
					}
					if (level.getCheckPoint() == 3) {
						level.setCheckPoint(level.getCheckPoint() + 1);
					}
					break;
				case SDLK_F4:
					if (crewSize >= 4) {
						selectedCrew = 4;
					}
					break;
				}
			}
			if (e.type == SDL_KEYDOWN) {//FOR CHOOSING WHERE THE CREWMEMBERS SHOULD GO
				switch (e.key.keysym.sym) {
				case SDLK_1:
					selected[selectedCrew - 1] = 1; break;
				case SDLK_2:
					if (level.getCheckPoint() == 5) {
						level.setCheckPoint(6);
					}selected[selectedCrew - 1] = 2; break;
				case SDLK_3:selected[selectedCrew - 1] = 3; break;
				case SDLK_4:selected[selectedCrew - 1] = 4; break;
				case SDLK_5:selected[selectedCrew - 1] = 5; break;
				case SDLK_6:selected[selectedCrew - 1] = 6; break;
				case SDLK_l:selected[selectedCrew - 1] = 7; break;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {//FOR MOUSE
				if (checkClicked(nodes[0].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 1;
				}
				else if (checkClicked(nodes[1].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 2;
					if (level.getCheckPoint() == 5) {
						level.setCheckPoint(6);
					}selected[selectedCrew - 1] = 2;
				}
				else if (checkClicked(nodes[2].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 3;
				}
				else if (checkClicked(nodes[3].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 4;
				}
				else if (checkClicked(nodes[4].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 5;
				}
				else if (checkClicked(nodes[5].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 6;
				}
				else if (checkClicked(nodes[6].getCollider(), &e) == true) {
					selected[selectedCrew - 1] = 7;
				}
			}
			if (nodes[6].handleEvent(e) == true) {
				if (level.getCheckPoint() == 7) {
					level.setCheckPoint(8);
				}
			}
			level.handleEvent(e);
			/*for (int i = 1; i <= 6; i++) {
				  nodes[i-1].handleEvent(e, selected);
			  }*/
		}
		//GAME THINGS HAPPENING
		SDL_RenderClear(gRenderer);
		background.render();
		level.render(spawnerFrame);
		SDL_Color textColor = { 255, 255 , 255 };
		//DRAWS ENEMIES, LIGHT, SHIP
		for (int i = 0; i <= 19; i++) {
			if (enemies[i].getAlive() == true) {
				enemies[i].render(spawnerFrame);
			}
			enemies[i].getHealth();
		}
		//DRAWS BULLETS
		nodes[6].renderBeam();
		ship.render();
		for (int i = 0; i < 100; i++) {
			if (bullets[i].getAlive() == true) {
				bullets[i].render(spawnerFrame);
			}
		}
		//IF NODES ARE FIRING AND NOT RELOADING, CREATES A NEW BULLET, THEN DRAWS NODES
		for (int i = 1; i <= 7; i++) {
			nodes[i - 1].render(selectedCrew);
		}
		//DRAW CREW
		for (int i = 1; i <= crewSize; i++) {
			crew[i - 1].render(frame, selectedCrew, nodes[crew[i - 1].getNode() - 1].getPoint(), nodes[crew[i - 1].getNode() - 1].getAngle(), nodes[crew[i - 1].getNode() - 1].getType());
		}
		for (int i = 1; i <= 7; i++) {
			nodes[i - 1].renderHealth();
		}
		if (level.getLevelNumber() == 0 || level.getLevelNumber() == 2) {
			level.loadMessages(ship, nodes);
			if (level.checkPauseGame() == true) {
				pause = true;
			}
		}
		////REMOVE THIS
		//std::ostringstream strs;
		//strs << level.getCheckPoint();
		//std::string str = strs.str();
		//gTextTexture.loadFromRenderedText(str, textColor);
		//gTextTexture.render(100, 100);
		//FOLLOWING ARE EVENTS THAT STOP WHEN GAME IS PAUSED, i.e MOVE THE BACKGROUND, MOVE THE CREWMEMBER, MOVE THE SHIP, etc.
		if (pause == false) {
			//****************
			//WHERE LEVELS ARE CREATED
			level.createLevel(enemies, nodes);
			//END OF LEVEL CREATING
			//****************
			for (int i = 0; i < 100; i++) {
				bullets[i].move(ship.getSCollider());
			}
			if (frame < 79) {
				frame++;
			}
			else {
				frame = 0;
			}
			if (spawnerFrame < 39) {
				spawnerFrame++;
			}
			else {
				spawnerFrame = 0;
			}
			//MOVES ALL ENEMIES
			for (int i = 0; i <= 19; i++) {
				if (enemies[i].getAlive() == true) {
					enemies[i].move(ship.getSCollider(), nodes, ship.getSCollider(), bullets);
					enemies[i].checkVisible(nodes[6].getOccupied(), 360 - nodes[6].getAngle());
				}
			}
			//MOVES BACKGROUND AND SHIP
			//UPDATES THE QUEUE FOR THE CREWMEMBERS, AND MOVES CREW TO THE NEXT QUEUE POINT
			for (int i = 1; i <= crewSize; i++) {
				if (nodes[selected[i - 1] - 1].getOccupied() == false) {
					if (crew[i - 1].move(selected[i - 1], ship, nodes) == true) {
						if (level.getCheckPoint() == 9) {
							level.setCheckPoint(10);
						}
					}
				}
			}
			//MOVES NODES
			for (int i = 1; i <= 7; i++) {
				//void move(bullet bullets[], bool eAlive[], bool eVisible[], SDL_Point* eCenter[]);
				bool eAlive[20];
				bool eVisible[20];
				SDL_Point eCenter[20];
				for (int a = 0; a < 20; a++) {
					eAlive[a] = enemies[a].getAlive();
					eVisible[a] = enemies[a].getVisible();
					eCenter[a] = enemies[a].getCenter();
				}
				nodes[i - 1].move(bullets, eAlive, eVisible, eCenter);
			}
			for (int i = 0; i <= 6; i++) {
				nodes[i].setOccupied(false, false);
			}
			//CHECKS WHICH NODES ARE OCCUPPIED BY CREW
			for (int i = 1; i <= crewSize; i++) {
				if (crew[i - 1].getSwitching() == false) {
					switch (crew[i - 1].checkOccupied()) {
					case 1: nodes[0].setOccupied(true, false); break;
					case 2: nodes[1].setOccupied(true, false); break;
					case 3: nodes[2].setOccupied(true, false); break;
					case 4: nodes[3].setOccupied(true, false); break;
					case 5: nodes[4].setOccupied(true, false); break;
					case 6: nodes[5].setOccupied(true, false); break;
					case 7: nodes[6].setOccupied(true, false); break;
					}
				}
				else {
					switch (crew[i - 1].checkOccupied()) {
					case 1: nodes[0].setOccupied(true, true); break;
					case 2: nodes[1].setOccupied(true, true); break;
					case 3: nodes[2].setOccupied(true, true); break;
					case 4: nodes[3].setOccupied(true, true); break;
					case 5: nodes[4].setOccupied(true, true); break;
					case 6: nodes[5].setOccupied(true, true); break;
					case 7: nodes[6].setOccupied(true, true); break;
					}
				}
			}
		}
		else {
			gTextTexture.loadFromRenderedText("Paused!", textColor);
			gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT)-200);
		}
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}