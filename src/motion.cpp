#include "motion.h"

Motion::Motion(std::string name) : name(_name) {
	init();
}

void Motion::init() {
	function = nullptr;
	startEvent = endEvent = nullptr;
	duration = 0;
	elapsedTime = 0;
	looping = false;
	activeness = false;
}

void Motion::animate() {
	try {
		update();
		checkTriggers();
		if (isActive()) function(geometry, this);
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}

void Motion::updateTime() {
	elapsedTime = Clock::getDeltaTime(initialTime);
	activeness = (elapsedTime <= duration);
}

void Motion::triggerEvents() {
	if (shouldStartEventBeTriggered()) {
		startEvent();
	}
	if (shouldEndEventBeTriggered()) {
		endEvent();
	}
}

bool Motion::shouldStartEventBeTriggered() {
	return (elapsedTime == 0)
		&& (startEvent != nullptr);
}

bool Motion::shouldEndEventBeTriggered() {
	return (elapsedTime >= duration)
		&& (endEvent != nullptr);
}

void Motion::setFunction(MotionFunction _function, ms _duration) {
	function = _function;
	duration = _duration;
}

void Motion::setParameter(std::string name, std::any value) {
	parameters.emplace(name, value);
}

// TODO: check for errors because i have no idea if this works
template <typename T>
T Motion::getParameter<T>(std::string name) {
	try {
		return std::any_cast<T>(parameters.at(name));
	}
	catch (std::out_of_range& e) {
		throw InvalidItemException(name, "parameter");
	}
}