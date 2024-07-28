#pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "motion_frame.h"

class Motion {
public:
	Motion(std::string _name, bool _active = true) : name(_name), active(_active) {}
	bool operator==(const Motion& other) const;

	virtual void reset();
	virtual SDL_FRect apply(const SDL_FRect& box) = 0;
	
	void addMotion(MotionFrame motion);
	MotionFrame* getMotion(std::string name);
	
	virtual void activate();
	void deactivate() { active = false; }

protected:
	bool isActive() { return active; }
	
	void updateTime();
	
private:
	std::vector<MotionFrame> frames;

	std::string name;
	bool active;
	
	Timepoint initialTime;
	ms elapsedTime;
	ms duration;
};

class SequentialAnimation : public Motion {
public:
	SequentialAnimation(std::string _name) : Motion(_name), currentMotion(motions.begin()) {}

	void animate(Geometry& geometry) override;
	void reset() override;
	void activate() override;
	
private:
	void selectNextMotion();

	std::vector<MotionFrame>::iterator currentMotion;
}

class ConcurrentAnimation : public Motion {
public:
	ConcurrentAnimation(bool _recursive = false) : Motion(_name) {}
	
	void animate(Geometry& geometry) override;
}