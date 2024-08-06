#include "motion.h"

bool operator==(const Motion& other) const {
	return name == other.name;
}

void Motion::reset() {
	for (MotionFrame* frame : frames) {
		frame.reset();
	}
	currentFrame = frames.begin();
}

void Motion::addFrame(MotionFrame* frame) {
	frames.push_back(frame);
}

SDL_FRect Motion::apply(const SDL_FRect& sourceBox, ms& delta) {
	SDL_FRect box = sourceBox;

	while (delta.count() > 0) {
		if (currentFrame == frames.end()) {
			// maybe add callbacks or something here
			return;
		}

		// Apply motion frame to the source box.
		currentFrame->updateTime(delta);
		box = currentFrame.apply(box);

		// If there's still more time left, move on to the next frame and repeat.
		if (delta.count() > 0) {
			currentFrame++;
		}
		else {
			break;
		}
	}

	return box;
}