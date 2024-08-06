#pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "motion_frame.h"

class Motion {
public:
	Motion(std::string _name, bool _active = true) : name(_name), active(true), duration(ms(0)), currentMotion(frames.begin()) {}
	bool operator==(const Motion& other) const;

	void reset();
	// is using ms& a good idea here?
	// this allows the function to change value,
	// which would allow the component to check if there's remaining ms left.
	// however this just seems too simple to be right idk
	SDL_FRect apply(const SDL_FRect& sourceBox, ms& delta);
	
	void addFrame(MotionFrame* frame);

private:
	std::string name;
	bool active;
	ms duration;

	std::vector<MotionFrame*> frames;
	std::vector<MotionFrame*>::iterator currentFrame;

	// maybe add some callback function variables
};