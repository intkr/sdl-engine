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
double rm = 0.6666666667; // 1280x720 : 0.6666666667, 1600x900 : 0.8333333333, 1920x1080 : 1.0

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	// remove comment to enable console output
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	srand((unsigned int)time(NULL));

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	Graphics* g = new Graphics((int)(1920 * rm), (int)(1080 * rm));
	Input* i = new Input(g);
	Audio* a = new Audio();
	StateManager* s = new StateManager(1, g, i, a);

	SDL_Event _event;
	clock_t frameStartMS, frameEndMS;
	bool gaming = true;
	
	while (gaming) {
		frameStartMS = clock();

		i->process(_event);
		a->update();
		s->update();
		g->renderScreen();

		frameEndMS = clock();
		if (frameEndMS - frameStartMS < 1000 / fps) {
			SDL_Delay(1000 / fps - (frameEndMS - frameStartMS));
		}
	}

	delete a;
	delete i;
	delete g;
	SDL_Quit();
	return 0;
}

/*
TODO:
	Fix sprite animation code
	
	Fix "FPS" so it actually means FPS << fix all animations so that it scales with FPS
	Fis param in sprite class

*/