#pragma once

#include <chrono>

typedef std::chrono::steady_clock SteadyClock;
typedef SteadyClock::time_point Timepoint;
typedef std::chrono::milliseconds ms;

class Clock {
public:
	static Clock* getClock();
	static void deleteClock();
	
	void updateTime();
	// Returns the starting timepoint of the current frame,
	// which is referred as the "current time" within the engine.
	static Timepoint getTime() { return frameTimepoint; }

	// Returns the difference between two timepoints, calculated as 'to - from'.
	// 'to' is set to the current frame time by default.
	static ms getDeltaTime(Timepoint from, Timepoint to = frameTimepoint;
	
private:
	Clock() : frameTimepoint(0) {}
	static Clock* _clock;
	
	Timepoint frameTimepoint;
}