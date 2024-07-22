#include "graphics_component.h"

GraphicsComponent::GraphicsComponent() {
}

void GraphicsComponent::setTexture(std::string name) {
	Graphics* g = Graphics::getGraphics();
	try {
		texture = g->getTexture(name);
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}

void GraphicsComponent::addAnimation(Animation& a) {
	try {
		checkObjectValidity<Animation>(a, animations);
		animations.push_back(a);
	}
	catch (GameException& e) {
		std::cout << e.what();
	}
}

void GraphicsComponent::update(ms delta) {
	updateAnimation(delta);
	updateBox();
}

void GraphicsComponent::updateAnimation(ms delta) {
	/*
	go through the current animation and iterate through its frames using delta
	if (delta>0 and animation's endpoint has been reached),
		go through the next animation and repeat
	if (delta=0 before or as the animation's endpoint),
		finish updating
	*/
}

void GraphicsComponent::updateBox() {
	textureBox = currentAnimation->getBox();
}