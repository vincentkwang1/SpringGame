#pragma once
#include "global.h"

#ifndef Perlin_h_
#define Perlin_h
class Perlin {
public:
	Perlin();
	std::vector<int> createArray(); //draws the troop
	std::vector<int> create(int width, int height, ppm image, unsigned int seed, int frequency, int size);
private:
};
#endif 
