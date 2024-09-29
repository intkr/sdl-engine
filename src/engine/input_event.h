#pragma once

#include "SDL.h"

// Small note for my two braincells in the future:
// Whether or not an entity is focused should not be checked by the input system.
// Handle that within the state.

// Defines the state of an input.
enum class InputState {
	// Default state for lack of input.
	_INPUT_NONE = 0,
	// All valid states for key and mouse inputs.
	_INPUT_DOWN, _INPUT_HOLD, _INPUT_UP
};

// Defines the valid actions done via key inputs.
enum class KeyAction {
	// Default value for keys not listed below.
	_KEY_ETC = 0,

	// Add key values specific to the game's needs here
	
	// Special function keys - should not overlap with values above.
	_KEY_SHIFT,
	_KEY_RETURN,
	_KEY_ESCAPE
}

// Defines all valid mouse buttons.
enum class MouseButton {
	// Default value for buttons not listed below.
	_MOUSE_ETC = 0,

	// add side buttons or scroll-related stuff when needed
	_MOUSE_LEFT,
	_MOUSE_MIDDLE,
	_MOUSE_RIGHT,

	// Used on hover inputs without any buttons pressed.
	_MOUSE_HOVER
}

struct UserInput {
	InputState type;
}

struct KeyInput : UserInput {
	KeyInput(KeyAction k, InputState t) : key(k), type(t) {}
	
	bool operator==(const KeyInput& other) {
		return (key == other.key) && (type == other.type);
	}
	
	KeyAction key;
}

struct MouseInput : UserInput {
	MouseInput(MouseButton b, InputState t, SDL_FPoint p = SDL_FPoint()) : button(b), pos(p), type(t) {}
	
	bool operator==(const MouseInput& other) {
		return (button == other.button) && (type == other.type);
	}
	
	MouseButton button;
	SDL_FPoint pos;
}