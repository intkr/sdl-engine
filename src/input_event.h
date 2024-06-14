#pragma once

#include "SDL.h"

enum InputType {
	// Default value for lack of events.
	_INPUT_NONE = 0,
	// Inputs where an entity is focused via mouse movement.
	_INPUT_FOCUS_IN = 1 << 0,
	_INPUT_FOCUSED = 1 << 1,
	_INPUT_FOCUS_OUT = 1 << 2,
	// Inputs where a mouse button or a key has acted on an entity.
	_INPUT_PRESS_DOWN = 1 << 3,
	_INPUT_PRESSED = 1 << 4,
	_INPUT_PRESS_UP = 1 << 5,
	// Input where an entity has been selected
	// via a mouse click or an 'Enter' key press.
	_INPUT_CLICK = 1 << 6
};

enum Key {
	// Default value for keys not listed below
	_KEY_ETC = 0,
	// Add key values specific to the game's needs

	// Special function keys
	_KEY_SHIFT,
	_KEY_RETURN,
	_KEY_ESCAPE
}

struct MouseButton {
	// Default value for all buttons not listed below
	_BUTTON_ETC = 0,
	// Mouse press
	_BUTTON_LEFT,
	_BUTTON_MIDDLE,
	_BUTTON_RIGHT,
	// Not a mouse press, used for mouse movement only
	_BUTTON_NONE
}
struct UserInput {
	InputType type;
}

struct KeyInput : UserInput {
	KeyInput(Key k, InputType t) : key(k), type(t) {}
	
	bool operator==(const KeyInput& other) {
		return (key == other.key) && (type == other.type);
	}
	
	Key key;
}

struct MouseInput : UserInput {
	MouseInput(MouseButton b, InputType t, SDL_FPoint p = SDL_FPoint()) : button(b), pos(p), type(t) {}
	
	bool operator==(const MouseInput& other) {
		return (button == other.button) && (type == other.type);
	}
	
	MouseButton button;
	SDL_FPoint pos;
}