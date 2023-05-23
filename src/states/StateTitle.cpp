//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "StateTitle.h"

StateTitle::StateTitle(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

StateTitle::~StateTitle() {}

void StateTitle::init() {
	g->reset();

	AnimationGroup* ag;
	AnimationEvent* ae;
	int cycle, w, h;
	// background
	if (g->addTexture("assets/bg.png", "test")) {
		if (g->addSprite(g->getTexture("test"), nullptr, nullptr, _BACKGROUND, "testbg")) {
			//		static motion
			ag = new AnimationGroup(true, false, true);
			if (g->addAnimationGroup("testbg", "idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				g->addAnimationEvent("testbg", "idleStatic", ae);
			}
		}
	}

	// test logo
	if (g->addTexture("assets/buh.png", "test2")) {
		SDL_QueryTexture(g->getTexture("test2"), 0, 0, &w, &h);
		SDL_FRect* r = new SDL_FRect{ (1920 - w) * 0.75f, (1080 - h) * 0.5f, (float)w, (float)h };
		if (g->addSprite(g->getTexture("test2"), nullptr, r, _FOREGROUND, "testfg")) {
			// pop out from center of screen
			cycle = 30;
			ag = new AnimationGroup(false, true, true);
			if (g->addAnimationGroup("testfg", "introPopOut", _INTRO, ag)) {
				ae = new AnimationEvent(cycle, Animations::resizeCenteredMotion);
				ae->setFloat("startSize", 0.0);
				ae->setFloat("endSize", 1.0);
				g->addAnimationEvent("testfg", "introPopOut", ae);

				// and move 128 pixels to the left for 24 frames
				cycle = 24;
				ae = new AnimationEvent(cycle, Animations::linearMotion);
				ae->setChar("axis", 'x');
				ae->setBool("baseMove", false);
				ae->setFloat("speed", 128.0f / cycle * -1);
				g->addAnimationEvent("testfg", "introPopOut", ae);
			}
			else delete ag;

			// idle in circular rotation / motion
			ag = new AnimationGroup(true, false, true);
			if (g->addAnimationGroup("testfg", "idleSpin", _IDLE, ag)) {
				// rotation
				cycle = 80;
				ae = new AnimationEvent(cycle * 2, Animations::sincosRotation);
				ae->setFloat("a", 6);
				ae->setFloat("b", (float)(1.0 / cycle));
				ae->setChar("func", 's');
				g->addAnimationEvent("testfg", "idleSpin", ae);

				// motion (x axis)
				cycle = 120;
				ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
				ae->setFloat("a", 128.0f);
				ae->setFloat("b", 1.0f / cycle);
				ae->setChar("axis", 'x');
				ae->setChar("func", 'c');
				g->addAnimationEvent("testfg", "idleSpin", ae);

				// motion (y axis)
				cycle = 120;
				ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
				ae->setFloat("a", 128.0f);
				ae->setFloat("b", 1.0f / cycle);
				ae->setChar("axis", 'y');
				ae->setChar("func", 's');
				g->addAnimationEvent("testfg", "idleSpin", ae);
			}
			else delete ag;

			// low opacity (active when clicked)
			ag = new AnimationGroup(true, false, false);
			if (g->addAnimationGroup("testfg", "idleOpacity", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::opacity);
				ae->setFloat("a", 0.1f);
			}
			else delete ag;
		}
		else {
			delete r;
		}
	}
}

Command StateTitle::update() {
	return Command{ _CMD_NONE, 1 };
}

void StateTitle::exitState(Command& cmd) {
	switch (cmd.value) {
	case _GAME_PAIR:
		freeSpecifics();
		break;
	default:
		freeAll();
	}
}

bool StateTitle::isStateRunning() {
	return test;
}

void StateTitle::freeAll() {
	
}

void StateTitle::freeSpecifics() {
	test = false;
}


Command StateTitle::handleClick(std::string name, bool active) {
	if (name == "testfg" && active) {
		// *vine boom*
		FMOD::Channel* ch;
		std::string vine = "vine", path = "assets/Vine Boom.ogg";
		ch = a->addSound(path, vine, false, false, _AUDIO_SFX, 100);
		ch->setPaused(false);

		return Command{ _CMD_TRANSITION, _GAME_PAIR };
	}
	return Command();
}