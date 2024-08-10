#pragma once

#include "SDL.h"

struct Transform {
    Transform(SDL_FPoint pos, double angle = 0.0, float scale = 1.0f) : position(pos), angle_deg(angle), scale_percent(scale) {}
    
    SDL_FPoint position;
    double angle_deg;
    float scale_percent;
};