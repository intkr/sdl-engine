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
	// Returns the "current" time - at which the current frame started.
	static Timepoint getTime() { return frameTimepoint; }

	// Calculated as 'to - from'.
	// 'to' defaults to the current time.
	static ms getDeltaTime(Timepoint from, Timepoint to = frameTimepoint;
	
private:
	Clock() : frameTimepoint(0) {}
	static Clock* _clock;
	
	Timepoint frameTimepoint;
}