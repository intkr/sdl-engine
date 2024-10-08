#pragma once

#include "fmod.hpp"
#include "fmod_output.h"
#include "fmod_errors.h"

#include "clock.h"
#include "exceptions.h"

typedef FMOD::Sound Sound;

// Note: if a channel makes a clicking sound at the end of playback, refer to ChannelControl::setMode() documentation
class Channel {
public:
	Channel(FMOD::Channel* ch) : channel(ch), active(false), looping(false) {}
	~Channel() {}
	
	void play();
	void pause();
	void stop();
	void update();
	bool isActive();
	void setLoop(bool active);
	
private:
	FMOD::Channel* channel;
	bool active;
	bool looping;
}