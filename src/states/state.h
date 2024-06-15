#pragma once
#include <string>
#include <algorithm>
#include <map>

#include <SDL.h>

#include "resources.h"

#include "../input_event.h"
#include "../motion_functions.h"
#include "../renderer.h"


enum class StateCode {
	_STATE_TEST = 0, _STATE_TITLE, _STATE_SELECT, _STATE_PREP,
	_GAME_PAIR
};

// Base class for states in a Finite State Machine.
class State {
public:
	State() {}
	virtual ~State() {}

	void render(Renderer* renderer);

	virtual void init() = 0;
	virtual void updateData() = 0;
	virtual void updateAssets() = 0;
	virtual void exit() = 0;
	
	void handleKey(KeyInput input);
	void handleMouse(MouseInput input);

protected:
	void addSprite(Sprite* sprite);
	void addEntity(Entity* entity);
	void addKeyEvent(KeyInput input, void(*f)());
	
	std::map<KeyInput, void(*)()> keyEvents;
	Resources* res;
};