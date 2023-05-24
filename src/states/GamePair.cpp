//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "GamePair.h"

GamePair::GamePair(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

GamePair::~GamePair() {}

void GamePair::init() {
	playing = false;
	displayTimer = 0;
	difficulty = 0;

	// probably shouldn't comment below but doing it for now
	//g->reset();

	AnimationGroup* ag;
	AnimationEvent* ae;
	Sprite* s;
	int cycle, w, h;

	// background
	if (g->addTexture("assets/bg.png", "test")) {
		g->addSprite(g->getTexture("test"), nullptr, nullptr, _BACKGROUND, "testbg");
		s = g->getSprite("testbg");
		if (s != nullptr) {
			//	static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}

	ae = new AnimationEvent(1, Animations::staticMotion);
	g->getSprite("testbg")->addAnimationEvent("idleStatic", ae);
}
		}
	}

	// card background
	if (g->addTexture("assets/pair/card-bg.png", "card-bg")) {
		std::string name;
		SDL_FRect* rect;
		SDL_QueryTexture(g->getTexture("card-bg"), nullptr, nullptr, &w, &h);

		for (int i = _PAIR_HEIGHT; i; i--) {
			for (int j = _PAIR_WIDTH; j; j--) {
				name = "card-bg-";
				name.append(std::to_string((i - 1) * 3 + (j - 1)));
				rect = new SDL_FRect{ (1920 * 0.5f - w * 1.75f) + (j - 1) * (w * 1.25f), (1080 * 0.5f - h * 2.375f) + (i - 1) * (h * 1.25f), (float)w, (float)h};

				g->addSprite(g->getTexture("card-bg"), nullptr, rect, _FOREGROUND, name);
				s = g->getSprite(name);
				if (s != nullptr) {
					ag = new AnimationGroup(true, false, true);
					if (s->addAnimationGroup("static", _IDLE, ag)) {
						ae = new AnimationEvent(1, Animations::staticMotion);
						s->addAnimationEvent("static", ae);
					}
				}
			}
		}
	}

	// actual cards - make and use sprites on gameplay
	// NOTE: rewrite this goofy code
	std::string path, name;
	cardTypes = 0;
	do {
		path = "assets/pair/card-";
		name = "card-card-";
		path.append(std::to_string(cardTypes));
		name.append(std::to_string(cardTypes));
		path.append(".png");
		cardTypes++;
	} while (g->addTexture(path, name));
	cardTypes--;
}

Command GamePair::update() {
	if (!playing) {
		displayTimer = displayFrames;
		playing = true;

		newPuzzle();
	}



	return Command();
}

void GamePair::exitState(Command& cmd) {
}

bool GamePair::isStateRunning() {
	return true;
}

Command GamePair::handleClick(std::string name, bool active) {
	if (name == "testfg" && active) {
		newPuzzle();
	}
	return Command();
}


void GamePair::newPuzzle() {
	deleteCards();
	// set cards based on difficulty
	// NOTE: this is for test purposes, recalibrate this later
	for (int i = 4 - difficulty; i; i--) {
		cards.push_back(-1);
		cards.push_back(-1);
	}

	int n;
	for (int i = difficulty + 2; i; i--) {
		n = rand() % cardTypes;
		cards.push_back(n);
		cards.push_back(n);
	}

	// shuffle card positions
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	
	// create card sprites
	for (int i = _PAIR_WIDTH * _PAIR_HEIGHT; i; i--) {
		createCard(i - 1, cards[i - 1]);
	}
}

void GamePair::exitState(Command& cmd) {
void GamePair::createCard(int pos, int type) {
	if (type == -1) return;
	int w, h;
	AnimationEvent* ae;
	AnimationGroup* ag;

	std::string textureName = "card-card-";
	std::string spriteName = "card-card-";
	textureName.append(std::to_string(type));
	spriteName.append(std::to_string(pos));
	SDL_QueryTexture(g->getTexture(textureName), nullptr, nullptr, &w, &h);
	SDL_FRect* rect;

	rect = new SDL_FRect{ (1920 * 0.5f - w * 1.75f) + (pos % _PAIR_WIDTH) * (w * 1.25f), (1080 * 0.5f - h * 2.375f) + (pos / _PAIR_WIDTH) * (h * 1.25f), (float)w, (float)h };
	g->addSprite(g->getTexture(textureName), nullptr, rect, _FOREGROUND, spriteName);
	Sprite* s = g->getSprite(spriteName);
	if (s != nullptr) {
		ag = new AnimationGroup(true, false, true);
		if (s->addAnimationGroup("static", _IDLE, ag)) {
			ae = new AnimationEvent(1, Animations::staticMotion);
			s->addAnimationEvent("static", ae);
		}
	}
}

void GamePair::deleteCards() {
	std::string name;
	for (int i = (int)cards.size(); i; i--) {
		if (cards[i - 1] != -1) {
			name = "card-card-";
			name.append(std::to_string(i - 1));
			g->deleteSprite(name, _FOREGROUND);
		}
	}
	cards.clear();
}

