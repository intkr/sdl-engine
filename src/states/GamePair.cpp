//#include <string.h>
#include "GamePair.h"

#include "../core.h"
#include "score.h"


GamePair::GamePair(SCore* _score, Core* _core) : Game(_score, _core) {
	init();
}

GamePair::~GamePair() {}

void GamePair::init() {
	scoreExponent = 1.05f;

	difficulty = 0;
	displayTimer = 0;
	remainingPairs = 0;
	lastCard = -1;

	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	AnimationGroup* ag;
	AnimationEvent* ae;
	SDL_FRect* r;
	Sprite* s;
	int w, h;

	Game::init();

	// background
	if (tex = g->addTexture("assets/bg.png", "test")) {
		s = g->addSprite("testbg", _BACKGROUND, new Sprite(tex, nullptr, nullptr));

		if (s != nullptr) {
			// static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}

	// card background
	if (tex = g->addTexture("assets/pair/card-bg.png", "card-bg")) {
		std::string name;
		//SDL_QueryTexture(g->getTexture("card-bg"), nullptr, nullptr, &w, &h);
		w = h = (int)(1080 * 0.1);

		for (int i = _PAIR_HEIGHT; i; i--) {
			for (int j = _PAIR_WIDTH; j; j--) {
				name = "card-bg-";
				name.append(std::to_string((i - 1) * 3 + (j - 1)));
				r = new SDL_FRect{ (1920 * 0.5f - w * 1.75f) + (j - 1) * (w * 1.25f), (1080 * 0.5f - h * 2.375f) + (i - 1) * (h * 1.25f), (float)w, (float)h };
				s = g->addSprite(name, _FOREGROUND, new Sprite(tex, nullptr, r));

				if (s != nullptr) {
					ag = new AnimationGroup(true, false, true);
					if (s->addAnimationGroup("static", _IDLE, ag)) {
						ae = new AnimationEvent(1, Animations::staticMotion);
						s->addAnimationEvent("static", ae);
					}

					ag = new AnimationGroup(false, false, false);
					if (s->addAnimationGroup("show", _IDLE, ag)) {
						ae = new AnimationEvent(6, Animations::linearScale);
						ae->setChar("axis", 'w');
						ae->setFloat("a", 0.0f);
						ae->setFloat("b", (float)w);
						ae->setBool("centered", true);
						s->addAnimationEvent("show", ae);
					}

					ag = new AnimationGroup(false, false, false);
					if (s->addAnimationGroup("hide", _IDLE, ag)) {
						ae = new AnimationEvent(6, Animations::linearScale);
						ae->setChar("axis", 'w');
						ae->setFloat("a", (float)w);
						ae->setFloat("b", 0.0f);
						ae->setBool("centered", true);
						s->addAnimationEvent("hide", ae);
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

void GamePair::update() {
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
				Graphics* g = core->getGraphics();
				g->addSprite("badjob",  _FOREGROUND, nullptr)->toggleAnimationGroup("idleStatic", _IDLE, false);
				g->addSprite("goodjob", _FOREGROUND, nullptr)->toggleAnimationGroup("idleStatic", _IDLE, false);

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
		exitState(_STATE_TITLE);
		break;
	}

	return;
}

void GamePair::exitState(StateType targetState) {
	Graphics* g = core->getGraphics();
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

	sCore->changeState(_STATE_TITLE);
}

void GamePair::handleClick(std::string name, bool active) {
	// if there's a thumb on display disable clicking
	if (!isInteractable() || gameStatus != _IDLE) return;

	if (name == "testfg" && active) {
		newPuzzle();
	}
	size_t pos = name.find("card-bg-");
	if (pos == (size_t)0) { // doesn't check for activeness so you can select cards in one mouse press
		int pickedCard = atoi(name.substr(8).c_str());

		interactCard(pickedCard);
	}
}

void GamePair::handleKey(SDL_Scancode key, bool active) {
	if (!isInteractable() || gameStatus != _IDLE) return;

	Audio* a = core->getAudio();
	if (key == SDL_SCANCODE_SPACE && active) {
		a->playSound("vine", _AUDIO_SFX, 100);
		newPuzzle();
		return;
	}

	Input* i = core->getInput();
	int cardIndex = i->checkKeybinds(key);
	if (cardIndex != -1) {
		// 12-keys
		interactCard(cardIndex);
	}
}

void GamePair::adjustDifficulty(bool win) {
	/*
	Difficulty : 0.0 ~ 4.99 (x.y)
	x decides the number of pairs (x + 2)
	y decides the number of card types

	Flat difficulty bonus of +0.25 if correct, -1.0 if incorrect.
	Additional bonus if the puzzle is solved fast enough (< 0.75s / pair)
	*/
	if (win) {
		float ms = puzzleElapsedFrames / 60.0f / ((int)difficulty + 2);
		difficulty += 0.25f + (max(1 / (10 * ms) - 1 / 7.5f, 0.0f));
	}
	else difficulty -= 1.0f;

	if (difficulty < 0.0f) difficulty = 0.0f;
	else if (difficulty >= 5.0f) difficulty = 4.9f;

	std::cout << difficulty << "\n";
}

void GamePair::interactCard(int pos) {
	if (!cards[pos].opened) {
		// If there's no pos to select, count as a loss
		if (cards[pos].type == -1) loseLevel();
		else {
			// open pos
			openCard(pos);

			// handle selected pair
			if (lastCard == -1) {
				lastCard = pos;
			}
			else {
				if (validatePair(lastCard, pos)) {
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

	Graphics* g = core->getGraphics();
	g->addSprite("goodjob", _FOREGROUND, nullptr)->toggleAnimationGroup("idleStatic", _IDLE, true);
	g->addSprite("goodjob", _FOREGROUND, nullptr)->setStatus(_IDLE);

	Audio* a = core->getAudio();
	a->playSound("goodsfx", _AUDIO_SFX, 30);

	displayTimer = resultDisplayFrames;
}

void GamePair::loseLevel() {
	Game::loseLevel();
	//std::cout << "lose\tTime : " << puzzleElapsedFrames << "\tDifficulty : " << difficulty << "\n";
	toggleInteractivity(false);
	adjustDifficulty(false);
	
	Graphics* g = core->getGraphics();
	g->addSprite("badjob", _FOREGROUND, nullptr)->toggleAnimationGroup("idleStatic", _IDLE, true);
	g->addSprite("badjob", _FOREGROUND, nullptr)->setStatus(_IDLE);

	Audio* a = core->getAudio();
	a->playSound("badsfx", _AUDIO_SFX, 30);

	displayTimer = resultDisplayFrames;
}

void GamePair::newPuzzle() {
	deleteCards();
	displayTimer = cardDisplayFrames;
	puzzleElapsedFrames = 0;
	toggleInteractivity(true);

	lastCard = -1;

	// reset card background
	Graphics* g = core->getGraphics();
	std::string name;
	Sprite* s;
	for (int i = 0; i < _PAIR_HEIGHT * _PAIR_WIDTH; i++) {
		name = "card-bg-";
		name.append(std::to_string(i));
		s = g->addSprite(name, _FOREGROUND, nullptr);
		s->resetDstRect();
	}

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
	Graphics* g = core->getGraphics();

	std::string textureName = "card-card-";
	std::string spriteName = "card-card-";
	textureName.append(std::to_string(type));
	spriteName.append(std::to_string(pos));

	//SDL_QueryTexture(g->getTexture(textureName), nullptr, nullptr, &w, &h);
	w = h = (int)(1080 * 0.1);
	SDL_FRect* r;
	SDL_Texture* tex = g->addTexture(nullptr, textureName);
	r = new SDL_FRect{ (1920 * 0.5f - w * 1.75f) + (pos % _PAIR_WIDTH) * (w * 1.25f), (1080 * 0.5f - h * 2.375f) + (pos / _PAIR_WIDTH) * (h * 1.25f), (float)w, (float)h };
	Sprite* s = g->addSprite(spriteName, _FOREGROUND, new Sprite(tex, nullptr, r));
	
	if (s != nullptr) {
		ag = new AnimationGroup(true, true, true);
		if (s->addAnimationGroup("static", _IDLE, ag)) {
			ae = new AnimationEvent(1, Animations::staticMotion);
			s->addAnimationEvent("static", ae);
		}

		ag = new AnimationGroup(false, false, false);
		if (s->addAnimationGroup("hide", _IDLE, ag)) {
			ae = new AnimationEvent(6, Animations::linearScale);
			ae->setChar("axis", 'w');
			ae->setFloat("a", (float)w);
			ae->setFloat("b", 0.0f);
			ae->setBool("centered", true);
			s->addAnimationEvent("hide", ae);
		}

		ag = new AnimationGroup(false, false, false);
		if (s->addAnimationGroup("show", _IDLE, ag)) {
			ae = new AnimationEvent(6, Animations::linearScale);
			ae->setChar("axis", 'w');
			ae->setFloat("a", 0.0f);
			ae->setFloat("b", (float)w);
			ae->setBool("centered", true);
			s->addAnimationEvent("show", ae);
		}
	}
}

void GamePair::deleteCards() {
	Graphics* g = core->getGraphics();
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
	Graphics* g = core->getGraphics();
	std::string name;
	for (int i = (int)cards.size(); i; i--) {
		if (cards[i - 1].type != -1) {
			name = "card-card-";
			name.append(std::to_string(i - 1));
			g->addSprite(name, _FOREGROUND, nullptr)->toggleAnimationGroup("static", _IDLE, false);
			g->addSprite(name, _FOREGROUND, nullptr)->toggleAnimationGroup("hide", _IDLE, true);
			name = "card-bg-";
			name.append(std::to_string(i - 1));
			g->addSprite(name, _FOREGROUND, nullptr)->toggleAnimationGroup("show", _IDLE, true);
		}
	}
}

void GamePair::openCard(int pos) {
	if (displayTimer > 0) {
		hideCards();
		displayTimer = -1;
	}

	Graphics* g = core->getGraphics();
	std::string name;
	if (cards[pos].type != -1) {
		cards[pos].opened = true;
		name = "card-card-";
		name.append(std::to_string(pos));
		Sprite* s = g->addSprite(name, _FOREGROUND, nullptr);
		s->setStatus(_IDLE);
		s->toggleAnimationGroup("static", _IDLE, true);
		s->toggleAnimationGroup("show", _IDLE, true);

		name = "card-bg-";
		name.append(std::to_string(pos));
		s = g->addSprite(name, _FOREGROUND, nullptr);
		s->toggleAnimationGroup("hide", _IDLE, true);
	}
}

bool GamePair::validatePair(int a, int b) {
	return (cards[a].type == cards[b].type);
}