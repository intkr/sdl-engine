#include "transform_component.h"

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
