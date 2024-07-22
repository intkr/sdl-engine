#pragma once

#include "clock.h"
#include "graphics.h"
#include "animation.h"

class GraphicsComponent {
	friend class RenderComponent; // allow the rendering component access to the texture and its rect data
public:
	GraphicsComponent();

	void setTexture(std::string name);
	void addAnimation(Animation& a);

	void update(ms delta);

private:
	void updateAnimation(ms delta);
	void updateBox();

	SDL_Texture* texture;
	SDL_Rect textureBox;

	std::vector<Animation> animations;
	std::vector<Animation>::iterator currentAnimation;
};

/*
animations of a gc are only applied to its sprites
things that should apply to both parent and children (like transformations) should be done in a different way (idk how)

applying animations should only affect the source geometry data
after that, the entity position should be passed through its sprites and subentities to set the final geometry data
*/