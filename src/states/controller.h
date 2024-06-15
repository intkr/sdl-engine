#pragma once

#include <map>

#include "state.h"
#include "resources.h"

#include "../input_event.h"
#include "../graphics.h"

// All available states should be included here
#include "StateTitle.h"
#include "StateSelect.h"
#include "StatePrep.h"
#include "StateTest.h"

typedef std::map<StateCode, State*(*)()> StateMap;

class StateController {
public:
	static StateController* getStateController();
	static void deleteStateController();

	void update();
	void render(Renderer* r);
	void changeState(StateCode state);

	void handleInput(KeyInput i);
	void handleInput(MouseInput i);

private:
	StateController();
	~StateController();
	StateController* _controller;
	
	void loadState(StateCode state);

	// This temporary implementation allows creating State objects with small code,
	// but this should be replaced with a Lua script later on.
	template <typename T>
	State* createState() { return new T; }
	void initStateTypes();
	StateMap stateTypes;
	
	State* state;
	Resources* resources;
};
