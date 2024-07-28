#pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "motion_frame.h"

// previously animation class

class Motion {
public:
	Motion(std::string _name, bool _active = true) : attribute(_name), duration(ms(0)) {}
	bool operator==(const Motion& other) const;

	virtual void reset();
	// TODO: If delta > duration, there will be leftover time for other motions to perform.
	// Figure out how that information can be notified.
	virtual SDL_FRect apply(const SDL_FRect& sourceBox, ms delta) = 0;
	
	void addFrame(MotionFrame frame);

private:
	Attribute attribute;

	std::vector<MotionFrame> frames;
	ms duration;
};

class SequentialMotion : public Motion {
public:
	SequentialMotion(std::string _name) : Motion(_name), currentMotion(frames.begin()) {}

	void reset() override;
	SDL_FRect apply(const SDL_FRect& sourceBox, ms delta) override;
	
private:
	std::vector<MotionFrame>::iterator currentFrame;
	// ^ idk why i can init to a private base class member im dumb
}

class ConcurrentMotion : public Motion {
public:
	ConcurrentMotion(bool _recursive = false) : Motion(_name) {}
	
	SDL_FRect apply(const SDL_FRect& sourceBox, ms delta) override;
}