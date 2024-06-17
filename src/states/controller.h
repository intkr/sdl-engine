#pragma once

#include <map>
#include <vector>

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
	void addState(StateCode state);
	void changeActiveState(StateCode state);
	void deleteActiveState();

	void handleInput(KeyInput i);
	void handleInput(MouseInput i);

private:
	StateController();
	~StateController();
	StateController* _controller;
	
	State* createState(StateCode state);

	// This temporary implementation allows creating State objects with small code,
	// but this should be replaced with a Lua script later on.
	template <typename T>
	State* createState() { return new T; }
	void mapStateCodes();
	StateMap stateCodes;
	
	// The state stack puts the most recent item in the back.
	// The last item in the stack is the currently active state.
	std::vector<State*> stateStack;
	State* activeState;

	Resources* resources;
};
