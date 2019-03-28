#include "background.h"
#include "global.h"
void background::render() {
	gBackgroundTexture.render(0,0);
}
void background::loadMedia(int which) {
	switch (which) {
	case 1:gBackgroundTexture.loadFromFile("resource/backgrounds/1.png"); break;
	case 2:gBackgroundTexture.loadFromFile("resource/backgrounds/2.png"); break;
	case 3:gBackgroundTexture.loadFromFile("resource/backgrounds/3.png"); break;
	case 4:gBackgroundTexture.loadFromFile("resource/backgrounds/4.png"); break;
	case 5:gBackgroundTexture.loadFromFile("resource/backgrounds/5.png"); break;
	case 6:gBackgroundTexture.loadFromFile("resource/backgrounds/6.png"); break;
	case 7:gBackgroundTexture.loadFromFile("resource/backgrounds/7.png"); break;
	case 8:gBackgroundTexture.loadFromFile("resource/backgrounds/8.png"); break;
	case 9:gBackgroundTexture.loadFromFile("resource/backgrounds/9.png"); break;
	case 10:gBackgroundTexture.loadFromFile("resource/backgrounds/10.png"); break;
	case 11:gBackgroundTexture.loadFromFile("resource/backgrounds/11.png"); break;
	case 12:gBackgroundTexture.loadFromFile("resource/backgrounds/12.png"); break;
	case 13:gGalaxyMapTexture.loadFromFile("resource/backgrounds/galaxyMap.png"); break;
	}
}