#pragma once

#include <vector>

#include "clock.h"

struct AnimationFrame {
    int row;
    int column;
    ms duration;
};

class Animation {
public:
    Animation(std::string _name) : name(_name) {}
    
    // The base box data is used to calculate
    // all sprite positions for a given animation.
    void setBaseBoxValues(int x, int y, int w, int h);

    void update(ms delta);
    SDL_Rect getBox();

private:
    std::string name;
    SDL_Rect baseBox;

    std::vector<AnimationFrame> frames;
    std::vector<AnimationFrame>::iterator currentFrame;
};