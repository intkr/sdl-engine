//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "GamePair.h"

GamePair::GamePair(Graphics* _g, Input* _i, Audio* _a) : Game(_g, _i, _a) {
	init();
}

GamePair::~GamePair() {}

void GamePair::init() {
	gameTimeline = _INTRO;
	displayTimer = 0;
	difficulty = 2;
	remainingPairs = 0;
	lastCard = -1;

	// probably shouldn't comment below but doing it for now
	//g->reset();

	AnimationGroup* ag;
	AnimationEvent* ae;
	SDL_FRect* rect;
	Sprite* s;
	int w, h;

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
		}
	}

	// thumbs
	if (g->addTexture("assets/good.png", "good")) {
		SDL_QueryTexture(g->getTexture("good"), nullptr, nullptr, &w, &h);
		rect = new SDL_FRect{ (1920.0f - w) / 2, 1080 * 0.1f, (float)w, (float)h };
		g->addSprite(g->getTexture("good"), nullptr, rect, _FOREGROUND, "goodjob");
		s = g->getSprite("goodjob");
		if (s != nullptr) {
			//	static motion
			ag = new AnimationGroup(false, false, false);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(60, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
		s->setStatus(_END);
	}

	if (g->addTexture("assets/bad.png", "bad")) {
		SDL_QueryTexture(g->getTexture("good"), nullptr, nullptr, &w, &h);
		rect = new SDL_FRect{ (1920.0f - w) / 2, 1080 * 0.1f, (float)w, (float)h };
		g->addSprite(g->getTexture("bad"), nullptr, rect, _FOREGROUND, "badjob");
		s = g->getSprite("badjob");
		if (s != nullptr) {
			//	static motion
			ag = new AnimationGroup(false, false, false);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(60, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
		s->setStatus(_END);
	}

	// card background
	if (g->addTexture("assets/pair/card-bg.png", "card-bg")) {
		std::string name;
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
	switch (gameTimeline) {
	case _INTRO:
		gameTimeline = _IDLE;
		newPuzzle();
		break;

	case _IDLE:
		switch ((displayTimer > 0) - (displayTimer < 0)) {
		case 0: // timer == 0
			if (!isInteractable()) {
				// hide result image
				g->getSprite("badjob")->toggleAnimationGroup("idleStatic", _IDLE, false);
				g->getSprite("goodjob")->toggleAnimationGroup("idleStatic", _IDLE, false);

				newPuzzle();
			}
			else hideCards();
		case 1: // timer > 0
			displayTimer--;
			break;
		case -1: // timer < 0
		default:
			break;
		}
		break;

	case _OUTRO:
	case _END:
		break;
	}

	return Command();
}

void GamePair::exitState(Command& cmd) {
}

bool GamePair::isStateRunning() {
	return true;
}

Command GamePair::handleClick(std::string name, bool active) {
	// if there's a thumb on display disable clicking
	if (!isInteractable()) return Command();

	if (name == "testfg" && active) {
		newPuzzle();
	}
	size_t pos = name.find("card-bg-");
	if (pos == (size_t)0) { // doesn't check for activeness so you can select cards in one mouse press
		int pickedCard = atoi(name.substr(8).c_str());

		if (!cards[pickedCard].opened) {
			// If there's no card to select, count as a loss
			if (cards[pickedCard].type == -1) loseLevel();
			else {
				// open card
				openCard(pickedCard);

				// handle selected pair
				if (lastCard == -1) {
					lastCard = pickedCard;
				}
				else {
					if (validatePair(lastCard, pickedCard)) {
						//std::cout << name << " pair found.\n";
						if (--remainingPairs == 0) {
							winLevel();
						}
					}
					else {
						loseLevel();
					}

					lastCard = -1;
				}
			}
		}
	}
	return Command();
}

void GamePair::winLevel() {
	std::cout << "yippee\n\n";
	toggleInteractivity(false);
	g->getSprite("goodjob")->toggleAnimationGroup("idleStatic", _IDLE, true);
	g->getSprite("goodjob")->setStatus(_IDLE);
	displayTimer = resultDisplayFrames;
}

void GamePair::loseLevel() {
	std::cout << "nooooo\n\n";
	toggleInteractivity(false);
	g->getSprite("badjob")->toggleAnimationGroup("idleStatic", _IDLE, true);
	g->getSprite("badjob")->setStatus(_IDLE);
	displayTimer = resultDisplayFrames;
}

void GamePair::newPuzzle() {
	deleteCards();
	displayTimer = cardDisplayFrames;
	toggleInteractivity(true);
	lastCard = -1;
	// set cards based on difficulty
	// TODO: this is for test purposes, recalibrate this later
	for (int i = 4 - (int)difficulty; i; i--) {
		cards.push_back(-1);
		cards.push_back(-1);
	}

	int n;
	remainingPairs = (int)difficulty + 2;
	for (int i = remainingPairs; i; i--) {
		n = rand() % cardTypes;
		cards.push_back(n);
		cards.push_back(n);
	}

	// shuffle card positions
	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	
	// create card sprites
	for (int i = _PAIR_WIDTH * _PAIR_HEIGHT; i; i--) {
		createCard(i - 1, cards[i - 1].type);
	}
}

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
		ag = new AnimationGroup(true, true, true);
		if (s->addAnimationGroup("static", _IDLE, ag)) {
			ae = new AnimationEvent(1, Animations::staticMotion);
			s->addAnimationEvent("static", ae);
		}
	}
}

void GamePair::deleteCards() {
	std::string name;
	for (int i = (int)cards.size(); i; i--) {
		if (cards[i - 1].type != -1) {
			name = "card-card-";
			name.append(std::to_string(i - 1));
			g->deleteSprite(name, _FOREGROUND);
		}
	}
	cards.clear();
}

void GamePair::hideCards() {
	std::string name;
	for (int i = (int)cards.size(); i; i--) {
		if (cards[i - 1].type != -1) {
			name = "card-card-";
			name.append(std::to_string(i - 1));
			g->getSprite(name)->toggleAnimationGroup("static", _IDLE, false);
		}
	}
}

void GamePair::openCard(int pos) {
	if (displayTimer > 0) {
		hideCards();
		displayTimer = -1;
	}

	std::string name;
	if (cards[pos].type != -1) {
		cards[pos].opened = true;
		name = "card-card-";
		name.append(std::to_string(pos));
		Sprite* s = g->getSprite(name);
		s->setStatus(_IDLE);
		s->toggleAnimationGroup("static", _IDLE, true);
	}
}

bool GamePair::validatePair(int a, int b) {
	return (cards[a].type == cards[b].type);
}