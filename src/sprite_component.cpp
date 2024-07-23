#include "graphics_component.h"

void SpriteComponent::setTexture(std::string name) {
	Graphics* g = Graphics::getGraphics();
	try {
		texture = g->getTexture(name);
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}

void SpriteComponent::loadAnimationFromFile(std::string path) {
	try {
		// check if file exists, load if true
		// parse through the file like a json or smth
		// get metadata to create an empty animation object
		// and then add each frame onto the animation
	}
	catch (...) {
		std::cout << e.what();
	}
}

void SpriteComponent::update(ms delta) {
	updateAnimation(delta);
	updateBox();
}

void SpriteComponent::updateAnimation(ms delta) {
	/*
	go through the current animation and iterate through its frames using delta
	if (delta>current frame duration),
		go to next frame
	if (delta>0 and animation's endpoint has been reached),
		go through the next animation and repeat
	if (delta<=curent frame duration),
		finish updating
	*/
}

void SpriteComponent::updateBox() {
	textureBox = currentAnimation->getBox();
}