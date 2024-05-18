#pragma once

#include "SDL.h"

#include "geometry.h"
#include "texture.h"

// probably shouldnt implement like this but im not smart enough to do otherwise

class Renderer {
public:
	Renderer(SDL_Renderer* r) : renderer(r) {}
	
	void clearScreen();
	void displayScreen();
	void renderTexture(Texture* tex, Geometry& geo);
	
private:
	SDL_Renderer* SDLrenderer;
};
