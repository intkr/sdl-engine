#pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "transform.h"
#include "motion_frame.h"

class Motion {
public:
	Motion(std::string _name, bool _active = true) : name(_name), active(true), duration(ms(0)), currentMotion(frames.begin()) {}
	bool operator==(const Motion& other) const;

	void reset();
	// Returns the transform after applying the given time ('delta').
	// The value of 'delta' decreases by the applied amount.
	// In most cases, this means that 'delta' will be equal to 0 by the end of the function -
	// however, if the remaining time of the motion is less than 'delta', then its value will be non-zero.
	Transform apply(const Transform& sourceBox, ms& delta);
	
	void addFrame(MotionFrame* frame);

private:
	std::string name;
	bool active;
	ms duration;

	std::vector<MotionFrame*> frames;
	std::vector<MotionFrame*>::iterator currentFrame;

	// maybe add some callback function variables
};