#include "clock.h"

Clock* Clock::getClock() {
	if (_clock == nullptr) _clock = new Clock();
	return _clock;
}

void Clock::deleteClock() {
	delete _clock;
}
void Clock::updateTime() {
	frameTimepoint = SteadyClock::now();
}

ms Clock::getDeltaTime(Timepoint from, Timepoint to) {
	return std::chrono::duration_cast<ms>(to - from);
}
