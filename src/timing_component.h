#pragma once
#include <map>

#include "clock.h"

class TimingComponent {
public:
    TimingComponent() : elapsedTime(ms(0)), currentBeat(0.0f) {}
    void addTimingPoint(float bpm, ms offset);
    void update(ms delta);
    long getBeatCount() { return beatCount; }
    float getBeatSubdivision() { return beatSubdivision; }

private:
    // <offset, bpm>
    std::map<ms, float> timingPoints;
    std::map<ms, float>::iterator currentTiming;

    ms elapsedTime;

    long beatCount;
    float beatSubdivision;
    // maybe add more statistical variables later
}