#include "motion_frame.h"

MotionFrame::MotionFrame(MotionFunction _function, ms _duration) : function(_function), loop(true),
																   duration(_duration), elapsedTime(ms(0))
																    {}

SDL_FRect MotionFrame::apply(const SDL_FRect& sourceBox, ms delta) {
	try {
		updateTime(delta);
		return function(sourceBox, this);
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}

void MotionFrame::updateTime(ms delta) {
	elapsedTime += delta;
	if (elapsedTime > duration) {
		elapsedTime = duration;
	}
}



void MotionFrame::setParameter(std::string name, std::any value) {
	parameters.emplace(name, value);
}

template <typename T>
T MotionFrame::getParameter<T>(std::string name) {
	try {
		return std::any_cast<T>(parameters.at(name));
	}
	catch (std::out_of_range& e) {
		throw InvalidItemException(name, "parameter");
	}
}