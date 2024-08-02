#pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "motion_frame.h"

class Motion {
public:
	Motion(std::string _name, bool _active = true) : attribute(_name), duration(ms(0)), currentMotion(frames.begin()) {}
	bool operator==(const Motion& other) const;

	virtual void reset();
	// TODO: If delta > duration, there will be leftover time for other motions to perform.
	// Figure out how that information can be notified.
	virtual SDL_FRect apply(const SDL_FRect& sourceBox, ms delta) = 0;
	
	void addFrame(MotionFrame& frame);

private:
	Attribute attribute;
	ms duration;

	std::vector<MotionFrame> frames;
	std::vector<MotionFrame>::iterator currentFrame;

	// maybe add some callback function variables
};