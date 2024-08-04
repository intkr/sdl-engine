#pragma once

#include <string>
#include <vector>

#include "SDL.h"

#include "clock.h"
#include "animation.h"

class SourceComponent {
	friend class SpriteComponent;

public:
	void initFromFile(std::string path);

	void update(ms delta);

private:
	void setTexture(std::string name);
	void loadAnimationFromFile(std::string path);
	
	void updateAnimation(ms delta);
	void updateBox();

	SDL_Texture* texture;
	SDL_Rect textureBox;

	std::vector<Animation> animations;
	std::vector<Animation>::iterator currentAnimation;
};