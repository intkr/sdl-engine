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
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
		s->setStatus(_END);
	}

	// timer bar
	if (tex = g->addTexture("assets/bar_outline.png", "bar-line")) {
		// outline
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ (1920.0f - w) / 2, 1080.0f * 0.9f - h * 0.5f, (float)w, (float)h};
		s = g->addSprite("bar-line", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			//	static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
		// fill
		if (tex = g->addTexture("assets/bar_fill.png", "bar-fill")) {
			SDL_QueryTexture(tex, nullptr, nullptr, &barWidth, &barHeight);
			r = new SDL_FRect{ (1920.0f - barWidth) / 2, 1080.0f * 0.9f - barHeight * 0.5f, (float)barWidth, (float)barHeight };
			SDL_Rect* srcRect = new SDL_Rect{ 0, 0, barWidth, barHeight };
			s = g->addSprite("bar-fill", _FOREGROUND, new Sprite(tex, srcRect, r));

			if (s != nullptr) {
				//	static motion
				ag = new AnimationGroup(true, false, true);
				if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
					ae = new AnimationEvent(1, Animations::staticMotion);
					s->addAnimationEvent("idleStatic", ae);
				}
			}	
		}
	}

	// timer text
	if (tex = g->addTexture(g->getTextTexture(L" ", "white", 200), "timer-text")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ (1920.0f - w) / 2, 1080.0f * 0.9f - h * 0.5f, (float)w, (float)h };
		s = g->addSprite("timer-text", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			//	static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}


	Audio* a = core->getAudio();
	a->addSound("assets/good.ogg", "goodsfx", false, false);
	a->addSound("assets/bad.ogg", "badsfx", false, false);
	a->addSound("assets/yippee.mp3", "combo", false, false);
}

void Game::update() {
	updateTimer();
	updateTime();
}

void Game::updateTimer() {
	Graphics* g = core->getGraphics();
	Sprite* s;
	SDL_Texture* tex;
	SDL_FRect* dstRect;
	SDL_Rect* srcRect;

	// update timer bar
	s = g->getSprite("bar-fill");
	dstRect = s->getDstRect();
	srcRect = s->getSrcRect();

	srcRect->w = (int)(barWidth * (min(1.0f, gameTimer / 3600.0f)));
	dstRect->w = barWidth * (min(1.0f, (float)gameTimer / 3600));

	// update timer text
	if (gameTimer % 60 == 0) {
		s = g->getSprite("timer-text");
		tex = g->getTextTexture(std::to_wstring(gameTimer / 60), "white", 200);
		s->setTexture(tex);
		int w, h;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		dstRect = s->getDstRect();
		dstRect->w = (float)w, dstRect->h = (float)h;
		dstRect->x = (1920.0f - w) / 2.0f;
		dstRect->y = 1080.0f * 0.9f - h / 2.0f;
	}
}

void Game::updateTime() {
	gameTimer--;
	gameElapsedFrames++;
	puzzleElapsedFrames++;

	if (gameTimer == 0) setStatus(_OUTRO);
}

void Game::exitState(StateType targetState) {
	Graphics* g = core->getGraphics();
	g->deleteSprite("goodjob", _FOREGROUND);
	g->deleteSprite("badjob", _FOREGROUND);
	g->deleteSprite("timer-text", _FOREGROUND);
	g->deleteSprite("bar-line", _FOREGROUND);
	g->deleteSprite("bar-fill", _FOREGROUND);

	g->deleteTexture("good");
	g->deleteTexture("bad");
	g->deleteTexture("timer-text");
	g->deleteTexture("bar-line");
	g->deleteTexture("bar-fill");

	core->getPlayer()->setValue("score", score, true);
	core->getPlayer()->setValue("maxCombo", maximumCombo, true);
}

void Game::winLevel() {
	currentCombo++;
	if (currentCombo > maximumCombo) maximumCombo = currentCombo;
	if (currentCombo % 5 == 0) {
		Audio* a = core->getAudio();
		a->playSound("combo", _SFX, 30);
		gameTimer += 5 * 60;
		updateTimer();
	}

	score += (int)(pow(currentCombo, scoreExponent) * baseScore);
}

void Game::loseLevel() {
	currentCombo = 0;
}