#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <cmath>
#include <sstream>;
//CREATE METHODS/GLOBAL CONSTANTS
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
typedef int32_t s32;

//METHODS: init, load_image, close, loadSurface
bool init();
void close();
bool loadMedia();
bool checkCollision(SDL_Rect a, SDL_Rect b);

class LTexture {
public:
	LTexture();
	~LTexture();
	void loadFromFile(std::string path);
	void loadFromRenderedText(std::string textureText, SDL_Color textColor);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};
//SCREEN COMPONENTS
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
LTexture gTextTexture;
//METHODS DEFINED
bool init() {
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("Vincent's Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags) & imgFlags;
	TTF_Init();
	return success;
}
bool loadMedia() {
	bool success = true;
	gFont = TTF_OpenFont("resource/font.ttf", 80);
	return success;
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
void fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	static const int BPP = 4;
	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
		SDL_RenderDrawLine(gRenderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(gRenderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
	}
}
//TEXTURE
LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}
void LTexture::loadFromFile(std::string path){
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;
}
void LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	mWidth = textSurface->w;
	mHeight = textSurface->h;
	SDL_FreeSurface(textSurface);
}
void LTexture::free(){
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}
void LTexture::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(mTexture, blending);
}
void LTexture::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(mTexture, alpha);
}
void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
int LTexture::getWidth(){
	return mWidth;
}
int LTexture::getHeight(){
	return mHeight;
}
//PADDLE
class Paddle1 {
public:
	static const int paddle_height = SCREEN_HEIGHT / 4;
	static const int paddle_width = 30;
	static const int paddle_spd = 12;
	Paddle1();
	void handleEvent(SDL_Event& e);
	void move();
	void render();
	void reset();
	SDL_Rect getpCollider();
private:
	int pPosX, pPosY;
	int pVel;
	SDL_Rect pCollider;
};
Paddle1::Paddle1() {
	pPosX = SCREEN_WIDTH / 15;
	pPosY = 3 * (SCREEN_HEIGHT / 8);
	pCollider.h = SCREEN_HEIGHT/4;
	pCollider.w = 30;
	pVel = 0;
}
void Paddle1::reset() {
	pPosX = SCREEN_WIDTH / 15;
	pPosY = 3 * (SCREEN_HEIGHT / 8);
}
void Paddle1::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w: pVel -= paddle_spd; break;
		case SDLK_s: pVel += paddle_spd; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_w: pVel += paddle_spd; break;
		case SDLK_s: pVel -= paddle_spd; break;
		}
	}
}
void Paddle1::move() {
	pCollider.x = pPosX;
	pPosY += pVel;
	pCollider.y = pPosY;
	if ((pPosY  < 0) || (pPosY + paddle_height > SCREEN_HEIGHT)) {
		pPosY -= pVel;
		pCollider.y = pPosY;
	}
}
void Paddle1::render() {
	SDL_Rect paddle1;
	paddle1.x = pPosX;
	paddle1.y = pPosY;
	paddle1.w = 30;
	paddle1.h = SCREEN_HEIGHT / 4;
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &paddle1);
}
SDL_Rect Paddle1::getpCollider() {
	return pCollider;
}
//AI PADDLE
class Paddle2 {
public:
	static const int paddle_height = SCREEN_HEIGHT / 4;
	static const int paddle_width = 30;
	static const int paddle_spd = 12;
	Paddle2();
	void handleEvent(SDL_Event& e);
	void move();
	void render();
	void reset();
	SDL_Rect getaCollider();
private:
	int aPosX, aPosY;
	int aVel;
	SDL_Rect aCollider;
};
Paddle2::Paddle2() {
	aPosX = SCREEN_WIDTH- (SCREEN_WIDTH / 15);
	aPosY = 3 * (SCREEN_HEIGHT / 8);
	aCollider.h = SCREEN_HEIGHT / 4;
	aCollider.w = 30;
	aVel = 0;
}
void Paddle2::reset() {
	aPosX = SCREEN_WIDTH - (SCREEN_WIDTH / 15);
	aPosY = 3 * (SCREEN_HEIGHT / 8);
}
void Paddle2::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: aVel -= paddle_spd; break;
		case SDLK_DOWN: aVel += paddle_spd; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		case SDLK_UP: aVel += paddle_spd; break;
		case SDLK_DOWN: aVel -= paddle_spd; break;
		}
	}
}
void Paddle2::move() {
	aCollider.x = aPosX;
	aPosY += aVel;
	aCollider.y = aPosY;
	if ((aPosY < 0) || (aPosY + paddle_height > SCREEN_HEIGHT)) {
		aPosY -= aVel;
		aCollider.y = aPosY;
	}
}
void Paddle2::render() {
	SDL_Rect paddle2;
	paddle2.x = aPosX;
	paddle2.y = aPosY;
	paddle2.w = 30;
	paddle2.h = SCREEN_HEIGHT / 4;
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &paddle2);
}
SDL_Rect Paddle2::getaCollider() {
	return aCollider;
}
//BALL
class Ball {
public:
	static const int ball_diameter = 32;
	Ball();
	int move(SDL_Rect& paddle1, SDL_Rect& paddle2);
	void render();
	void reset1();
	void reset2();
	SDL_Rect getmCollider();
private:
	double mPosX, mPosY;
	double mVelX, mVelY;
	SDL_Rect mCollider;
};
Ball::Ball() {
	mPosX = SCREEN_WIDTH/2;
	mPosY = -5 + SCREEN_HEIGHT / 2;
	mCollider.w = ball_diameter;
	mCollider.h = ball_diameter;
	mVelX = 10;
	mVelY = 0;
}
int Ball::move(SDL_Rect& paddle1, SDL_Rect& paddle2) {
	mPosX += mVelX;
	mCollider.x = mPosX - mCollider.w / 2;
	mPosY += mVelY;
	mCollider.y = mPosY-mCollider.h/2;
	if ((mPosX - mCollider.w / 2 < 0)) {
		return 1;
	}
	if (checkCollision(mCollider, paddle1) && (mPosX -20 - mCollider.w / 2 < SCREEN_WIDTH / 15)) {
		mVelY = -mVelY;
		mCollider.y = mPosY - mCollider.h / 2;
		return 0;
	}
	else if ((mPosX + mCollider.w/2 > SCREEN_WIDTH)) {
		return 2;
	}
	else if (checkCollision(mCollider, paddle2)) {
		mVelX = -mVelX;
		mCollider.x = mPosX - mCollider.w / 2;
		mCollider.y = mPosY - mCollider.h / 2;
		mVelY = mVelY + 6 * (.9 + 2 * (-(paddle2.y + paddle2.h) + (mPosY + mCollider.w / 2)) / paddle2.h);
		return 0;
	}
	else if (checkCollision(mCollider, paddle1)) {
		mVelX = -mVelX;
		mCollider.x = mPosX - mCollider.w / 2;
		mCollider.y = mPosY - mCollider.h / 2;
		mVelY = mVelY + 6*(.9 + 2*(-(paddle1.y + paddle1.h) + (mPosY + mCollider.w / 2)) / paddle1.h);
		return 0;
	}
	if ((mPosY - mCollider.h / 2 < 0) || (mPosY + mCollider.w / 2 > SCREEN_HEIGHT)) {
		mVelY = -mVelY;
		mCollider.y = mPosY - mCollider.h / 2;
		return 0;
	}
	return 0;
}
void Ball::render() {
	fill_circle(gRenderer, mPosX, mPosY, 16, 0xFF, 0xFF, 0xFF, 0xFF);
}
SDL_Rect Ball::getmCollider() {
	return mCollider;
}
void Ball::reset1() {
	mPosX = SCREEN_WIDTH/2;
	mPosY = -5 + SCREEN_HEIGHT / 2;
	mVelX = 10;
	mVelY = 0;
}
void Ball::reset2() {
	mPosX = SCREEN_WIDTH/2;
	mPosY = -5 + SCREEN_HEIGHT / 2;
	mVelX = -10;
	mVelY = 0;
}
//CHECK COLLISION
bool checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	if (bottomA <= topB){
		return false;
	}
	if (topA >= bottomB){
		return false;
	}
	if (rightA <= leftB){
		return false;
	}
	if (leftA >= rightB){
		return false;
	}
	return true;
}
//MAIN FUNCTION
int main(int argc, char* args[]) {
	int player_score = 0;
	int ai_score = 0;
	init();
	loadMedia();
	bool quit = false;
	SDL_Event e;
	Ball ball;
	Paddle1 paddle1;
	Paddle2 paddle2;
	//GAME MAIN LOOP
	while (!quit) {
		//ALLOWS QUITTING
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT ) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
			}
			paddle1.handleEvent(e);
			paddle2.handleEvent(e);
		}
		//ACTUAL THINGS HAPPENING
		SDL_Rect cPaddle1 = paddle1.getpCollider();
		SDL_Rect cPaddle2 = paddle2.getaCollider();
		SDL_Rect hitBox = ball.getmCollider();
		SDL_Delay(20);
		if (ball.move(cPaddle1, cPaddle2) == 1) {
			ai_score++;
			if (ai_score > 10) {
				std::cout << "Player Loses!!";
				quit = true;
			}
			std::cout << player_score;
			std::cout << "-";
			std::cout << ai_score;
			std::cout << "\n";
			ball.reset1();
			paddle1.reset();
			paddle2.reset();
			SDL_Delay(500);
		}
		else if (ball.move(cPaddle1, cPaddle2) == 2) {
			player_score++;
			if (player_score > 10) {
				std::cout << "Player Wins!!";
				quit = true;
			}
			std::cout << player_score;
			std::cout << "-";
			std::cout << ai_score;
			std::cout << "\n";
			ball.reset2();
			paddle1.reset();
			paddle2.reset();
			SDL_Delay(500);
		}
		paddle1.move();
		paddle2.move();
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);
		//PADDLE 1
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		//PADDLE 2
		SDL_RenderFillRect(gRenderer, &cPaddle2);
		//CIRCLE
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &cPaddle1);
		ball.render();
		SDL_Color textColor = { 255, 0, 0 };
		std::ostringstream oss;
		oss << player_score << "-" << ai_score;
		gTextTexture.loadFromRenderedText(oss.str(), textColor);
		gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
		//DRAW
		SDL_RenderPresent(gRenderer);
	}
	//END OF MAIN LOOP
	close();
	return 0;
}