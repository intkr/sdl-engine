#pragma once

#include <map>
#include <vector>

#include "SDL.h"

#include "sprite.h"

class Input {
public:
	Input(std::map<std::string, Sprite*>** s);
	~Input();

	void process(SDL_Event& e);

	void flushInput();
	
	//void handleClick(std::map<std::string, Sprite*>** sprites);

	std::map<SDL_Scancode, bool>* getPressedKeys();
	std::map<std::string, bool>* getClickedObject();
	std::vector<std::string>* getReleasedObject();

private:
	// Handles keyboard input.
	// type should be either SDL_KEYDOWN or SDL_KEYUP.
	void pollInput(SDL_Scancode inputKey, Uint32 type);

	// Handles mouse input. (Currently left click only)
	void pollInput(int x, int y);

	// Stores the data of the left mouse button.
	// 0 : Up
	// 1 : Down (active click)
	// 2 : Down (passive click)
	short mouseStatus;

	int curX, curY;
	SDL_Scancode leftKeybinds[4][3];
	SDL_Scancode rightKeybinds[4][3];
	std::map<std::string, Sprite*>** _sprites;

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
};