#include "motion.h"

bool operator==(const Motion& other) const {
	return attribute.name == other.attribute.name;
}

void Motion::reset() {
	for (MotionFrame frame : motions) {
		frame.reset();
	}
	currentFrame = frames.begin();
}

void Motion::addFrame(MotionFrame& frame) {
	// change parameter to actual frame data
	motions.push_back(motion);
}

SDL_FRect Motion::apply(const SDL_FRect& sourceBox, ms delta) {
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
