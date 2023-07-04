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

SDL_Texture* Core::strToTexture(std::wstring text, std::string color, int wrapLength) {
	SDL_Surface* textSurface = g->getTextSurface(text, "white", 800);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(g->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);

	return textTexture;
}

SDL_Texture* Core::addTexture(std::string path, std::string name) {
	return g->addTexture(path, name);
}

SDL_Texture* Core::addTexture(SDL_Texture* tex, std::string name) {
	return g->addTexture(tex, name);
}

bool Core::deleteTexture(std::string name) {
	return g->deleteTexture(name);
}

Sprite* Core::addSprite(std::string name, SpriteType type, Sprite* s) {
	return g->addSprite(name, type, s);
}

bool Core::deleteSprite(std::string name, SpriteType type) {
	return g->deleteSprite(name, type);
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

bool Core::addSound(std::string path, std::string name, bool isLoop, bool isStream) {
	return a->addSound(path, name, isLoop, isStream, _AUDIO_SFX, 100);
}

bool Core::playSound(std::string name, AudioType type, int volume) {
	return a->playSound(name, type, volume);
}

bool Core::pauseSound(std::string name) {
	return a->pauseSound(name);
}