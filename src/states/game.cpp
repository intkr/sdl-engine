#include "game.h"

#include "../core.h"
#include "score.h"

void Game::init() {
	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	AnimationGroup* ag;
	AnimationEvent* ae;
	SDL_FRect* r;
	Sprite* s;
	int w, h;

	// thumbs
	if (tex = g->addTexture("assets/good.png", "good")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ (1920.0f - w) / 2, 1080 * 0.1f, (float)w, (float)h };
		s = g->addSprite("goodjob", _FOREGROUND, new Sprite(tex, nullptr, r));

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


	if (tex = g->addTexture("assets/bad.png", "bad")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ (1920.0f - w) / 2, 1080 * 0.1f, (float)w, (float)h };
		s = g->addSprite("badjob", _FOREGROUND, new Sprite(tex, nullptr, r));

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

	Audio* a = core->getAudio();
	a->addSound("assets/good.ogg", "goodsfx", false, false);
	a->addSound("assets/bad.ogg", "badsfx", false, false);
	a->addSound("assets/yippee.mp3", "combo", false, false);
}

void Game::winLevel() {
	currentCombo++;
	if (currentCombo > maximumCombo) maximumCombo = currentCombo;
	if (currentCombo % 5 == 0) {
		Audio* a = core->getAudio();
		a->playSound("combo", _SFX, 30);
	}

	score += (int)(pow(currentCombo, scoreExponent) * baseScore);
}

void Game::loseLevel() {
	currentCombo = 0;
}