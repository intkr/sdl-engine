#pragma once

#include "SDL.h"

class Renderer {
public:
	Renderer(SDL_Renderer* r) : renderer(r) {}
	
	void clearScreen();
	void displayScreen();
	void renderTexture(SDL_Texture* tex, SDL_Rect* source, SDL_FRect target, double angle = 0.0);
	
private:
	SDL_Renderer* SDLrenderer;
};
