#include "entity.h"

Entity::~Entity() {
	// Delete subentities first,
	for (Entity*& e : subentities) {
		delete e;
	}
	
	// then delete components
}

bool operator==(const Entity& other) const {
	return name == other.name;
}


void Entity::addSubentity(Entity* e) {
	try {
		// TODO: uh idk where code for this function went lol
		// also retouch similar functions below and ones on other files

		//checkObjectValidity(e, subentities); 
		subentities.push_back(e);
	}
	catch (GameException& ex) {
		std::cout << ex.what();
	}
}

Entity* Entity::getSubentity(std::string name) {
	auto iter = std::find(subentities.begin(), subentities.end(), e);
	if (iter == subentities.end()) {
		throw InvalidItemException(name, "entity");
	}
	return *iter;
}

void addSprite(SpriteComponent* sprite) {
	auto iter = std::find(sprites.begin(), sprites.end(), sprite);
	if (iter != sprites.end()) {
		throw DuplicateItemException(sprite->getName(), "sprite");
	}
	sprites.push_back(sprite);
}

void addCollision(CollisionComponent* collision, std::string spriteName) {
	auto iter = std::find(sprites.begin(), sprites.end(), spriteName);
	if (iter == sprites.end()) {
		throw InvalidItemException(spriteName, "sprite");
	}
	collisions.push_back(collision);
	collision->setSpriteTransform(iter->getTransform());
}

//////////////////////////////////////
// old code below
//////////////////////////////////////

void Entity::setKeyEvent(KeyInput input, void(*f)(Entity*)) {
	if (keyEvents.find(input) != keyEvents.end()) {
		std::cout << "Warning - Overriding key event on " << name << "\n";
	}
	keyEvents.emplace(input, f);
}

void Entity::setMouseEvent(MouseInput input, void(*f)(Entity*)) {
	if (mouseEvents.find(input) != mouseEvents.end()) {
		std::cout << "Warning - Overriding mouse event on " << name << "\n";
	}
	mouseEvents.emplace(input, f);
}

void Entity::update() {
	graphics.update();
}

void Entity::updateHitboxes(EntityGeometry parentGeometry) {
	EntityGeometry entityGeometry = parentGeometry + geometry;
	// Recursively update subentities' hitboxes first,
	for (Entity* entity : subentities) {
		entity->updateHitboxes(entityGeometry);
	}
	// and then update this entity's sprite hitboxes
	for (Sprite* sprite : sprites) {
		sprite->updateHitbox(entityGeometry);
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
	if (doesCollide(pos)) {
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

bool Entity::doesCollide(SDL_FPoint point) {
	SDL_FRect*& modRect = geometry.modRect;
	point.x -= modRect->x;
	point.y -= modRect->y;

	for (Sprite* sprite : sprites) {
		if (sprite->isPointInSprite(point))
			return true;
	}
	return false;
}