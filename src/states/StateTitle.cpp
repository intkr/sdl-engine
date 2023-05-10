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

	float f[4] = { 0, };
	int w, h, animationLength, cycle;
	Animation* a;

	g->addTexture("assets/bg.png", "test");
	g->addSprite(g->getTexture("test"), NULL, NULL, _BACKGROUND, "testbg");
	a = new Animation(true, true, true, staticMotion);
	g->addAnimation("testbg", "bgStatic", a, _INTRO);
	a = new Animation(true, true, true, staticMotion);
	g->addAnimation("testbg", "bgStatic", a, _IDLE);

	g->addTexture("assets/buh.png", "test2");
	SDL_QueryTexture(g->getTexture("test2"), 0, 0, &w, &h);
	SDL_FRect* r = new SDL_FRect{ (float)(rm * (1920 - w) / 2), (float)(rm * (1080 - h) / 2), (float)rm * w, (float)rm * h };
	g->addSprite(g->getTexture("test2"), NULL, r, _FOREGROUND, "testfg");
	// pop out from 0.0x to 1.0x across 30 frames
	f[0] = 0;
	f[1] = 1;
	animationLength = 30;
	g->addAnimation("testfg", "logoPopOut", new Animation(f, animationLength, false, true, false, resizeCenteredMotion), _INTRO);
	// rotate as a sine function across 160 frames, 6 degrees max
	cycle = 80;
	f[0] = 6;
	f[1] = 1.0f / cycle;
	animationLength = 2 * cycle;
	g->addAnimation("testfg", "logoRotation", new Animation(f, animationLength, true, true, false, sinRotation), _IDLE);
	// moves 128 pixels to the left across 24 frames
	cycle = 24;
	f[0] = 1;
	f[1] = (float)rm * 128 / cycle * -1;
	f[2] = 0;
	animationLength = cycle;
	g->addAnimation("testfg", "logoMoveLeft", new Animation(f, animationLength, false, false, true, linearMotion), _IDLE);
	//move in a clockwise circular motion, T = 120 frames
	
	cycle = 120;
	f[0] = 128 * (float)rm;
	f[1] = 1.0f / cycle;
	f[2] = true;
	f[3] = false; // y, sin
	animationLength = 2 * cycle;
	g->addAnimation("testfg", "logoCircularY", new Animation(f, animationLength, true, true, true, sincosMotion), _IDLE);
	f[2] = false;
	f[3] = true; // x, cos
	g->addAnimation("testfg", "logoCircularX", new Animation(f, animationLength, true, true, true, sincosMotion), _IDLE);
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