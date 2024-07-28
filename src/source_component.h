#pragma once

#include "clock.h"
#include "graphics.h"
#include "animation.h"

class SourceComponent {
	friend class GraphicsComponent;
public:
	void initFromFile(std::string path);

	void update(ms delta);

private:
	void setTexture(std::string name);
	void loadAnimationFromFile(std::string path);
	
	void updateAnimation(ms delta);
	void updateBox();

	Attribute attribute;
	SDL_Texture* texture;
	SDL_Rect textureBox;

	std::vector<Animation> animations;
	std::vector<Animation>::iterator currentAnimation;
};