#include "StateSelect.h"

#include "../core.h"
#include "score.h"

StateSelect::StateSelect(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

StateSelect::~StateSelect() {}

void StateSelect::init() {
	selectedGame = core->getPlayer()->getValue("selectedGame", true).asInt();

	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	AnimationGroup* ag;
	AnimationEvent* ae;
	Sprite* s;
	SDL_FRect* r;
	int w, h;

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

	// <button name, path>
	
	gameList["pairBtn"] = _GAME_PAIR;

	int index = 0;
	std::string path;
	for (auto it : gameList) {
		path = "assets/";
		path.append(it.first);
		path.append(".png");
		if (tex = g->addTexture(path, it.first)) {
			SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
			r = new SDL_FRect{ 200.0f + (w * 1.2f) * (index / 3), 150.0f + (h * 1.2f) * (index % 3), (float)w, (float)h};
			s = g->addSprite(it.first, _FOREGROUND, new Sprite(tex, nullptr, r));

			if (s != nullptr) {
				ag = new AnimationGroup(true, false, true);
				if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
					ae = new AnimationEvent(1, Animations::staticMotion);
					s->addAnimationEvent("idleStatic", ae);
				}
			}
		}
		index++;
	}
	std::cout << selectedGame << "\n";
	if (selectedGame != -1) {
		if (tex = g->addTexture("assets/btnBorder.png", "zzborder")) {
			SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
			r = new SDL_FRect{ 200.0f + (w * 1.2f) * (selectedGame / 3), 150.0f + (h * 1.2f) * (selectedGame % 3), (float)w, (float)h };
			s = g->addSprite("zzborder", _FOREGROUND, new Sprite(tex, nullptr, r));

			if (s != nullptr) {
				ag = new AnimationGroup(true, false, true);
				if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
					ae = new AnimationEvent(1, Animations::staticMotion);
					s->addAnimationEvent("idleStatic", ae);
				}
			}
		}
	}
}

void StateSelect::update() {}

void StateSelect::exitState(StateType targetState) {
	Graphics* g = core->getGraphics();
	for (auto it : gameList) {
		g->deleteSprite(it.first, _FOREGROUND);
		g->deleteTexture(it.first);
	}
	g->deleteSprite("zzborder", _FOREGROUND);
	sCore->changeState(targetState);
}

void StateSelect::handleHover(std::string name) {
	if (gameList.count(name) > 0) {
		core->getPlayer()->setValue("selectedGame", (int)gameList[name], true);
	}
}

void StateSelect::handleClick(std::string name, bool active) {
	Audio* a = core->getAudio();

	// Minigame buttons
	if (gameList.count(name) > 0 && active) {
		a->playSound("vine", _SFX, 100);

		switch (gameList[name]) {
		case _GAME_PAIR:
			exitState(_STATE_PREP);
			break;
		}
	}
}