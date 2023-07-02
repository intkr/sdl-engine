#include "core.h"

#include "graphics.h"
#include "audio.h"
#include "input.h"
#include "player.h"
#include "states/score.h"

Core::Core() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	p = new Player(this);
	g = new Graphics(this);
	i = new Input(this);
	a = new Audio(this);
	s = new SCore(this);
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

void Core::gaming() {
	const int fps = 60;

	SDL_Event _event;
	clock_t frameStartMS, frameEndMS;
	bool gaming = true;

	p->saveData();

	while (gaming) {
		frameStartMS = clock();

		i->update(_event);
		a->update();
		s->update();
		g->renderScreen();

		if (i->isQuitTriggered()) gaming = false;

		// Limit fps by delaying the game
		frameEndMS = clock();
		if (frameEndMS - frameStartMS < 1000 / fps) {
			SDL_Delay(1000 / fps - (frameEndMS - frameStartMS));
		}
	}
}

std::map<std::string, Sprite*>** Core::getSpriteMaps() {
	return g->_sprites;
}

void Core::handleKey(SDL_Scancode id, bool active) {
	s->handleKey(id, active);
}

void Core::handleHover(std::string objName) {
	s->handleHover(objName);
}

void Core::handleClick(std::string objName, bool active) {
	s->handleClick(objName, active);
}

void Core::handleRelease(std::string objName) {
	s->handleRelease(objName);
}

int Core::checkKeybinds(SDL_Scancode key) {
	return i->checkKeybinds(key);
}