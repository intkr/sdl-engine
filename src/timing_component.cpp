#include "timing_component.h"

void TimingComponent::addTimingPoint(float bpm, ms offset = ms(0)) {
    if (timingPoints.count(offset) > 0) {
        // A timing point for the given offset has already been added.
        // It will be overriden with the new data.
    }
    timingPoints.insert(offset, bpm);
}

void TimingComponent::update(ms delta) {
    elapsedTime += delta;
    currentTiming = timingPoints.lower_bound(elapsedTime);

    ms offset = currentTiming.first;
    float bpm = currentTiming.second;

    currentBeat = (elapsedTime.count() - offset.count()) / bpm;
    beatCount = (long)std::trunc(currentBeat);
    beatSubdivision = std::modf(currentBeat, &bpm); // bpm is unused here; only to match parameter types.
}