#pragma once

#include "SDL.h"

class Renderer {
public:
	Renderer(SDL_Renderer* r) : renderer(r) {}
	
	void clearScreen();
	void displayScreen();
	void renderTexture(SDL_Texture* tex, const SDL_Rect* source, const SDL_FRect* target, const double angle, const SDL_FPoint* center);
	
private:
	SDL_Renderer* SDLrenderer;
};
