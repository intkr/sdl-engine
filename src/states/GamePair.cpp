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
	scoreExponent = 1.05f;

	difficulty = 0;
	displayTimer = 0;
	remainingPairs = 0;
	lastCard = -1;

	//g->reset();

	AnimationGroup* ag;
	AnimationEvent* ae;
	SDL_FRect* rect;
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
		//SDL_QueryTexture(g->getTexture("card-bg"), nullptr, nullptr, &w, &h);
		w = h = (int)(1080 * 0.1);

		for (int i = _PAIR_HEIGHT; i; i--) {
			for (int j = _PAIR_WIDTH; j; j--) {
				name = "card-bg-";
				name.append(std::to_string((i - 1) * 3 + (j - 1)));
				rect = new SDL_FRect{ (1920 * 0.5f - w * 1.75f) + (j - 1) * (w * 1.25f), (1080 * 0.5f - h * 2.375f) + (i - 1) * (h * 1.25f), (float)w, (float)h };

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
	// TODO: rewrite this goofy code
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
	switch (gameStatus) {
	case _INTRO:
		// TODO: change this into a more proper intro cutscene after more stuff is made
		gameStatus = _IDLE;

		newPuzzle();
		break;

	case _IDLE:
		updateTime();

		// game over condition check
		//if (gameTimer % 60 == 0) std::cout << gameTimer / 60 << " seconds left\n";
		if (gameTimer == 0) {
			gameStatus = _OUTRO;
		}

		// handle display timer
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
		std::cout << "Game over\n";
		gameStatus = _END;
		break;

	case _END:
		Command cmd(_CMD_STATE, (int)_STATE_TITLE);
		exitState(cmd);
		return cmd;
		break;
	}

	return Command();
}

void GamePair::exitState(Command& cmd) {
	g->deleteSprite("goodjob", _FOREGROUND);
	g->deleteSprite("badjob", _FOREGROUND);
	deleteCards();

	g->deleteTexture("good");
	g->deleteTexture("bad");

	std::string name;
	while (cardTypes >= 0) {
		name = "card-card-";
		name.append(std::to_string(cardTypes));
		g->deleteTexture(name);
		cardTypes--;
	}

	for (int i = _PAIR_HEIGHT; i; i--) {
		for (int j = _PAIR_WIDTH; j; j--) {
			name = "card-bg-";
			name.append(std::to_string((i - 1) * 3 + (j - 1)));
			g->deleteSprite(name, _FOREGROUND);
		}
	}
	g->deleteTexture("card-bg");

	std::cout << "Score : " << score << "\tMax combo : " << maximumCombo << "\n";
}

bool GamePair::isStateRunning() {
	return gameStatus != _END;
}

Command GamePair::handleClick(std::string name, bool active) {
	// if there's a thumb on display disable clicking
	if (!isInteractable() || gameStatus != _IDLE) return Command();

	if (name == "testfg" && active) {
		newPuzzle();
	}
	size_t pos = name.find("card-bg-");
	if (pos == (size_t)0) { // doesn't check for activeness so you can select cards in one mouse press
		int pickedCard = atoi(name.substr(8).c_str());

		interactCard(pickedCard);
	}
	return Command();
}

Command GamePair::handleKey(SDL_Scancode key, bool active) {
	if (!isInteractable() || gameStatus != _IDLE) return Command();

	if (key == SDL_SCANCODE_SPACE && active) {
		newPuzzle();
		return Command();
	}

	int cardIndex = i->checkKeybinds(key);
	if (cardIndex != -1) {
		// 12-keys
		interactCard(cardIndex);
	}

	return Command();
}

void GamePair::adjustDifficulty(bool won) {
	/*
	Difficulty : 0.0 ~ 4.99 (x.y)
	x decides the number of pairs (x + 2)
	y decides the number of card types

	Flat difficulty bonus of +0.25 if correct, -1.0 if incorrect.
	Additional bonus if the puzzle is solved fast enough (<0.75s / pair)
	*/
	if (won) {
		float ms = puzzleElapsedFrames / 60.0f / ((int)difficulty + 2);
		difficulty += 0.25f + std::max(1 / (10 * ms) - 1 / 7.5f, 0.0f);
	}
	else difficulty -= 1.0f;

	if (difficulty < 0.0f) difficulty = 0.0f;
	else if (difficulty >= 5.0f) difficulty = 4.9f;

	std::cout << difficulty << "\n";
}

void GamePair::interactCard(int cardPos) {
	if (!cards[cardPos].opened) {
		// If there's no cardPos to select, count as a loss
		if (cards[cardPos].type == -1) loseLevel();
		else {
			// open cardPos
			openCard(cardPos);

			// handle selected pair
			if (lastCard == -1) {
				lastCard = cardPos;
			}
			else {
				if (validatePair(lastCard, cardPos)) {
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

void GamePair::winLevel() {
	Game::winLevel();
	//std::cout << "win\tTime : " << puzzleElapsedFrames << "\tDifficulty : " << difficulty << "\n";
	toggleInteractivity(false);
	adjustDifficulty(true);

	g->getSprite("goodjob")->toggleAnimationGroup("idleStatic", _IDLE, true);
	g->getSprite("goodjob")->setStatus(_IDLE);

	displayTimer = resultDisplayFrames;
}

void GamePair::loseLevel() {
	Game::loseLevel();
	//std::cout << "lose\tTime : " << puzzleElapsedFrames << "\tDifficulty : " << difficulty << "\n";
	toggleInteractivity(false);
	adjustDifficulty(false);

	g->getSprite("badjob")->toggleAnimationGroup("idleStatic", _IDLE, true);
	g->getSprite("badjob")->setStatus(_IDLE);

	displayTimer = resultDisplayFrames;
}

void GamePair::newPuzzle() {
	deleteCards();
	displayTimer = cardDisplayFrames;
	puzzleElapsedFrames = 0;
	toggleInteractivity(true);

	lastCard = -1;

	// insert empty cards
	for (int i = 4 - (int)difficulty; i; i--) {
		cards.push_back(-1);
		cards.push_back(-1);
	}

	// insert cards
	int n;
	int minimumPairs = 3;
	remainingPairs = (int)difficulty + 2;
	for (int i = remainingPairs; i; i--) {
		//n = rand() % (int)((cardTypes - minimumPairs) * (difficulty - (int)difficulty) + minimumPairs);

		// normalize difficulty (0.0 ~ 5.0) to (2 ~ cardTypes);
		n = rand() % (int)(difficulty / 5.0f * (cardTypes - 3) + 3);
		if (n >= cardTypes) std::cout << "wtf " << n << "\n";
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
	//SDL_QueryTexture(g->getTexture(textureName), nullptr, nullptr, &w, &h);
	w = h = (int)(1080 * 0.1);
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