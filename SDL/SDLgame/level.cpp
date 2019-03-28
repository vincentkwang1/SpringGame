#include "level.h"
#include "global.h"
#include "node.h"
#include <time.h>
#include <string>
level::level(){
	gFont = TTF_OpenFont("resource/font1.ttf", 30);
	numberOfMessages[0] = 8;
	numberOfMessages[1] = 0;
	numberOfMessages[2] = 3;
}
void level::setCheckPoint(int newCheckPoint) {
	tutorialCheckPoint = newCheckPoint;
}
bool level::checkLevelCompletion(enemy enemies[20]) {
	int counter = 0;
	for (int i = 0; i < 20; i++) {
		if (enemies[i].getAlive() == false) {
			counter++;
		}
	}
	if (counter == 20) {
		return true;
	}
	else {
		return false;
	}
}
void level::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		if (messageNumber <= numberOfMessages[levelNumber]-1 && finishedWriting == false) {
			letterCount = 0;
			letterDelay = 0;
		}
		switch (e.key.keysym.sym) {
		case SDLK_SPACE:
			//when pressing space, resets everything and changes the messageNumber
			if (messageNumber <= numberOfMessages[levelNumber]-1 && responseType == false) {
				if (finishedWriting == true && showingText == true) {
					letterCount = 3;
					letterDelay = 3;
					strcpy_s(messagechars, " "); 
					whichLetter = 0;  
					str = ""; 
					if (skip > 0) {
						messageNumber = messageNumber + skip + 1;
					}
					else {
						messageNumber++;
					}
					break;
				}
				else {
					//if not done writing, speed it up
					letterCount = 0;
					letterDelay = 0;
				}
			}
			if(finishedWriting == true && messageNumber >= numberOfMessages[levelNumber] - 1){
				showingText = false;
			}
			break;
		case SDLK_1:
			if (responseType == true && 1 <= responses) {
				if (finishedWriting == true) {
					letterCount = 3;
					letterDelay = 3;
					strcpy_s(messagechars, " ");
					whichLetter = 0;
					str = "";
					if (skip > 0) {
						messageNumber = messageNumber + skip + 1;
					}
					else {
						messageNumber++;
					}
					break;
				}
				else {
					//if not done writing, speed it up
					letterCount = 0;
					letterDelay = 0;
				}
				response = 1;
				break;
			}break;
		case SDLK_2:
			if (responseType == true && 2 <= responses) {
				response = 2;
				if (finishedWriting == true) {
					letterCount = 3;
					letterDelay = 3;
					strcpy_s(messagechars, " ");
					whichLetter = 0;
					str = "";
					if (skip > 0) {
						messageNumber = messageNumber + skip + 1;
					}
					else {
						messageNumber = messageNumber + 2;
					}
					break;
				}
				else {
					//if not done writing, speed it up
					letterCount = 0;
					letterDelay = 0;
				} break;
			}break;
		case SDLK_3:
			if (responseType == true && 3 <= responses) {
				response = 3;
				if (finishedWriting == true) {
					letterCount = 3;
					letterDelay = 3;
					strcpy_s(messagechars, " ");
					whichLetter = 0;
					str = "";
					if (skip > 0) {
						messageNumber = messageNumber + skip + 1;
					}
					else {
						messageNumber = messageNumber + 3;
					}
					break;
				}
				else {
					//if not done writing, speed it up
					letterCount = 0;
					letterDelay = 0;
				}break;
			}break;
		case SDLK_F11:
			tutorialCheckPoint++;
			break;
	}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {//FOR MOUSE
		SDL_Rect buttonCollider = { 100, 100, 127, 62 };
		if (checkClicked(buttonCollider, &e) == true) {
			skipTutorial(8, 11);
		}
	}
}
bool level::checkClicked(SDL_Rect a, SDL_Event* e) {
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
void level::loadMessages(ship ship, node nodes[]) {
	if (levelNumber == 0) {
		char message1chars[306] = "(Press any key to speed up text crawl)\nWelcome to Vincent's game!\nYou are the captain of a spacecraft equipped with a massive bomb on a mission to destroy the alien mothership. You must use everything at your disposal to fight through hordes of aliens and succeed in your mission.\n\nPress space to continue";
		messageLengths[0] = 306 - 13;
		char message2chars[87] = "You are in control of 3 crewmembers, a light, and a weapon. \n\nPress space to continue";
		messageLengths[1] = 87;
		char message3chars[148] = "The game is paused. Press 'space' to pause and unpause. You can still command your crew while the game is paused.\n\nUnpause with 'space' to continue";
		messageLengths[2] = 148 - 13;
		char message4chars[220] = "You are controlling the highlighted crewmember. Crewmembers can be selected with 'f1', 'f2', etc., or cycled through with 'tab' \n\nUnpause with 'space' then try selecting another crewmember with 'f3' or 'tab' to continue";
		messageLengths[3] = 220 - 13;
		char message5chars[182] = "Click any of the unoccupied blue pods to move your selected crewmember, or press '1', '2', etc. \n\nUnpause with 'space', then move to the top middle pod by clicking it or pressing 2.";
		messageLengths[4] = 182 - 13;
		char message6chars[349] = "Your crew will automatically fire at nearby enemies if they are in a pod with a weapon. If the health bar of a pod goes to 0, your crew will no longer be able to use it. Your weapons will also only target enemies that the light is shining on. If the light is occupied, you can rotate it with 'q' or 'e'. \n\nUnpause, then press 'q' or 'e' to continue";
		messageLengths[5] = 349 - 13;
		char message7chars[211] = "In order to move weapons between pods, press 'f' to remove a weapon from the selected crewmember, then move to a new location to place it. You cannot move the light. \n\nUnpause, then move the weapon to continue.";
		messageLengths[6] = 211 - 13;
		char message8chars[197] = "The aliens are coming! Remember that you can only target enemies that are lit by your light. Pause if you need a moment to think and reposition your weapons. Good luck! \n\nPress 'space' to continue";
		messageLengths[7] = 197 - 13;
		switch (messageNumber + 1) {
		case 1: strcpy_s(messagechars, message1chars); drawMessage(false, 550, 300, 800); break;
		case 2: strcpy_s(messagechars, message2chars); drawMessage(false, 550, 300, 800); break;
		case 3: strcpy_s(messagechars, message3chars); drawMessage(true, 100, 500, 350); tutorialCheckPoint = 1; break;
		case 4:
			if (tutorialCheckPoint == 2) {
				if (delay < 100) {
					delay++;
				}
				else {
					delay = 0;
					tutorialCheckPoint++;
				}
			}
			if (tutorialCheckPoint == 3) {
				showingText = true;
				strcpy_s(messagechars, message4chars);
				drawMessage(true, 100, 500, 450);
			}
			else {
				pauseGame(false);
				showingText = false;
			}
			if (tutorialCheckPoint == 4) {
				messageNumber = 4;
				letterCount = 3;
				letterDelay = 3;
				strcpy_s(messagechars, " ");
				whichLetter = 0;
				str = "";
			}
			break;
		case 5:
			if (tutorialCheckPoint == 4) {
				if (delay < 20) {
					delay++;
				}
				else {
					delay = 0;
					tutorialCheckPoint++;
				}
			}
			if (tutorialCheckPoint == 5) {
				showingText = true;
				strcpy_s(messagechars, message5chars);
				drawMessage(true, 100, 500, 450);
			}
			else {
				pauseGame(false);
				showingText = false;
			}
			break;
		case 6:
			if (tutorialCheckPoint == 6) {
				if (delay < 50) {
					delay++;
				}
				else {
					delay = 0;
					tutorialCheckPoint++;
				}
			}
			if (tutorialCheckPoint == 7) {
				showingText = true;
				strcpy_s(messagechars, message6chars);
				drawMessage(false, 550, 300, 800);
			}
			else {
				pauseGame(false);
				showingText = false;
			}
			break;
		case 7:
			if (tutorialCheckPoint == 8) {
				if (delay < 50) {
					delay++;
				}
				else {
					delay = 0;
					tutorialCheckPoint++;
				}
			}
			if (tutorialCheckPoint == 9) {
				showingText = true;
				strcpy_s(messagechars, message7chars);
				drawMessage(true, 100, 500, 450);
			}
			else {
				pauseGame(false);
				showingText = false;
			}
			break;
		case 8:
			if (tutorialCheckPoint == 10) {
				if (delay < 20) {
					delay++;
				}
				else {
					delay = 0;
					tutorialCheckPoint++;
				}
			}
			if (tutorialCheckPoint == 11) {
				showingText = true;
				strcpy_s(messagechars, message8chars);
				drawMessage(false, 550, 300, 800);
			}
			else {
				pauseGame(false);
				showingText = false;
			}
			break;
		case 9: showingText = false; pauseGame(false);
			if (levelNumber == 0) {
				levelNumber = 1;
				initSpawnersDone = false;
			} break;
		}
	}
	//LEVEL TWO
	if (levelNumber == 2) {
		deleteSpawners();
		char message1chars[224] = "Congratulations!\nYou've pushed back the aliens for now. You find among the remnants of the aliens a strange intact weapon. It doesn't seem to be of human origin.\n\n1. Claim weapon for yourself (1 new weapon)\n\n2. Let it drift";		
		messageLengths[0] = 224 - 13;
		char message2chars[234] = "You bring the weapon on board and wash off the space debris. You install it into one of your pods, and give it a couple test fires. It seems to shoot slower than your standard weaponry, but deals more damage.\n\nPress space to continue";
		messageLengths[1] = 234 - 13;
		char message3chars[84] = "You choose to let the weapon continue to drift in space.\n\nPress space to continue";
		messageLengths[1] = 84 - 13;
		char message4chars[84] = "Your mission is to .\n\nPress space to continue";
		messageLengths[1] = 84 - 13;
		switch (messageNumber + 1) {
		case 1: strcpy_s(messagechars, message1chars); responses = 2; responseType = true; drawMessage(false, 550, 300, 800); break;
		case 2: ship.reward(2, 2, nodes); strcpy_s(messagechars, message2chars); responseType = false; skip = 1; drawMessage(false, 550, 300, 800); break;
		case 3: strcpy_s(messagechars, message3chars); responseType = false; skip = 0; drawMessage(false, 550, 300, 800); break;
		case 4: showingText = false; pauseGame(false);
			if (levelNumber == 2) {
				levelNumber = 3;
				initSpawnersDone = false;
			} break;
		}
	}
}
void level::skipTutorial(int gMessageNumber, int gTutorialCheckPoint) {
	letterCount = 3;
	letterDelay = 3;
	strcpy_s(messagechars, " ");
	whichLetter = 0;
	str = "";
	messageNumber = gMessageNumber;
	tutorialCheckPoint = gTutorialCheckPoint;
}
int level::getCheckPoint() {
	return tutorialCheckPoint;
}
void level::drawMessage(bool mini, int messageXPos, int messageYPos, int messageWidth) {
	if (levelNumber == 0) {
		if (messageNumber < 4) {
			gSkipButtonTexture.render(100, 100);
		}
	}
	if (showingText == true) {
		std::string s(1, messagechars[whichLetter]);
		if (letterCount == letterDelay) {
			letterCount = 0;
			whichLetter++;
			letterXPos = letterXPos + 10;
			//str is created by s
			str.append(s);
		}
		else {
			letterCount++;
		}
		if (whichLetter >= messageLengths[messageNumber]) {
			finishedWriting = true;
		}
		else {
			finishedWriting = false;
		}
		//draws message, which is the string "str"
		message.loadFromRenderedTextWrapped(str, textColor, messageWidth);
		if (mini == true) {
			gMiniTextBoxTexture.setAlpha(240);
			gMiniTextBoxTexture.render(messageXPos - 30, messageYPos - 30);
		}
		else {
			gTextBoxTexture.setAlpha(240);
			gTextBoxTexture.render(messageXPos - 50, messageYPos - 50);//903, 565
		}
		message.render(messageXPos, messageYPos);
		pauseGame(true);
	}
	else {
		pauseGame(false);
	}
}
void level::pauseGame(bool pause) {
	pPause = pause;
}
bool level::checkPauseGame() {
	return pPause;
}
bool level::initSpawners() {
	srand(time(NULL));
	spawnerPos[0] = { ((2 * (rand() % 2) - 1)*(500 + (rand() % 300)) + 860),  ((2 * (rand() % 2) - 1)*(150 + (rand() % 200)) + 390) };
	spawnerPos[1] = { ((2 * (rand() % 2) - 1)*(500 + (rand() % 300)) + 860), ((2 * (rand() % 2) - 1)*(150 + (rand() % 200)) + 390) };
	initSpawnersDone = true;
	return initSpawnersDone;
}
void level::deleteSpawners() {
	spawnerPos[0] = { -100, -100 };
	spawnerPos[1] = { -100, -100 };
}
int level::getLevelNumber() {
	return levelNumber;
}
void level::createLevel(enemy enemies[20], node nodes[]) {
	switch (levelNumber) {
	case 1: 
		//**********************************
		//TUTORIAL LEVEL
		//decides number spawned
		spawnNumber[0] = 2;
		spawnNumber[1] = 2;
		if (initSpawnersDone == false) {
			initSpawners();
		}
		//create Spawners
		spawner[0] = { spawnerPos[0].x, spawnerPos[0].y };
		spawner[1] = { spawnerPos[1].x, spawnerPos[1].y };
		if (numberSpawned[0] < spawnNumber[0]) {
			if (spawnDelay[0] == 100) {
				spawner[0].spawnEnemy(enemies, nodes);
				numberSpawned[0]++;
				spawnNumber[0]--;
				spawnDelay[0] = 0;
			}
			spawnDelay[0]++;
		}
		else {
			done[0] = true;
		}
		if (numberSpawned[1] < spawnNumber[1]) {
			if (spawnDelay[1] == 100) {
				spawner[1].spawnEnemy(enemies, nodes);
				numberSpawned[1]++;
				spawnNumber[1]--;
				spawnDelay[1] = 0;
			}
			spawnDelay[1]++;
		}
		else {
			done[1] = true;
		}
		if (checkLevelCompletion(enemies) == true) {
			initSpawnersDone = false;
			numberSpawned[0] = 0;
			numberSpawned[1] = 0;
			done[0] = false;
			done[1] = false;
			//reset message vars
			messageNumber = 0;
			finishedWriting = false;
			showingText = true;
			letterCount = 3;
			letterDelay = 3;
			strcpy_s(messagechars, " ");
			whichLetter = 0;
			str = "";
			deleteSpawners();
			//advance level
			if (levelNumber == 1) {
				levelNumber = 2;
			}
		}
		break;
		//**********************************
	case 2:
		//TUTORIAL ROUND 2
		break;
	case 3:
		//**********************************
		//LEVEL TWO
		//decides number spawned
		spawnNumber[0] = 4;
		spawnNumber[1] = 4;
		if (initSpawnersDone == false) {
			initSpawners();
		}
		//create Spawners
		spawner[0] = { spawnerPos[0].x, spawnerPos[0].y };
		spawner[1] = { spawnerPos[1].x, spawnerPos[1].y };
		if (numberSpawned[0] < spawnNumber[0]) {
			if (spawnDelay[0] == 100) {
				spawner[0].spawnEnemy(enemies, nodes);
				numberSpawned[0]++;
				spawnNumber[0]--;
				spawnDelay[0] = 0;
			}
			spawnDelay[0]++;
		}
		else {
			done[0] = true;
		}
		if (numberSpawned[1] < spawnNumber[1]) {
			if (spawnDelay[1] == 100) {
				spawner[1].spawnEnemy(enemies, nodes);
				numberSpawned[1]++;
				spawnNumber[1]--;
				spawnDelay[1] = 0;
			}
			spawnDelay[1]++;
		}
		else {
			done[1] = true;
		}
		if (checkLevelCompletion(enemies) == true) {
			gNodeTexture.render(100, 100);
		}
		break;
		//**********************************
	}
}
void level::render(int spawnerFrame) {
	if (levelNumber != 0 && levelNumber != 2) {
		if (done[0] == false) {
			spawner[0].render(spawnerFrame);
		}
		if (done[1] == false) {
			spawner[1].render(spawnerFrame);
		}
	}
}