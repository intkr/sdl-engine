#include "motion.h"

bool operator==(const Motion& other) const {
	return attribute.name == other.attribute.name;
}

void Motion::reset() {
	for (MotionFrame frame : motions) {
		frame.reset();
	}
}

void SequentialMotion::reset() {
	Motion::reset();
	currentFrame = frames.begin();
}

SDL_FRect SequentialMotion::apply(const SDL_FRect& sourceBox, ms delta) {
	SDL_FRect box = sourceBox;
	while (delta > 0) {
		if (currentFrame == frames.end()) {
			// maybe add callbacks or something here
			return;
		}

		// if delta > current frame length,
			// update box to end of frame
			// delta -= frame length
			// next frame
			// continue
		// if 0 <= delta < current frame length,
			// update box to delta
			// break
		box = currentFrame.apply(box, delta);
		if (delta.count() >= currentFrame.getDuration()) {
			delta -= ms(currentFrame.getDuration());
			currentFrame++;
		}
		else if (delta < currentFrame.getDuration()) {
			break;
		}
	}

	return box;
}

SDL_FRect ConcurrentMotion::apply(const SDL_FRect& box, ms delta) {
	SDL_FRect box = sourceBox;
	bool animatedMotionExists = false;
	
	for (MotionFrame frame : motions) {
		if (frame.isUnfinished()) {
			animatedMotionExists = true;
			box = frame.apply(box, delta);
		}
	}

	// If any of the motions were animated, then this animation is considered active.
	active = animatedMotionExists;

	return box;
}

void Motion::addFrame(MotionFrame frame) {
	// change parameter to actual frame data
	motions.push_back(motion);
}