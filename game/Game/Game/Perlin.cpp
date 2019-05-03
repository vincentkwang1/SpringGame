#include <cmath>
#include "ppm.h"
#include <iostream>
#include "Perlin.h"
#include "PerlinNoise.h"

Perlin::Perlin() {
	std::vector<int> create(int width, int height, ppm image, unsigned int seed, int frequency, int size);
}
std::vector<int> Perlin::createArray(int gWidth, int gHeight, int frequency, int tileType) {

	// Define the size of the image
	unsigned int width = gWidth, height = gHeight;
	// Create an empty PPM image
	ppm gImage(width, height);
	// Define seed
	unsigned int gSeed = rand() % 1000;
	// Define frequency
	int gFrequency = frequency;//5, 15, 40
	// Define size
	int gSize = width * height;

	// creates a map
	std::vector<int> gValue1 = create(width, height, gImage, gSeed, gFrequency, gSize);
	std::vector<int> gValue2 = create(width, height, gImage, gSeed, gFrequency * 4, gSize);
	std::vector<int> gValue3 = create(width, height, gImage, gSeed, gFrequency * 10, gSize);

	std::vector<int> finalValue;
	finalValue.resize(gSize);
	for (int i = 0; i < gSize; i++) {
		finalValue[i] = (gValue1[i] + gValue2[i] / 2 + gValue3[i] / 4) * 4 / 7;
		if ((finalValue[i] + (tileType-2) * 20) < 255 && finalValue[i]+(tileType-2) * 20 > 0) {
			finalValue[i] = finalValue[i] + (tileType-2) * 20;
		}
	}
	return finalValue;
} 
std::vector<int> Perlin::create(int width, int height, ppm image, unsigned int seed, int frequency, int size) {
	std::vector<int> value;
	value.resize(size);

	// Create a PerlinNoise object with a random permutation vector generated with seed
	PerlinNoise pn(seed);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a shade of gray generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i) {     // y
		for (unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			// Typical Perlin noise
			double n = pn.noise(frequency * x, frequency * y, .8);
			value[kk] = floor(255 * n);
			kk++;
		}
	}
	return value;
}