#pragma once

#include "clock.h"
#include "sprite.h"
#include "animation.h"

class GraphicsComponent {
public:
	void addSprite(Sprite* s);
	void addAnimation(Animation* a);

	void update(ms delta);
	void render();

private:
	// Checks if the object actually exists and has not been added yet.
	// TODO: exception cannot provide enough information as of now
	template<typename T>
	void checkObjectValidity(T* t, std::vector<T*> v);
	template<typename T>
	bool doesObjectExist(T* t, std::vector<T*> v);

	void resetSpriteModifiers();
	void playAnimations();
	void applyAnimation(Animation* animation);

	std::vector<Sprite*> sprites;
	std::vector<Animation*> animations;
};

template <typename T>
void GraphicsComponent::checkObjectValidity<T>(T* t, std::vector<T*> v) {
	if (t == nullptr)
		throw InvalidItemException("nullptr", "object");
	if(doesObjectExist<T>(t))
		throw DuplicateItemException("(?)", "object");
}

template <typename T>
bool GraphicsComponent::doesObjectExist<T>(T* t, std::vector<T*> v) {
	return (std::find(v.begin(), v.end(), t) != v.end());
}

/*
animations of a gc are only applied to its sprites
things that should apply to both parent and children (like transformations) should be done in a different way (idk how)

applying animations should only affect the source geometry data
after that, the entity position should be passed through its sprites and subentities to set the final geometry data
*/