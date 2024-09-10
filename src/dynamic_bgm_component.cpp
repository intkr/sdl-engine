#include "dynamic_bgm_component.h"

void DynamicBGMComponent::addBGMElement(float timing, std::string element) {
    elements.insert(timing, element);
}

void DynamicBGMComponent::update(long count, float subdivision) {
    // tidy up this code later, lazy rn

    float timing = (count % beatsPerBar) + subdivision;

    // points to the first sound element that has not been played yet
    auto iter = elements.upper_bound(lastTimingPoint);
    // if the next sound in line has a timing point later than the given parameter,
    // it should not be played now - i.e. nothing should be played this frame.
    if (iter.first > timing) return;
    
    // The value of 'timing' is modified to properly compare values,
    // in case of situations where the timing point looped back to the beginning.
    if (lastTimingPoint > timing) timing += beatsPerBar;
    // in such cases, this flag variable is used to adjust the iterator's key value.
    bool endReached = false;

    while (iter.first + endReached * beatsPerBar <= timing) {
        // some sound playing code here

        if (++iter == elements.end()) {
            endReached = true;
            iter = elements.begin();
        }
    }

    lastTimingPoint = timing;
}