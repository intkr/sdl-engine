#pragma once

#include "SDL.h"

enum InputType {
	// Default value for no events.
	_INPUT_NONE = 0,
	// Inputs where an entity is focused via
	// keyboard presses or mouse movement.
	_INPUT_FOCUS_IN = 1 << 0,
	_INPUT_FOCUSED = 1 << 1,
	_INPUT_FOCUS_OUT = 1 << 2,
	// Inputs where a mouse button or a key is
	// being pressed down/up on an entity.
	// This can't occur without being focused.
	_INPUT_PRESS_DOWN = 1 << 3,
	_INPUT_PRESSED = 1 << 4,
	_INPUT_PRESS_UP = 1 << 5,
	// Input where an entity has been selected
	// via a mouse click or a 'return' key press.
	_INPUT_CLICK = 1 << 6
};

enum Key {
	// Default value for all keys except ones below
	_KEY_ETC = 0,
	// 12 key layout
	_KEY_A1, _KEY_A2, _KEY_A3,
	_KEY_B1, _KEY_B2, _KEY_B3,
	_KEY_C1, _KEY_C2, _KEY_C3,
	_KEY_D1, _KEY_D2, _KEY_D3,
	// Special function keys
	_KEY_SHIFT,
	_KEY_RETURN,
	_KEY_ESCAPE
}

struct MouseButton {
	// Default value for all buttons except ones below
	_BUTTON_ETC = 0,
	// Mouse press
	_BUTTON_LEFT,
	_BUTTON_MIDDLE,
	_BUTTON_RIGHT,
	// Only used for hover in/out checks
	_BUTTON_NONE
}
struct UserInput {
	InputType type;
}

struct KeyInput : UserInput {
	KeyInput(InputType t, Key k) : key(k), type(t) {}
	
	bool operator==(const KeyInput& other) {
		return (key == other.key) && (type == other.type);
	}
	
	Key key;
}

struct MouseInput : UserInput {
	MouseInput(InputType t, MouseButton b, SDL_FPoint p = SDL_FPoint()) : button(b), pos(p), type(t) {}
	
	bool operator==(const MouseInput& other) {
		return (button == other.button) && (type == other.type);
	}
	
	MouseButton button;
	SDL_FPoint pos;
}