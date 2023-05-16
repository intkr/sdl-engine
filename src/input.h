#pragma once

#include <map>
#include <vector>

#include "SDL.h"

#include "graphics.h"
#include "sprite.h"

enum MouseStatus {
	 _MOUSE_UP, _MOUSE_ACTIVE, _MOUSE_PASSIVE
};

class Input {
public:
	Input(Graphics* g);
	~Input();

	// Gets mouse / keyboard input from SDL2, and stores its data accordingly.
	void process(SDL_Event& e);

	// Updates all active keys/objects in pressedKeys and clickedObjects to passive ones.
	// Erases all previously released objects from releasedObjects.
	void flushInput();
	
	// Contains all keyboard scancodes that has been pressed.
	// map.first : Object name identifier
	// map.second : Click status (false = active, true = passive)
	std::map<SDL_Scancode, bool>* getPressedKeys();

	// NOTE: Add released keys if needed
	
	// Contains all object identifiers that has been clicked.
	// map.first : Object name identifier
	// map.second : Click status (false = active, true = passive)
	std::map<std::string, bool>* getClickedObject();

	// Contains all object identifiers that were released this frame.
	std::vector<std::string>* getReleasedObject();

	std::vector<std::string>* getHoveredObject();

private:
	// Handles keyboard input.
	// type should be either SDL_KEYDOWN or SDL_KEYUP.
	void pollInput(SDL_Scancode inputKey, Uint32 type);

	// Handles mouse input. (Currently left click only)
	void pollInput(int x, int y);

	// Stores the current status of the left mouse button.
	// 0 : Up
	// 1 : Down (active click)
	// 2 : Down (passive click)
	short mouseStatus;

	int curX, curY;
	SDL_Scancode leftKeybinds[4][3];
	SDL_Scancode rightKeybinds[4][3];

	// Pointer to the Graphics object to access sprite objects.
	const Graphics* _g;

	// Stores all keys that are being pressed.
	// If it's an active key (it was just pressed this frame), then the bool value is false.
	// If it's a passive key (it has been pressed since before), then the bool value is true.
	std::map<SDL_Scancode, bool> pressedKeys;

	// Stores all names of objects where the mouse button is held down within its hitbox.
	// If it's an active click (it was just clicked this frame), then the bool value is false.
	// If it's a passive click (it has been clicked since before), then the bool value is true.
	std::map<std::string, bool> clickedObject;

	// Stores all names of objects where the mouse button is released within its hitbox.
	// Use this to figure out which buttons were clicked, and make sure to clear it before the next frame.
	std::vector<std::string> releasedObject;

	std::vector<std::string> hoveredObject;
};