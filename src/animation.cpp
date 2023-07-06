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
		if (animationList[currentAnimation]->animate(sprite)) {
			if (++currentAnimation >= animationList.size()) {
				if (looping && enabled) {
					reset();
					return false;
				}
				else {
					enabled = false;
					return true;
				}
				//currentAnimation *= looping;
				//return !looping;
			}
		}
		return false;
	}
	else {
		bool finished = true;

		for (auto animation = animationList.begin(); animation != animationList.end();) {
			if ((*animation)->animate(sprite)) {
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
}

void AnimationGroup::reset() {
	currentAnimation = 0;
	for (auto animation : animationList) {
		animation->reset();
	}
}

void AnimationGroup::enableGroup() {
	enabled = true;
	for (auto e : animationList) {
		e->reset();
	}
}

//////////////////////////////////////////

bool AnimationEvent::animate(Sprite* sprite) {
	f(sprite, this);

	if (++currentFrame > maxFrames) {
		// Animation has finished
		
		//currentFrame = 0;
		return true;
	}
	return false;
}

bool AnimationEvent::setBool(std::string name, bool value) {
	if (paramBool.count(name) > 0) {
		std::cout << "Failed to set bool parameter \"" << name << "\". (Duplicate parmeter name)\n";
		return false;
	}
	paramBool[name] = value;
	return true;
}

bool AnimationEvent::setChar(std::string name, char value) {
	if (paramChar.count(name) > 0) {
		std::cout << "Failed to set char parameter \"" << name << "\". (Duplicate parmeter name)\n";
		return false;
	}
	paramChar[name] = value;
	return true;
}

bool AnimationEvent::setFloat(std::string name, float value) {
	if (paramFloat.count(name) > 0) {
		std::cout << "Failed to set float parameter \"" << name << "\". (Duplicate parmeter name)\n";
		return false;
	}
	paramFloat[name] = value;
	return true;
}

bool AnimationEvent::getBool(std::string name) {
	if (paramBool.count(name) == 0) {
		std::cout << "Failed to get bool parameter \"" << name << "\". (Invalid parmeter name)\n";
		return false;
	}
	return paramBool[name];
}


char AnimationEvent::getChar(std::string name) {
	if (paramChar.count(name) == 0) {
		std::cout << "Failed to get char parameter \"" << name << "\". (Invalid parmeter name)\n";
		return '\0';
	}
	return paramChar[name];
}

float AnimationEvent::getFloat(std::string name) {
	if (paramFloat.count(name) == 0) {
		std::cout << "Failed to get float parameter \"" << name << "\". (Invalid parmeter name)\n";
		return 0.0f;
	}
	return paramFloat[name];
}