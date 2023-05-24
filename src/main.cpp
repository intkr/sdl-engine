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
	//AllocConsole();
	//freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	
	srand((unsigned int)time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	Graphics* g = new Graphics(1280, 720);
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
	Quitting with X button

	Make the pair minigame - utilize TDD for minigame development

	Fix "FPS" so it actually means FPS << fix all animations so that it scales with FPS
		in the meantime, develop with fixed 60fps
	Make coherent error/exception prompts
*/