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
	
	// active values (_IN / _OUT) are transformed into passive (_ED) values.
	void flushInput();
	void flushKeys();
	void flushKeyStatus(InputType& status);
	void flushMouse();
	void changeInputStatus(InputType& input, InputType from, InputType to) {
		if (i == from)
			i = to;
	}
	
	void pollInput();
	void setInputDevicePriority(Uint32 type);
	void setInputStatus(InputType& input, InputType type) { i = type; }
	
	void keyDown(SDL_Scancode inputKey);
	void keyUp(SDL_Scancode inputKey);
	Key getBindedKey(SDL_Scancode scancode);
	void setKeyStatus(Key key, InputType type);
	void addKeyEvent(Key key, InputType type);
	
	void mouseDown(Uint8 button);
	void mouseUp(Uint8 button);
	MouseButton getButton(Uint8 button);
	void updateCursorPos(SDL_Event& e);
	
	void handleInput();
	void handleKeys();
	void handleMouse();

	std::map<SDL_Scancode, Key> keybinds;
	std::map<Key, InputType> keyStatus;
	std::map<MouseButton, InputType> mouseStatus;
	SDL_FPoint cursorPos;
	
	// 99% sure this is bad implementation, search for a better alternative
	bool quitTriggered;

	enum class InputDevice { _NONE, _MOUSE, _KEY };
	// This variable exists to ensure that any mouse activity overrides all
	// keyboard actions prior, as they should be considered irrelevant. 
	InputDevice lastInputDevice;
};
