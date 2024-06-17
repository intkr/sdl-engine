#include "state.h"

void State::assignResources(Resource* res) {
	resources = res;
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



void State::addKeyEvent(KeyInput input, void(*f)()) {
	if (keyEvents.find(input) != keyEvents.end()) {
		std::cout << "Event overriden\n";
	}
	keyEvents.emplace(input, f);
}
