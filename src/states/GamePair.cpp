//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "GamePair.h"

extern float rm;

GamePair::GamePair(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

GamePair::~GamePair() {}

void GamePair::init() {
	g->reset();

	AnimationGroup* ag;
	AnimationEvent* ae;
	int cycle;

	// background
	g->addTexture("assets/bg.png", "test");
	g->addSprite(g->getTexture("test"), nullptr, nullptr, _BACKGROUND, "testbg");

	//		static motion
	ag = new AnimationGroup(true, false, true);
	g->getSprite("testbg")->addAnimationGroup("idleStatic", _IDLE, ag);

	ae = new AnimationEvent(1, Animations::staticMotion);
	g->getSprite("testbg")->addAnimationEvent("idleStatic", ae);
}

Command GamePair::update() {
	for (auto key : *(i->getPressedKeys())) {

	}

	FMOD::Channel* ch;
	for (auto obj : *(i->getClickedObject())) {
		if (obj.first == "testfg" && obj.second == false) {
			std::string vine = "vine", path = "assets/Vine Boom.ogg";
			ch = a->addSound(path, vine, false, false, _AUDIO_SFX, 100);
			ch->setPaused(false);
			return Command();
		}
	}

	return Command();
}

void GamePair::exitState(Command& cmd) {
}

bool GamePair::isStateRunning() {
	return true;
}