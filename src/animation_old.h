#pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "motion.h"

// temporary "old" file while I make yet another renovation to the system
class Animation {
public:
	Animation(std::string _name) : name(_name), active(true) {}
	~Animation();
	
	bool operator==(const Animation& other) const;

	virtual void reset();
	virtual void animate(Geometry& geometry) = 0;
	
	void addMotion(Motion* motion);
	Motion* getMotion(std::string name);
	
	virtual void activate();
	void deactivate() { active = false; }

protected:
	bool isActive() { return active; }
	
	void updateTime();
	
private:
	std::vector<Motion*> motions;

	std::string name;
	bool active;
	
	Timepoint initialTime;
	ms elapsedTime;
	ms duration;
};

class SequentialAnimation : public Animation {
public:
	SequentialAnimation(std::string _name) : Animation(_name), currentMotion(motions.begin()) {}

	void animate(Geometry& geometry) override;
	void reset() override;
	void activate() override;
	
private:
	void selectNextMotion();

	std::vector<Motion*>::iterator currentMotion;
}

class ConcurrentAnimation : public Animation {
public:
	ConcurrentAnimation(bool _recursive = false) : Animation(_name) {}
	
	void animate(Geometry& geometry) override;
}