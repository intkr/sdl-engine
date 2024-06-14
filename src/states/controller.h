#pragma once
#include <map>

#include "../input_event.h"

#include "StateTitle.h"
#include "StateSelect.h"
#include "StatePrep.h"
#include "StateTest.h"

#include "GamePair.h"

class StateController {
public:
	StateController();
	~StateController();

	void update();
	void changeState(StateCode state);

	void handleKey(KeyInput input);
	void handleMouse(MouseInput input);

private:
	void loadState(StateCode state);
	
	State* state;
};