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

	- Implement a logging system for easier debugging

	- get the state-related files I wrote on mobile because I forgor to bring those
	- also figure out a way to keep entities/sprites loaded when transitioning to a new state
	  for some smooth transitioning animations

	- Input events confuse me rn so be sure to make that clear in my brain,
	  and then comment thoroughly so I don't get confused later on again

	- Consider using Lua to make states instead of hardcoding and linking everything into the StateController.
	  This should be better for game extensibility and flexibility in the long term.
	  (maybe consider using Sol (https://github.com/ThePhD/sol2))
	  * Also research about what should be hardcoded and what should be scripted because I have no idea

	- Make the State object perform rendering calls using its sprite data.
		* a Renderer should only need geometry/texture data to render

	- Put all functions required for every State in the base class, so all derived classes can do their specific stuff.

	- Create audio effect systems.

	- Text (fonts and text color) and sprites should be separated into their own classes, not within Graphics.

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

	- Replace all #pragma onces with #ifndefs for compatibility.

	- When implementing customizable keybinds, how should duplicate keys be handled?
		* obviously they should be prohibited in the first place but how should that be handled

	- The current input system does not properly handle key presses that aren't used in the game.
	  i.e. pressing multiple of those may or may not trigger each PRESS_DOWN/ED/UP as one might expect.

	- How do I handle storing and rendering sprites without intertwining a bunch of headers and classes

	- Optimize collision checking
*/

/*
Not-too-important small notes for the brainrot future me:

	- BPM should be handled by a music-specific class object, not Channels or whatever.

	- Remind myself why recursive animation exists because I don't get the point of it rn

	- When checking for collision of an entity, consider overloading a single collision-checking function
	  with all possible targets - a single point (mouse cursor), a line, convex/concave shapes, etc.
*/