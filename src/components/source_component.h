#pragma once

#include <string>
#include <vector>

#include "SDL.h"

#include "engine/clock.h"
#include "engine/animation.h"

class SourceComponent {
public:
	void initFromFile(std::string path);

	void update(ms delta);

	SDL_Texture* getTexture() { return texture; }
	const SDL_Rect* getSourceBox() { return textureBox; }
	const SDL_FPoint* getCenter() { return center; }
	
private:
	void setTexture(std::string name);
	void loadAnimationFromFile(std::string path);
	
	void updateAnimation(ms delta);
	void updateBox();

	SDL_Texture* texture;
	SDL_Rect textureBox;
    // Point where the sprite will rotate around.
    SDL_FPoint center;

	std::vector<Animation> animations;
	std::vector<Animation>::iterator currentAnimation;
};