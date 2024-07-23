#pragma once

#include "clock.h"
#include "graphics.h"
#include "animation.h"

class SpriteComponent {
	friend class RenderComponent; // allow the rendering component access to the texture and its box data
public:
	SpriteComponent();

	void setTexture(std::string textureName);
	void loadAnimationFromFile(std::string path);

	void update(ms delta);

private:
	void updateAnimation(ms delta);
	void updateBox();

	Attribute attribute;
	SDL_Texture* texture;
	SDL_Rect textureBox;

	std::vector<Animation> animations;
	std::vector<Animation>::iterator currentAnimation;
};