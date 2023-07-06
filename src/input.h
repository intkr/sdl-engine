#pragma once

#include <map>
#include <vector>

#include "SDL.h"

#include "graphics.h"
#include "sprite.h"
#include "states/score.h"

class Core;

enum MouseStatus {
	 _MOUSE_UP, _MOUSE_ACTIVE, _MOUSE_PASSIVE
};

class Input {
	// Note:
	//		An 'active' input means that the input started on this exact frame,
	//		as opposed to a 'passive' input which means that the input has started on previous frames.
	//		The relationship of 'active / passive' is comparable to a 'click / hold' relationship.
public:
	Input(Core* _core);
	~Input();

	/// <summary>
	/// Receives all input for the current frame from SDL,
	/// and stores its data accordingly.
	/// </summary>
	void update();
	
	std::map<SDL_Scancode, bool>* getPressedKeys() { return &pressedKeys; }
	std::vector<SDL_Scancode>* getReleasedKeys() { return &releasedKeys; }
	std::map<std::string, bool>* getClickedSprites() { return &clickedSprites; }
	std::vector<std::string>* getReleasedSprites() { return &releasedSprites; }
	std::vector<std::string>* getHoveredSprites() { return &hoveredSprites; }

	// TODO: this should be unneeded if pressedKeys only contains the 12 assigned keys,
	//		but there should be uniquely assigned keys such as 'Space' and 'Escape' for specific purposes
	//		and the viability of the 12 keys within a non-grid layout should be thoroughly checked.
	int checkKeybinds(SDL_Scancode key);

private:
	/// <summary>
	/// Updates the status of all active keys and sprites to passive,<para/>
	/// and also erases the data of all previously released keys and sprites.
	/// </summary>
	void flushInput();

	/// <summary>
	/// Polls all inputs scanned from SDL, saving its data to designated areas.
	/// </summary>
	void pollInput();

	/// <summary>
	/// Polls a keyboard input scanned from SDL, saving its data to either pressedKeys or releasedKeys.
	/// </summary>
	/// <param name="inputKey">: SDL_Scancode for a given key, with its value following the format 'SDL_SCANCODE_'.</param>
	/// <param name="type">: Value of SDL_Event.type, must be either SDL_KEYDOWN or SDL_KEYUP.</param>
	void pollKey(SDL_Scancode inputKey, Uint32 type);

	/// <summary>
	/// Polls a mouse input scanned from SDL, saving its data to either hoveredSprites, clickedSprites, or releasedSprites.<para/>
	/// Currently only polls left clicks.
	/// </summary>
	/// <param name="x">: x coordinates of the click.</param>
	/// <param name="y">: y coordinates of the click.</param>
	void pollMouse(int x, int y);

	/// <summary>
	/// Calls the current state's input functions for each key / sprite polled on this frame.
	/// </summary>
	void handleInput();

	/// <summary>
	/// Current status of the left mouse button.<para/>
	/// </summary>
	MouseStatus leftClickStatus;

	/// <summary>
	/// Coordinate values of the cursor.
	/// </summary>
	int curX, curY;

	/// <summary>
	/// The keys used for 12-key gameplay.
	/// </summary>
	SDL_Scancode twelveKeys[4][3];
	
	// Stores all keys that are being pressed.
	// If it's an active key (it was just pressed this frame), then the bool value is false.
	// If it's a passive key (it has been pressed since before), then the bool value is true.

	/// <summary>
	/// List of all keys that has been pressed.<para/>
	/// SDL_Scancode refers to a physical keyboard input, with its value following the format 'SDL_SCANCODE_'.<para/>
	/// bool refers to the activeness of the key press.
	/// </summary>
	std::map<SDL_Scancode, bool> pressedKeys;

	/// <summary>
	/// List of all keys that was released.<para/>
	/// SDL_Scancode refers to a physical keyboard input, with its value following the format 'SDL_SCANCODE_'.
	/// </summary>
	std::vector<SDL_Scancode> releasedKeys;
	
	/// <summary>
	/// List of all sprites that has been pressed.<para/>
	/// std::string refers to the name of the sprite.<para/>
	/// bool refers to the activeness of the key press.
	/// </summary>
	std::map<std::string, bool> clickedSprites;

	/// <summary>
	/// List of all sprites that was released.<para/>
	/// std::string refers to the name of the sprite.
	/// </summary>
	std::vector<std::string> releasedSprites;

	/// <summary>
	/// List of all sprites that is being hovered on.<para/>
	/// std::string refers to the name of the sprite.
	/// </summary>
	std::vector<std::string> hoveredSprites;
	
	Core* core;
};