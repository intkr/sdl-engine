#include "state.h"
#include "../graphics.h"
#include "../audio.h"

State::State(Graphics* _g, Input* _i, Audio* _a) : g(_g), i(_i), a(_a) {}

State::~State() {}

bool State::isStateRunning() {
	return g->hasSprites() || a->hasSounds();
}