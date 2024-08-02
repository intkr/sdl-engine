#pragma once
#include <map>
#include <any>
#include <string>

#include "SDL.h"

#include "clock.h"
#include "exception.h"

typedef SDL_FRect(*)(SDL_FRect, MotionFrame&) MotionFunction;

class MotionFrame {
public:
	MotionFrame(MotionFunction _function, ms _duration);

	void reset() { duration = ms(0); }
	SDL_FRect apply(const SDL_FRect& sourceBox, ms delta);

	void setLoop(bool value) { loop = value; }
	void setParameter(std::string name, std::any value);
	
	ms getElapsedTime() { return elapsedTime; }
	template<typename T>
	T getParameter(std::string name);

private:
	void init();
	void updateTime(ms delta);

	MotionFunction function;

	ms elapsedTime;
	ms duration;

	std::map<std::string, std::any> parameters;
};