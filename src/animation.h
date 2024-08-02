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
    
    // The box data of the first sprite is used to calculate
    // all positions of subsequent sprites for a given animation.
    // TODO: rename
    void initFirstSprite(int x, int y, int w, int h);

    void update(ms delta);
    SDL_Rect getBox();

private:
    std::string name;
    SDL_Rect baseBox;

    std::vector<AnimationFrame> frames;
    std::vector<AnimationFrame>::iterator currentFrame;
};