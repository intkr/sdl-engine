#include "graphics_component.h"

void SourceComponent::setTexture(std::string name) {
	Graphics* g = Graphics::getGraphics();
	try {
		texture = g->getTexture(name);
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}

void SourceComponent::initFromFile(std::string path) {
	try {
		// parse through file
			// get attributes, create empty animation object
			// add each frame onto the animation
	}
	catch (...) {
		std::cout << e.what();
	}
}

void SourceComponent::update(ms delta) {
	updateAnimation(delta);
	updateBox();
}

void SourceComponent::updateAnimation(ms delta) {
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

void SourceComponent::updateBox() {
	textureBox = currentAnimation->getBox();
}