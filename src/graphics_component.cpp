#include "graphics_component.h"

void GraphicsComponent::addSprite(Sprite* s) {
	try {
		checkObjectValidity<Sprite>(s, sprites);
		sprites.push_back(s);
	}
	catch (GameException& e) {
		std::cout << e.what();
	}
}

void GraphicsComponent::addAnimation(Animation* a) {
	try {
		checkObjectValidity<Animation>(a, animations);
		animations.push_back(a);
	}
	catch (GameException& e) {
		std::cout << e.what();
	}
}

void GraphicsComponent::update() {
	resetSpriteModifiers();
	playAnimations();
}

void GraphicsComponent::resetSpriteModifiers() {
	for (Sprite* sprite : sprites) {
		sprite->reset();
	}
}

void GraphicsComponent::playAnimations() {
	for (Animation* animation : animations) {
		applyAnimation(animation);
	}
}

void GraphicsComponent::applyAnimation(Animation* a) {
	for (Sprite* sprite : sprites) {
		sprite->applyAnimation(a);
	}
}
