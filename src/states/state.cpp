#include "state.h"
#include "../graphics.h"
#include "../audio.h"

bool State::isStateRunning() {
	return g->hasSprites() || a->hasSounds();
}

Command State::handleKey(SDL_Scancode key, bool active) { return Command(); }
Command State::handleHover(std::string name) { return Command(); }
Command State::handleClick(std::string name, bool active) { return Command(); }
Command State::handleRelease(std::string name) { return Command(); }
Command State::update() { return Command(); }