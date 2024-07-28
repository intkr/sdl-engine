#pragma once
#include <map>
#include <any>
#include <string>

#include "clock.h"
#include "geometry.h"
#include "exception.h"

typedef void(*)(Geometry*, MotionFrame*) MotionFunction;

class MotionFrame {
public:
	MotionFrame(std::string _name);
	
	void animate(Geometry* target);
	void reset() { initialTime = Clock::getTime(); }
	void enableLoop() { looping = true; }

	void setFunction(MotionFunction _function, ms _duration);
	void setParameter(std::string name, std::any value);
	void setStartEvent(void(*f)()) { startEvent = f; }
	void setEndEvent(void(*f)()) { endEvent = f; }
	
	std::string getName() { return name; }
	ms getElapsedTime() { return elapsedTime; }
	ms getDuration() { return duration; }
	
	template<typename T>
	T getParameter(std::string name);


private:
	void init();
	void updateTime();
	
	void triggerEvents();
	bool shouldStartEventBeTriggered();
	bool shouldEndEventBeTriggered();
	
	bool isActive() { return active; }
	
	MotionFunction function;

	Timepoint initialTime;
	ms elapsedTime;
	ms duration;
	
	std::string name;
	bool activeness;
	bool looping;
	
	void (*startEvent)();
	void (*endEvent)();

	std::map<std::string, std::any> parameters;
};