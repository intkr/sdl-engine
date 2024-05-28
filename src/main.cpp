#define SDL_MAIN_HANDLED

#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "system.h"

void openDebugConsole() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	//openDebugConsole();

	System* sys = new System();
	sys->loop();

	return 0;
}

/* reminding progress:
	motion functions <<<< idk if this is really necessary nor good implemention, research into scripting (Lua or wtv)
*/

/*
Stuff I must do before I eventually meltdown:

	- Make a 'Renderer' class that does all the sprite rendering.
	- Make a sprite list in State, and pass the Renderer object to State so it can iterate through sprites and render.
		* a Renderer should only need geometry/texture data to render
	- Allow Entities to group multiple sub-Entities.
	- Put all functions required for every State in the base class, so all derived classes can do their specific stuff
	- Create audio effect systems.
	- Text (fonts and text color) and sprites should be separated into its own class, not within Graphics.
	- Attributes for both sprites and entities, and ones sprite-specific should be separated properly.
*/

/*
Stuff to ponder upon like a sophisticated individual:

	- When implementing customizable keybinds, how should duplicate keys be handled?
		* obviously they should be prohibited in the first place but how should that be handled
	- The current input system does not properly handle key presses that aren't used in the game.
	  i.e. pressing multiple of those may or may not trigger each PRESS_DOWN/ED/UP as one might expect.
	- How do I handle storing and rendering sprites without intertwining a bunch of headers and classes
	- Learn how to script with Lua (maybe consider using Sol (https://github.com/ThePhD/sol2))
*/

/*
Small notes for the brainrot future me:

	- BPM should be handled by a music-specific class object, not Channels or whatever.
	- Remind myself why recursive animation exists because I don't get the point of it rn
	- When checking for collision of an entity, consider overloading a single collision-checking function
	  with all possible targets - a single point (mouse cursor), a line, convex/concave shapes, etc.
*/