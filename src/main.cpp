#define SDL_MAIN_HANDLED

#include <iostream>
#include <Windows.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

#include "core.h"

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	// Opens the console for debugging purposes.
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	
	srand((unsigned int)time(NULL));

	Core* core = new Core();
	core->loop();

	return 0;
}

/*
TODO:
	player class for user data file save / load
		+ non-messy way to use user data throughout multiple objects

	fix this amalgated mess of object hierarchy communication bullshit

	-- idk do it when you feel like it
	
	-- puzzle ideas
	road direction puzzle

	-- endgame stuff
	Fix "FPS"
	Multithreading on places where it makes sense
	Insert error prompts
	SDL / FMOD licensing check
*/