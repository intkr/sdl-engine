#include "StatePrep.h"

#include "../core.h"
#include "score.h"

StatePrep::StatePrep(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

void StatePrep::init() {
	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	AnimationGroup* ag;
	AnimationEvent* ae;
	Sprite* s;
	SDL_FRect* r;
	int w, h;

	if (tex = g->addTexture("assets/stuff.png", "ztuff")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ (1920 - w) / 2 * 0.2f, 1080 - h - (1080 - h) / 2 * 0.333f, (float)w, (float)h };
		s = g->addSprite("ztuff", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			// static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}

	if (tex = g->addTexture("assets/arrow.png", "zarrow")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ 1920.0f - w - 75, 1080.0f - h - 75, (float)w, (float)h };
		s = g->addSprite("zarrow", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			// static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}
}

void StatePrep::update() {}

void StatePrep::exitState(StateType targetState) {
	Graphics* g = core->getGraphics();
	g->deleteSprite("zarrow", _FOREGROUND);
	g->deleteSprite("ztuff", _FOREGROUND);
	sCore->changeState(targetState);
}

void StatePrep::handleClick(std::string name, bool active) {
	Audio* a = core->getAudio();
	if (name == "zarrow" && active) {
		a->playSound("vine", _SFX, 100);
		StateType selectedGame = (StateType)(core->getPlayer()->getValue("selectedGame", true).asInt());
		switch (selectedGame) {
		case _GAME_PAIR:
			exitState(_GAME_PAIR);
			break;
		default:
			// shouldn't happen when properly implemented
			std::cout << ":skull:\n";
			break;
		}
	}
}