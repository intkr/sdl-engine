#pragma once

#include "SDL.h"
#include "SDL_image.h"

struct Texture {
	~Texture() { SDL_DestroyTexture(texture); }
	Texture(SDL_Texture* _texture, std::string _name) : texture(_texture), name(_name) {}
	
	SDL_Texture* texture;
	std::string name;
}
