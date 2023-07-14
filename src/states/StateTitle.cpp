#include "StateTitle.h"

#include "../core.h"
#include "score.h"


StateTitle::StateTitle(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

StateTitle::~StateTitle() {}

void StateTitle::init() {
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

	// text
	tex = g->getTextTexture(L"°¡³ª´ÙABC", "white", 800);
	if (tex = g->addTexture(tex, "testText")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ 100.0f, 100.0f, (float)w, (float)h };
		s = g->addSprite("txt", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			// static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}

	// test logo
	if (tex = g->addTexture("assets/buh.png", "test2"), 1) {
		SDL_QueryTexture(tex, 0, 0, &w, &h);
		r = new SDL_FRect{ (1920 - w) * 0.75f, (1080 - h) * 0.5f, (float)w, (float)h };
		s = g->addSprite("testfg", _FOREGROUND, new Sprite(tex, nullptr, r));

		if (s != nullptr) {
			// pop out from center of screen
			cycle = 30;
			ag = new AnimationGroup(false, true, true);
			if (s->addAnimationGroup("introPopOut", _INTRO, ag)) {
				ae = new AnimationEvent(cycle, Animations::resizeCenteredMotion);
				ae->setFloat("startSize", 0.0);
				ae->setFloat("endSize", 1.0);
				s->addAnimationEvent("introPopOut", ae);

				// and move 128 pixels to the left for 24 frames
				cycle = 24;
				ae = new AnimationEvent(cycle, Animations::linearMotion);
				ae->setChar("axis", 'x');
				ae->setBool("baseMove", false);
				ae->setFloat("speed", 128.0f / cycle * -1);
				s->addAnimationEvent("introPopOut", ae);
			}
			else delete ag;

			// idle in circular rotation / motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleSpin", _IDLE, ag)) {
				// rotation
				cycle = 80;
				ae = new AnimationEvent(cycle * 2, Animations::sincosRotation);
				ae->setFloat("a", 6);
				ae->setFloat("b", (float)(1.0 / cycle));
				ae->setChar("func", 's');
				s->addAnimationEvent("idleSpin", ae);

				// motion (x axis)
				cycle = 120;
				ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
				ae->setFloat("a", 128.0f);
				ae->setFloat("b", 1.0f / cycle);
				ae->setChar("axis", 'x');
				ae->setChar("func", 'c');
				s->addAnimationEvent("idleSpin", ae);

				// motion (y axis)
				cycle = 120;
				ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
				ae->setFloat("a", 128.0f);
				ae->setFloat("b", 1.0f / cycle);
				ae->setChar("axis", 'y');
				ae->setChar("func", 's');
				s->addAnimationEvent("idleSpin", ae);
			}
			else delete ag;

			// low opacity (active when clicked)
			ag = new AnimationGroup(true, false, false);
			if (s->addAnimationGroup("idleOpacity", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::opacity);
				ae->setFloat("a", 0.1f);
				s->addAnimationEvent("idleOpacity", ae);
			}
			else delete ag;
		}
		else {
			delete r;
		}
	}
	else {
		// if sprite already exists, disable 10% opacity
		s = g->addSprite("testfg", _FOREGROUND, nullptr);
		if (s != nullptr) {
			s->toggleAnimationGroup("idleOpacity", _IDLE, false);
		}
	}

	Audio* a = core->getAudio();
	if (a->addSound("assets/Vine Boom.ogg", "vine", false, false)) {
		
	}
	if (a->addSound("assets/audio.mp3", "testbgm", true, true)) {
		a->playSound("testbgm", _BGM, 10);
	}
	
}

void StateTitle::update() {
	return;
}

void StateTitle::exitState(StateType targetState) {
	switch (targetState) {
	case _GAME_PAIR:
		freeSpecifics();
		break;
	default:
		freeAll();
	}
	sCore->changeState(targetState);
}

void StateTitle::freeAll() {
	Graphics* g = core->getGraphics();
	g->deleteSprite("testfg", _FOREGROUND);
	g->deleteSprite("txt", _FOREGROUND);
}

void StateTitle::freeSpecifics() {
	Graphics* g = core->getGraphics();
	g->addSprite("testfg", _FOREGROUND, nullptr)->toggleAnimationGroup("idleOpacity", _IDLE, true);
	test = false;
}


void StateTitle::handleClick(std::string name, bool active) {
	Audio* a = core->getAudio();
	if (name == "testfg" && active) {
		// *vine boom*
		a->playSound("vine", _SFX, 100);
		exitState(_STATE_SELECT);
	}
	return;
}

void StateTitle::handleKey(SDL_Scancode key, bool active) {
	Audio* a = core->getAudio();
	if (key == SDL_SCANCODE_SPACE && active) {
		a->playSound("vine", _SFX, 100);
		exitState(_STATE_SELECT);
	}
	return;
}