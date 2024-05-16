pragma once
#include <vector>
#include <string>

#include "clock.h"
#include "motion.h"

class Animation {
public:
	Animation(std::string _name, bool _recursive = false)
		: recursive(_recursive), name(_name) {}
	~Animation();
	
	bool operator==(const Animation& other) const;

	virtual void reset();
	virtual void animate(Geometry& geometry) = 0;
	
	void addMotion(Motion* motion);
	Motion* getMotion(std::string name);
	
	virtual void activate();
	void deactivate() { activeness = false; }

protected:
	bool isRecursive() { return recursive; }
	bool isActive() { return activeness; }
	
	void updateTime();
	
private:
	std::vector<Motion*> motions;

	std::string name;
	bool activeness;
	bool recursive;
	
	Timepoint initialTime;
	ms elapsedTime;
	ms duration;
};

class SequentialAnimation : public Animation {
public:
	SequentialAnimation(std::string _name, bool _recursive = false) : Animation(_recursive, _enabled), currentMotion(motions.begin()) {}
	
	void animate(Geometry& geometry) override;
	void reset() override;
	void activate() override;
	
private:
	void selectNextMotion();

	std::vector<Motion*>::iterator currentMotion;
}

class ConcurrentAnimation : public Animation {
public:
	ConcurrentAnimation(bool _recursive = false, bool _enabled = true) : Animation(_recursive, _enabled) {}
	
	void animate(Geometry& geometry) override;
}