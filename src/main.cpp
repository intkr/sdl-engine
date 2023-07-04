#define SDL_MAIN_HANDLED

#include <iostream>
#include <Windows.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

#include "core.h"

//extern const int fps = 60; // Not actually FPS

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	// remove or add comment to toggle console output for debug purposes
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	
	srand((unsigned int)time(NULL));

	Core* game = new Core();
	game->gaming();

	return 0;
}

/*
TODO:
	work on class descriptions and member function comments

	user data file save / load
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