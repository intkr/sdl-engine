#pragma once

#include "SDL.h"

#include "attribute.h"
#include "geometry.h"

class Texture {
	friend class RenderComponent;

public:
	Texture(SDL_Texture* _texture, std::string _name) : texture(_texture), attribute(_name) {}
	~Texture() {
		SDL_DestroyTexture(texture);
	}

	void setSourceBox(Rect<int> box) {
		sourceBox = box;
	}

private:
	Attribute attribute;
	SDL_Texture* source;
	Rect<int> sourceBox;
}
