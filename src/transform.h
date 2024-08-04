#pragma once

#include "SDL.h"

struct Transform {
    Transform(SDL_FPoint pos, double angle = 0.0) : position(pos), angle_deg(angle), scale_percent(1.0) {}
    
    SDL_FPoint position;
    double angle_deg;
    double scale_percent;
};