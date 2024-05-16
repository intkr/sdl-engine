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


/*
Stuff I must do before I eventually meltdown:

	- Make a 'Renderer' class that does all the sprite rendering.
	- Make a sprite list in State, and pass the Renderer object to State so it can iterate through sprites and render.
		* a Renderer should only need geometry/texture data to render
	- Allow Entities to group multiple sub-Entities
	- Put all functions required for every State in the base class, so all derived classes can do their specific stuff
*/

/*
Puzzle ideas:
	road direction puzzle
	dance puzzle

Notes:
	- Need a better name than 'Motion' for the namespace used by all animating functions
Important notes:
	- The input data (more specifically, keyStatus and mouseStatus) needs to be 
	  reset when the State changes (or any equivalent action) to prevent any
	  unintended input triggers.
	  
	  By such logic, "Half-presses" should be considered equally as not having any 
	  input at all - therefore, there needs an additional check for keyUps to see if 
	  there's input data for keyDown already
	  (if not, keyUp is invalid)
	  
	- If collision checks take too much time, consider saving the hitbox region of the sprites as the width and height of the entity - which would 
	  then be used to compare with the distance between the entity's center and the 
	  cursor.
*/
