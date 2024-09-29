#pragma once

#include <map>
#include <string>

// TODO: implement a way to actually call Audio to play sounds

class DynamicBGMComponent {
public:
    void addBGMElement(float timing, std::string element);
    void update(long count, float subdivision);

private:
    std::multimap<float, std::string> elements;
    float lastTimingPoint;
    int beatsPerBar;
};