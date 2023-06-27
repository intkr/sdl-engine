#define SDL_MAIN_HANDLED

#include <iostream>
#include <Windows.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

#include "graphics.h"
#include "audio.h"
#include "input.h"
#include "states/stateManager.h"

extern const int fps = 60; // Not actually FPS

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	// remove or add comment to toggle console output for debug purposes
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	
	srand((unsigned int)time(NULL));
	
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	Graphics* g = new Graphics(853, 480);
	Input* i = new Input(g);
	Audio* a = new Audio();
	StateManager* s = new StateManager(_STATE_TITLE, g, i, a);

	SDL_Event _event;
	clock_t frameStartMS, frameEndMS;
	bool gaming = true;
	
	while (gaming) {
		frameStartMS = clock();

		i->process(_event);
		a->update();
		s->update();
		g->renderScreen();

		if (i->isQuitTriggered()) gaming = false;

		frameEndMS = clock();
		if (frameEndMS - frameStartMS < 1000 / fps) {
			SDL_Delay(1000 / fps - (frameEndMS - frameStartMS));
		}
	}

	delete s;
	delete a;
	delete i;
	delete g;
	SDL_Quit();
	return 0;
}

/*
TODO:
	devise a game difficulty calculation formula
	fix sprite opacity changes - especially fade ins and fade outs

	road direction puzzle

	-- idk do it when youf eel like it
	12-key support

	-- endgame stuff
	Fix "FPS"
	Multithreading on places where it makes sense
	Insert error prompts
	SDL / FMOD licensing check
*/