#include "StateSelect.h"

#include "../core.h"
#include "score.h"

StateSelect::StateSelect(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

StateSelect::~StateSelect() {}

void StateSelect::init() {
	selectedGame = -1;

	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	AnimationGroup* ag;
	AnimationEvent* ae;
	Sprite* s;
	SDL_FRect* r;
	int cycle, w, h;

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

	if (tex = g->addTexture("assets/button.png", "testBtn")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ 200, 100, (float)w, (float)h };
		s = g->addSprite("testBtn", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}
}

void StateSelect::update() {}

void StateSelect::exitState(StateType targetState) {
	Graphics* g = core->getGraphics();
	g->deleteSprite("testBtn", _FOREGROUND);
	g->deleteTexture("testBtn");
	sCore->changeState(targetState);
}

void StateSelect::handleClick(std::string name, bool active) {
	Audio* a = core->getAudio();
	if (name == "testBtn" && active) {
		// *vine boom*
		a->playSound("vine", _AUDIO_SFX, 100);
		exitState(_GAME_PAIR);
	}
}