//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "StateTitle.h"

extern double rm;

StateTitle::StateTitle(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

StateTitle::~StateTitle() {}

void StateTitle::init() {
	g->reset();

	AnimationGroup* ag;
	AnimationEvent* ae;
	int cycle;
	// background
	g->addTexture("assets/bg.png", "test");
	g->addSprite(g->getTexture("test"), NULL, NULL, _BACKGROUND, "testbg");

	//		static motion
	ag = new AnimationGroup(true, false);
	g->addAnimationGroup("testbg", "idleStatic", _IDLE, ag);

	ae = new AnimationEvent(1, Animations::staticMotion);
	g->addAnimationEvent("testbg", "idleStatic", ae);

	// test logo
	int w, h;
	g->addTexture("assets/buh.png", "test2");
	SDL_QueryTexture(g->getTexture("test2"), 0, 0, &w, &h);
	SDL_FRect* r = new SDL_FRect{ (float)(rm * (1920 - w) / 2), (float)(rm * (1080 - h) / 2), (float)rm * w, (float)rm * h };
	g->addSprite(g->getTexture("test2"), NULL, r, _FOREGROUND, "testfg");

	// pop out from center of screen
	cycle = 30;
	ag = new AnimationGroup(false, true);
	g->addAnimationGroup("testfg", "introPopOut", _INTRO, ag);
	ae = new AnimationEvent(cycle, Animations::resizeCenteredMotion);
	ae->setFloat("startSize", 0.0);
	ae->setFloat("endSize", 1.0);
	g->addAnimationEvent("testfg", "introPopOut", ae);


	// and move 128 pixels to the left for 24 frames
	cycle = 24;
	ae = new AnimationEvent(cycle, Animations::linearMotion);
	ae->setChar("axis", 'x');
	ae->setBool("baseMove", false);
	ae->setFloat("speed", (float)rm * 128 / cycle * -1);
	g->addAnimationEvent("testfg", "introPopOut", ae);

	// idle in circular rotation / motion
	ag = new AnimationGroup(true, false);
	g->addAnimationGroup("testfg", "idleSpin", _IDLE, ag);
	
		// rotation
	cycle = 80;
	ae = new AnimationEvent(cycle * 2, Animations::sincosRotation);
	ae->setFloat("a", 6);
	ae->setFloat("b", (float)(1.0 / cycle));
	ae->setChar("func", 's');
	g->addAnimationEvent("testfg", "idleSpin", ae);

		// motion (x axis)
	ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
	ae->setFloat("a", 128.0f * rm);
	ae->setFloat("b", 1.0f / cycle);
	ae->setChar("axis", 'x');
	ae->setChar("func", 'c');
	g->addAnimationEvent("testfg", "idleSpin", ae);

		// motion (y axis)
	cycle = 120;
	ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
	ae->setFloat("a", 128.0f * rm);
	ae->setFloat("b", 1.0f / cycle);
	ae->setChar("axis", 'y');
	ae->setChar("func", 's');
	g->addAnimationEvent("testfg", "idleSpin", ae);


	/*
	// opacity
	f[0] = 0;
	f[1] = 128;
	animationLength = 15;
	g->addAnimation("testfg", "logoFadeIn", new Animation(f, animationLength, false, true, true, opacity), _INTRO);
	f[0] = 128;
	animationLength = 1;
	g->addAnimation("testfg", "logoOpacity", new Animation(f, animationLength, true, true, true, opacity), _IDLE);
	f[0] = 128;
	f[1] = 0;
	animationLength = 15;
	
	//g->addAnimation("testfg", "logoFadeOut", new Animation(f, animationLength, false, true, true, opacity), _OUTRO);
	//g->addAnimation("testbg", "bgFadeOut", new Animation(f, animationLength, false, true, true, opacity), _OUTRO);

	*/
}

Command StateTitle::update() {
	for (auto key : *(i->getPressedKeys())) {
		// Trigger screen transition on any key press
		if (key.second == false) {
			g->reset();
			return Command(_CMD_STATE, 1);
		}
	}

	//Note: this works but it's unnecessary now
	for (auto obj : *(i->getClickedObject())) {
		if (obj.first == "testfg" && obj.second == false) {
			std::string vine = "vine", path = "assets/Vine Boom.ogg";
			a->addSound(path, vine, 0, 0, 100);
			a->getChannel(vine)->setPaused(false);
			return Command(_CMD_STATE, 1);
		}
	}

	return Command(_CMD_NONE, 1);
}