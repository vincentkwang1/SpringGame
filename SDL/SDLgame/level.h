#pragma once
#include "spawner.h"
#include "enemy.h"
#include "node.h"
#include "ship.h"
class level {
public:
	level();
	spawner spawner[2]; 
	void createLevel(enemy enemies[20], node nodes[]);
	void render(int spawnerFrame);
	void drawMessage(bool mini, int messageXPos, int messageYPos, int messageWidth);
	bool checkPauseGame();
	void pauseGame(bool pause);
	void setCheckPoint(int newCheckPoint);
	bool initSpawners();
	int getCheckPoint();
	void handleEvent(SDL_Event& e);
	void deleteSpawners();
	bool checkClicked(SDL_Rect a, SDL_Event* e);
	bool checkLevelCompletion(enemy enemies[20]);
	int getLevelNumber();
	void loadMessages(ship ship, node nodes[]);
	void skipTutorial(int gMessageNumber, int gTutorialCheckPoint);
	//void handleEvent(SDL_Event& e);
private:
	int response = 1;
	int responses = 0;
	int skip = 0;
	bool responseType = false;
	int numberOfMessages[3];
	int messageLengths[10];
	bool initSpawnersDone = false;
	int delay = 0;
	int tutorialCheckPoint = 0; //0 is hasn't yet reached first checkpoint
	//1 is reached text
	//1 is letting the user pause/unpause
	//2 is waiting
	//3 is reached text about crewmembers
	//3 is letting the user select crewmembers
	//4 is waiting
	//5 is reached the text about nodes
	//6 is reached text describing crew behavior
	//9 is waiting for user to do the 'f' thing
	//10-11 is prompting the user to start
	bool finishedWriting = false;
	int levelNumber = 0; //0 = tutorial
	int spawnNumber[2];
	bool pPause;
	bool showingText = true;
	int whichLetter = 0;
	int messageNumber = 0;
	char messagechars[500];
	int letterDelay = 3;
	std::string str = "";
	int letterCount = 3;
	int letterXPos = 550;
	int letterYPos = 300;
	SDL_Point spawnerPos[2];
	LTexture message;
	SDL_Color textColor = { 240, 240, 240 };
	int numberSpawned[2] = { 0, 0 };
	int spawnDelay[2] = { 100, 50 };
	bool done[2] = { false, false };
};