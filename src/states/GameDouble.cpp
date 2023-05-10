//#include <string.h>

#include "../graphics.h"
#include "../audio.h"
#include "../input.h"

#include "GameDouble.h"

extern double rm;

GameDouble::GameDouble(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a) {
	init();
}

GameDouble::~GameDouble() {}

void GameDouble::init() {
	g->reset();

}

Command GameDouble::update() {
	for (auto key : *(i->getPressedKeys())) {

	}

	for (auto obj : *(i->getClickedObject())) {
		if (obj.first == "testfg" && obj.second == false) {
			std::string vine = "vine", path = "assets/Vine Boom.ogg";
			a->addSound(path, vine, 0, 0, 100);
			a->getChannel(vine)->setPaused(false);
			return Command();
		}
	}

	return Command();
}