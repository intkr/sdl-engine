#pragma once

#include <vector>

#include "clock.h"
#include "attribute.h"

struct AnimationFrame {
    int row;
    int column;
    ms duration;
};

class Animation {
public:
    Animation(std::string name) : attribute(name) {}
    
    // The box data of the first sprite is used to calculate
    // all positions of subsequent sprites for a given animation.
    // TODO: rename
    void initFirstSprite(int x, int y, int w, int h);

    void update(ms delta);
    SDL_Rect getBox();

private:
    Attribute attribute;
    SDL_Rect baseBox;

    std::vector<AnimationFrame> frames;
    std::vector<AnimationFrame>::iterator currentFrame;
};