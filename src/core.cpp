#include "core.h"

Core::Core() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	p = new Player(this);
	g = new Graphics(this);
	i = new Input(this);
	a = new Audio(this);
	s = new SCore(this);

	gaming = true;
}

Core::~Core() {
	delete p;
	delete s;
	delete a;
	delete i;
	delete g;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Core::loop() {
	const int fps = 60;
	clock_t frameStartMS, frameEndMS;

	while (gaming) {
		frameStartMS = clock();

		i->update();
		a->update();
		s->update();
		g->renderScreen();

		// Limit fps by delaying the game
		frameEndMS = clock();
		if (frameEndMS - frameStartMS < 1000 / fps) {
			SDL_Delay(1000 / fps - (frameEndMS - frameStartMS));
		}
	}
}
