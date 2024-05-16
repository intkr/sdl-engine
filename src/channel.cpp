#include "channel.h"

void Channel::play() {
	channel->setPaused(false);
}

void Channel::pause() {
	channel->setPaused(true);
}

void Channel::stop() {
	channel->stop();
}

void Channel::update() {
	if (isActive) {
		// process audio effects here
	}
}

bool Channel::isActive() {
	channel->isPlaying(&active);
	return active;
}

void setLoop(bool active) {
	if (active) channel->setMode(FMOD_LOOP_NORMAL);
	else channel->setMode(FMOD_LOOP_OFF);
}
