//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "../functions.h"

#include "TitleMenu.h"

extern double rm;

TitleMenuState::TitleMenuState(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

TitleMenuState::~TitleMenuState() {}

void TitleMenuState::init() {
	g->reset();

	float f[4] = { 0, };
	int w, h, maxFrames, cycle;
	Animation* a;

	g->addTexture("assets/bg.png", "test");
	g->addSprite(g->getTexture("test"), NULL, NULL, BACKGROUND, "testbg");
	a = new Animation(true, true, true, staticMotion);
	g->addAnimation("testbg", "bgStatic", a, INTRO);
	a = new Animation(true, true, true, staticMotion);
	g->addAnimation("testbg", "bgStatic", a, IDLE);

	g->addTexture("assets/buh.png", "test2");
	SDL_QueryTexture(g->getTexture("test2"), 0, 0, &w, &h);
	SDL_FRect* r = new SDL_FRect{ (float)(rm * (1920 - w) / 2), (float)(rm * (1080 - h) / 2), (float)rm * w, (float)rm * h };
	g->addSprite(g->getTexture("test2"), NULL, r, FOREGROUND, "testfg");
	// pop out from 0.0x to 1.0x across 30 frames
	f[0] = 0;
	f[1] = 1;
	maxFrames = 30;
	g->addAnimation("testfg", "logoPopOut", new Animation(f, maxFrames, false, true, false, resizeCenteredMotion), INTRO);
	// rotate as a sine function across 160 frames, 6 degrees max
	cycle = 80;
	f[0] = 6;
	f[1] = 1.0f / cycle;
	maxFrames = 2 * cycle;
	g->addAnimation("testfg", "logoRotation", new Animation(f, maxFrames, true, true, false, sinRotation), IDLE);
	// moves 128 pixels to the left across 24 frames
	cycle = 24;
	f[0] = 1;
	f[1] = (float)rm * 128 / cycle * -1;
	f[2] = 0;
	maxFrames = cycle;
	g->addAnimation("testfg", "logoMoveLeft", new Animation(f, maxFrames, false, false, true, linearMotion), IDLE);
	//move in a clockwise circular motion, T = 120 frames
	
	cycle = 120;
	f[0] = 128 * (float)rm;
	f[1] = 1.0f / cycle;
	f[2] = true;
	f[3] = false; // y, sin
	maxFrames = 2 * cycle;
	g->addAnimation("testfg", "logoCircularY", new Animation(f, maxFrames, true, true, true, sincosMotion), IDLE);
	f[2] = false;
	f[3] = true; // x, cos
	g->addAnimation("testfg", "logoCircularX", new Animation(f, maxFrames, true, true, true, sincosMotion), IDLE);
	// opacity
	f[0] = 0;
	f[1] = 128;
	maxFrames = 15;
	g->addAnimation("testfg", "logoFadeIn", new Animation(f, maxFrames, false, true, true, opacity), INTRO);
	f[0] = 128;
	maxFrames = 1;
	g->addAnimation("testfg", "logoOpacity", new Animation(f, maxFrames, true, true, true, opacity), IDLE);
	f[0] = 128;
	f[1] = 0;
	maxFrames = 15;
	
	//g->addAnimation("testfg", "logoFadeOut", new Animation(f, maxFrames, false, true, true, opacity), OUTRO);
	//g->addAnimation("testbg", "bgFadeOut", new Animation(f, maxFrames, false, true, true, opacity), OUTRO);
}

int TitleMenuState::update() {
	for (auto key : *(i->getPressedKeys())) {
		if (key.second == false) {
			g->reset();
			return 1;
		}
	}

	//TODO: test if this works
	for (auto obj : *(i->getClickedObject())) {
		if (obj.first == "testfg" && obj.second == false) {
			std::string vine = "vine", path = "assets/Vine Boom.ogg";
			randomizeString(&vine, 3);
			a->addSound(path, vine, 0, 0, 100);
			a->getChannel(vine)->setPaused(false);
			return 1;
		}
	}

	return 0;
}