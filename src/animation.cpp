#include "animation.h"
#include "sprite.h"

bool AnimationGroup::addEvent(AnimationEvent* e) {
	try {
		animationList.push_back(e);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool AnimationGroup::animate(Sprite* sprite) {
	if (sequential) {
		// Sequential animation group, process the currently playing animation.
		if (animationList[currentAnimation]->animate(sprite)) {
			// Animation has finished, move on to the next one.
			// If the animation group doesn't loop, delete the currently finished animation.
			if (!looping) {
				delete animationList[currentAnimation];
				animationList.erase(animationList.begin() + currentAnimation--); // subtract 1 as compensation
			}

			if (++currentAnimation >= animationList.size()) {
				currentAnimation *= looping;
				return !looping;
			}
		}
	}
	else {
		for (auto animation = animationList.begin(); animation != animationList.end();) {
			// Non-sequential animation group, iterate through animationList and process them all at once
			if ((*animation)->animate(sprite)) {
				// Animation has finished.
				// If the animation group doesn't loop, delete the currently finished animation.
				if (!looping) {
					delete *animation;
					animation = animationList.erase(animation);
				}
			}
		}

		return (animationList.size() == 0);
	}

	return false;
}


bool AnimationEvent::animate(Sprite* sprite) {
	f(sprite, this);

	// When animation is finished, reset frame counter to 0
	if (++currentFrame >= animationLength) {
		currentFrame = 0;
		return true;
	}
	return false;
}
