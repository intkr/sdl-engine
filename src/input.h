#pragma once

#include <map>
#include <algorithm>

#include "SDL.h"

#include "input_event.h"
#include "graphics.h"
#include "entity.h"
#include "states/controller.h"

class Input {
public:
	static Input* getInput();
	static void deleteInput();

	void processInputData();
	void resetInputData();
	
	void setKeybinds(Key key, SDL_Scancode scancode);
	
	bool isQuitTriggered() { return quitTriggered; }
	
private:
	Input();
	~Input();
	Input* _input;
	
	void deleteBindedKeyIfDuplicate(Key key, SDL_Scancode scancode);
	
	void flushInput();
	void flushKeys();
	void flushKeyStatus(InputState& status);
	void flushMouse();
	void changeInputStatus(InputState& input, InputState from, InputState to) {
		if (i == from)
			i = to;
	}
	
	void pollInput();
	void setInputDevicePriority(Uint32 type);
	void setInputStatus(InputState& input, InputState type) { i = type; }
	
	void keyDown(SDL_Scancode inputKey);
	void keyUp(SDL_Scancode inputKey);
	Key getBindedKey(SDL_Scancode scancode);
	void setKeyStatus(Key key, InputState type);
	void addKeyEvent(Key key, InputState type);
	
	void mouseDown(Uint8 button);
	void mouseUp(Uint8 button);
	MouseButton getButton(Uint8 button);
	void updateCursorPos(SDL_Event& e);
	
	void handleInput();
	void handleKeys();
	void handleMouse();
	
	std::map<SDL_Scancode, Key> keybinds;

	std::map<Key, InputState> keyStatus;
	std::map<MouseButton, InputState> mouseStatus;
	SDL_FPoint cursorPos;
	
	// TODO: replace this with a observer connected to the engine - notify it for quit triggers.
	bool quitTriggered;

	enum class InputDevice { _NONE, _MOUSE, _KEY };
	// This variable exists to ensure that any mouse activity overrides all
	// keyboard actions prior, as they should be considered irrelevant. 
	InputDevice lastInputDevice;
};
