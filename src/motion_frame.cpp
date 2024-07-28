#include "motion_frame.h"

MotionFrame::MotionFrame(std::string name) : name(_name) {
	init();
}

void MotionFrame::init() {
	function = nullptr;
	startEvent = endEvent = nullptr;
	duration = 0;
	elapsedTime = 0;
	looping = false;
	activeness = false;
}

void MotionFrame::animate() {
	try {
		update();
		checkTriggers();
		if (isActive()) function(geometry, this);
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}

void MotionFrame::updateTime() {
	elapsedTime = Clock::getDeltaTime(initialTime);
	activeness = (elapsedTime <= duration);
}

void MotionFrame::triggerEvents() {
	if (shouldStartEventBeTriggered()) {
		startEvent();
	}
	if (shouldEndEventBeTriggered()) {
		endEvent();
	}
}

bool MotionFrame::shouldStartEventBeTriggered() {
	return (elapsedTime == 0)
		&& (startEvent != nullptr);
}

bool MotionFrame::shouldEndEventBeTriggered() {
	return (elapsedTime >= duration)
		&& (endEvent != nullptr);
}

void MotionFrame::setFunction(MotionFunction _function, ms _duration) {
	function = _function;
	duration = _duration;
}

void MotionFrame::setParameter(std::string name, std::any value) {
	parameters.emplace(name, value);
}

// TODO: check for errors because i have no idea if this works
template <typename T>
T MotionFrame::getParameter<T>(std::string name) {
	try {
		return std::any_cast<T>(parameters.at(name));
	}
	catch (std::out_of_range& e) {
		throw InvalidItemException(name, "parameter");
	}
}