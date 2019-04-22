#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <cmath>
#include <sstream>
#ifndef LTexture_h_
#define LTexture_h_
class LTexture {
public:
	LTexture();
	~LTexture();
	void loadFromFile(std::string path);
	void loadFromRenderedText(std::string textureText, SDL_Color textColor);
	void loadFromRenderedTextWrapped(std::string textureText, SDL_Color textColor, int width);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
	void colorMod(int r, int g, int b);
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
#endif // !LTexture_h_
