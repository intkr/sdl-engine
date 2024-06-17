#define SDL_MAIN_HANDLED

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "engine.h"

void openDebugConsole() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	//openDebugConsole();

	Engine engine;
	engine.loop();

	return 0;
}

/*
Highly prioritized stuff I must do before I eventually meltdown:
	- (#1 priority) use CMake to build this project instead of Visual Studio,
	  so it becomes decoupled from VS for anyone who may not use it to code stuff.

	- Consider using Lua to make states instead of hardcoding and linking everything into the StateController.
	  This should be better for game extensibility and flexibility in the long term.
	  (maybe consider using Sol (https://github.com/ThePhD/sol2))
	  * Also research about what should be hardcoded and what should be scripted because I have no idea

	- Implement a logging system for easier debugging

	- When implementing customizable keybinds, how should duplicate keys be handled?
		* If it's guaranteed that two key actions can not happen simultaneously,
		  then having duplicate keys shouldn't be a problem and may be allowed.
		  A category system for key actions would be required for this to be possible - think about this more later.

	- Text (fonts and text color) and sprites should be separated into their own classes, not within Graphics.

	- When handling time in states, search for a way that can ignore time being paused

	- Implement attributes for sprites / entities / states
	  Notable examples I should add:
		- Collidable (Entity) : ignore collision checks if false for optimization
		- Renderable (Entity, Sprite) : used for invisible hitboxes (idk when I'd use but still)
		- StateSpecific (Entity, Sprite) : used for resources specific to that state only (allows smooth state transitions if false)
		- Interactable (State) : false for cutscenes and whatnot
		- Paused (State) : self-explanatory
*/

/*
Moderately important stuff to ponder upon like a sophisticated individual:
	- Add functions in classes such that all classes adhere to "the rule of fives".

	- Replace all #pragma onces with #ifndefs for IDE compatibility.

	- The current input system does not properly handle key presses that aren't used in the game.
	  i.e. pressing multiple of those may or may not trigger each PRESS_DOWN/ED/UP as one might expect.

	- How do I handle storing and rendering sprites without intertwining a bunch of headers and classes

	- Find a way to add game-specific key values without altering the enum class itself -
	  in other words, consider using a different method of storing valid keys (vectors or whatever, maybe create a custom class idk)
	  
	- Optimize collision checking
*/

/*
Not-too-important small notes for the brainrot future me:
	- Create audio effect systems.. if I need it idk

	- BPM should be handled by a music-specific class object, not Channels or whatever.

	- Remind myself why recursive animation exists because I don't get the point of it rn

	- When checking for collision of an entity, consider overloading a single collision-checking function
	  with all possible targets - a single point (mouse cursor), a line, convex/concave shapes, etc.
*/