#include "animation.h"
#include "sprite.h"

AnimationGroup::~AnimationGroup() {
	for (auto it = animationList.begin(); it != animationList.end();) {
		delete* it;
		it = animationList.erase(it);
	}
}

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
	if (!enabled) return true;

	if (sequential) {
		// Sequential animation group, process the currently playing animation.
		if (animationList[currentAnimation]->animate(sprite)) {
			// Animation has finished, move on to the next one.

			//if (!looping) {
			//	delete animationList[currentAnimation];
			//	animationList.erase(animationList.begin() + currentAnimation--); // subtract 1 as compensation
			//}

			if (++currentAnimation >= animationList.size()) {
				if (looping) {
					reset();
					return false;
				}
				else {
					enabled = false;
					return true;
				}
				currentAnimation *= looping;
				return !looping;
			}
		}
	}
	else {
		bool finished = true;

		for (auto animation = animationList.begin(); animation != animationList.end();) {
			// Non-sequential animation group, iterate through animationList and process them all at once
			if ((*animation)->animate(sprite)) {
				// Animation has finished
				if (looping && enabled) {
					(*animation)->reset();
					finished = false;
				}
			}
			else finished = false;

			animation++;
		}

		if (finished && !looping) {
			enabled = false;
			return true;
		}

		return finished;
	}

	// shouldn't reach here
	return false;
}

void AnimationGroup::reset() {
	currentAnimation = 0;
	for (auto animation : animationList) {
		animation->reset();
	}
}

//////////////////////////////////////////

bool AnimationEvent::animate(Sprite* sprite) {
	f(sprite, this);

	if (++currentFrame >= maxFrames) {
		// Animation has finished
		
		//currentFrame = 0;
		return true;
	}
	return false;
}
