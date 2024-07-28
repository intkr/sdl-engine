#include "motion.h"

Motion::~Motion() {
	for (auto motion : motions) {
		delete motion;
	}
}

bool operator==(const Motion& other) const {
	return name == other.name;
}

void Motion::addMotion(MotionFrame* motion) {
	if (motion == nullptr) {
		throw InvalidItemException("nullptr", "motion");
	}
	motions.push_back(motion);
}

MotionFrame* Motion::getMotion(std::string name) {
	for (MotionFrame* motion : motions) {
		if (motion->getName() == name)
		return motion;
	}
	throw InvalidItemException(name, "motion");
}

void SequentialAnimation::animate(Geometry& geometry) {
	ms delta = Clock::getDeltaTime(elapsedTime);
	
	MotionFrame* motion = *currentMotion;
	while (delta.count() > 0) {
		
	}
	
	if (motion->isActive()) {
		
		motion.animate(geometry);
	}
	else selectNextMotion();
}

void ConcurrentAnimation::animate(Geometry& geometry) {
	bool animatedMotionExists = false;
	
	for (MotionFrame* motion : motions) {
		if (motion.isActive()) {
			animatedMotionExists = true;
			motion.animate(geometry);
		}
	}
	
	// If any of the motions were animated, then this animation is considered active.
	active = animatedMotionExists;
}

void SequentialAnimation::selectNextMotion() {
	currentMotion++;
	if (currentMotion == motions.end()) deactivate();
}

void Motion::reset() {
	initialTime = Clock::getTime();
	for (auto motion : motions) {
		motion->reset();
	}
}

void SequentialAnimation::reset() {
	Motion::reset();
	currentMotion = motions.begin();
}

void Motion::activate() {
	active = true;
	reset();
}

void SequentialAnimation::activate() {
	// me when when
	active = true;
	reset();
}

void Motion::updateTime() {
	elapsedTime = Clock::getDeltaTime(initialTime);
	active = (elapsedTime <= duration);
}
