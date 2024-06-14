#include "animation.h"
#include "sprite.h"

Animation::~Animation() {
	for (auto motion : motions) {
		delete motion;
	}
}

bool operator==(const Animation& other) const {
	return name == other.name;
}

void Animation::addMotion(Motion* motion) {
	if (motion == nullptr) {
		throw InvalidItemException("nullptr", "motion");
	}
	motions.push_back(motion);
}

Motion* Animation::getMotion(std::string name) {
	for (Motion* motion : motions) {
		if (motion->getName() == name)
		return motion;
	}
	throw InvalidItemException(name, "motion");
}

void SequentialAnimation::animate(Geometry& geometry) {
	ms delta = Clock::getDeltaTime(elapsedTime);
	
	Motion* motion = *currentMotion;
	while (delta.count() > 0) {
		
	}
	
	if (motion->isActive()) {
		
		motion.animate(geometry);
	}
	else selectNextMotion();
}

void ConcurrentAnimation::animate(Geometry& geometry) {
	bool animatedMotionExists = false;
	
	for (Motion* motion : motions) {
		if (motion.isActive()) {
			animatedMotionExists = true;
			motion.animate(geometry);
		}
	}
	
	// If any of the motions were animated, then this animation is considered active.
	activeness = animatedMotionExists;
}

void SequentialAnimation::selectNextMotion() {
	currentMotion++;
	if (currentMotion == motions.end()) deactivate();
}

void Animation::reset() {
	initialTime = Clock::getTime();
	for (auto motion : motions) {
		motion->reset();
	}
}

void SequentialAnimation::reset() {
	Animation::reset();
	currentMotion = motions.begin();
}

void Animation::activate() {
	activeness = true;
	reset();
}

void SequentialAnimation::activate() {
	// me when when
	activeness = true;
	reset();
}

void Animation::updateTime() {
	elapsedTime = Clock::getDeltaTime(initialTime);
	activeness = (elapsedTime <= duration);
}
