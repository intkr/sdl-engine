#include "entity.h"

Entity::~Entity() {
	// delete sprite and animations
	// delete subentities (recursive)
}

bool operator==(const Entity& other) const {
	return attribute.name == other.attribute.name;
}

void Entity::addSprite(Sprite* s) {
	try {
		checkSpriteValidity(s);
		sprites.push_back(s);
	}
	catch (GameException& e) {
		std::cout << e.what();
	}
}

void Entity::checkSpriteValidity(Sprite* s) {
	if (s == nullptr)
		throw InvalidItemException("nullptr", "sprite");
	if(isSpriteAlreadyMapped(s))
		throw DuplicateItemException(s->getName(), "sprite");
}

bool Entity::isSpriteAlreadyMapped(Sprite* s) {
	return (std::find(sprites.begin(), sprites.end(), s) != sprites.end());
}

void Entity::addAnimation(Animation* a) {
	try {
		checkAnimationValidity(a);
		sprites.push_back(a);
	}
	catch (GameException& e) {
		std::cout << e.what();
	}
}

void Entity::checkAnimationValidity(Animation* a) {
	if (a == nullptr)
		throw InvalidItemException("nullptr", "animation");
	if(isAnimationAlreadyMapped(a))
		throw DuplicateItemException(a->getName(), "animation");
}

bool Entity::isAnimationAlreadyMapped(Animation* a) {
	return (std::find(animations.begin(), animations.end(), a) != animations.end());
}

void Entity::addSubentity(Entity* e) {
	// TODO: separate code like other add functions
	if (e == nullptr || std::find(subentities.begin(), subentities.end(), e) == subentities.end()) {
		subentities.push_back(e);
	}
}

Entity* Entity::getSubentity(std::string name) {
	auto iter = std::find(subentities.begin(), subentities.end(), e);
	if (iter == subentities.end()) throw InvalidItemException(name, "entity");
	return *iter;
}

void Entity::setKeyEvent(KeyInput input, void(*f)(Entity*)) {
	if (keyEvents.find(input) != keyEvents.end()) {
		std::cout << "Warning - Overriding key event on " << attribute.name << "\n";
	}
	keyEvents.emplace(input, f);
}

void Entity::setMouseEvent(MouseInput input, void(*f)(Entity*)) {
	if (mouseEvents.find(input) != mouseEvents.end()) {
		std::cout << "Warning - Overriding mouse event on " << attribute.name << "\n";
	}
	mouseEvents.emplace(input, f);
}

void Entity::update() {
	resetAllSpriteEffects();
	playAnimations();
	updateHitboxes();
}

void Entity::resetAllSpriteEffects() {
	for (Sprite* sprite : sprites) {
		sprite->reset();
	}
}

void Entity::playAnimations() {
	for (Animation* animation : animations) {
		if (animation->isRecursive()) {
			animateRecursively(animation);
		}
		else applyAnimation(animation);
	}
}

void Entity::animateRecursively(Animation* a) {
	applyAnimation(animation);
	// apply animation to subentities first,
	for (Entity* entity : subentities) {
		entity->animateRecursively(a);
	}
	// then apply the animation to the current entity.
	applyAnimation(a);
}

void Entity::applyAnimation(Animation* a) {
	for (Sprite* sprite : sprites) {
		sprite->applyAnimation(a);
	}
}

void Entity::updateHitboxes(Orientation parentOrientation) {
	Orientation entityOrientation = parentOrientation + orientation;
	// recursively update subentities
	for (Entity* entity : subentities) {
		entity->updateHitboxes(entityOrientation);
	}
	// update this entity's sprite hitboxes
	for (Sprite* sprite : sprites) {
		sprite->updateHitbox(entityOrientation);
	}
}

void Entity::draw(Renderer* renderer) {
	for (Sprite* sprite : sprites) {
		sprite->draw(renderer);
	}
}

void Entity::handleKey(KeyInput input) {
	auto iter = keyEvents.find(input);
	if (iter != keyEvents.end())
		iter.second(this);
}

void Entity::handleMouse(MouseInput input) {
	MouseInput collisionInput = getCollisionInput(input.pos);
	
	if (collisionInput.type != _INPUT_NONE) {
		handleMouseInput(input);
	}
	handleMouseInput(collisionInput);
}

MouseInput Entity::getCollisionInput(SDL_FPoint pos) {
	if (isPointInEntity(pos)) {
		if (!isFocused()) {
			return MouseInput(_INPUT_FOCUS_IN, _MOUSE_NONE);
		}
		return MouseInput(_INPUT_FOCUSED, _MOUSE_NONE);
	}
	else {
		if (isFocused()) {
			return MouseInput(_INPUT_FOCUS_OUT, _MOUSE_NONE);
		}
		return MouseInput(_INPUT_NONE, _MOUSE_NONE);
	}
}

void Entity::handleMouseActivity(MouseInput input) {
	auto iter = mouseEvents.find(input);
	if (iter != mouseEvents.end())
		iter.second(this);
}

bool Entity::isPointInEntity(SDL_FPoint point) {
	SDL_FRect*& modRect = geometry.modRect;
	point.x -= modRect->x;
	point.y -= modRect->y;

	for (Sprite* sprite : sprites) {
		if (sprite->isPointInSprite(point))
			return true;
	}
	return false;
}