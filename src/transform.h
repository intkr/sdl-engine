#pragma once

#include "SDL.h"

#include "math_operators.h"
#include "math_constants.h"

struct Transform {
    Transform(SDL_FPoint pos, const Transform& parentTransform)
      : position(pos), parent(parentTransform),
        angle_deg(0.0), scale_percent(1.0f) {}

    void inherit(const Transform& parent) {
        rotate(parent.angle_deg);
        scale(parent.scale_percent);
        translate(parent.position);
    }

    void rotate(double rotation_deg) {
        if (rotation_deg == 0.0) return;

        angle_deg += rotation_deg;
        double rotation_rad = rotation_deg * PI / 180;
        // Apply rotation matrix on position
        position.x = position.x * cos(rotation_deg) - position.y * sin(rotation_deg);
        position.y = position.x * sin(rotation_deg) + position.y * cos(rotation_deg);
    }

    void scale(float multiplier) {
        scale_percent *= multiplier;
        position *= multiplier;
    }

    void translate(SDL_FPoint delta) {
        position += delta;
    }
    
    const Transform* parent;

    SDL_FPoint position;
    double angle_deg;
    // Currently only allows fixed-ratio scaling.
    // Change code when axis-specific scaling is needed.
    float scale_percent;
};