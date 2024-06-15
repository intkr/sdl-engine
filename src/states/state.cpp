#include "state.h"

void State::render(Renderer* renderer) {
	for (Sprite* sprite : sprites) {
		sprite->render(renderer);
	}
}

void State::handleKey(KeyInput input) {
	// If a key event can be triggered from the state itself,
	// trigger that event and finish handling.
	if (keyEvents.find(input) != keyEvents.end()) {
		keyEvents.at(input)();
		return;
	}
	
	// Otherwise, trigger key events from the currently focused entity.
	// TODO: replace iteration with smth like "currentFocusedEntity" returned by the state.
	Entity* entity;
	for (auto iter : entities) {
		entity = iter.second;
		if (entity->isFocused()) {
			entity->handleKey(input);
		}
	}
}

void State::handleMouse(MouseInput input) {
	Entity* entity;
	for (auto iter : entities) {
		entity = iter.second;
		if (entity->doesCollide(input.pos)) {
			entity->handleMouse(input);
		}
	}
}

void State::addSprite(Sprite* sprite) {
	auto iter = std::lower_bound(sprites.begin(), sprites.end(), sprite,
	[](Sprite& a, Sprite& b) -> bool { return a.getLayer() < b.getLayer(); } );
	sprites.insert(iter, sprite);
}

void State::addEntity(Entity* entity) {
	entities.push_back(entity);
}

void State::addKeyEvent(KeyInput input, void(*f)()) {
	if (keyEvents.find(input) != keyEvents.end()) {
		std::cout << "Event overriden\n";
	}
	keyEvents.emplace(input, f);
}
