#pragma once
#include <vector>

#include "SDL.h"

#include "transform.h"
#include "motion.h"

class DisplayComponent {
    friend class SpriteComponent;

public:
	void initFromFile(std::string path);
    void setObjectTransform(Transform objTransform) {
        objectTransform = objTransform;
    }

	void update(ms delta);

private:
    void loadMotionFromFile(std::string path);

    void applyMotion(ms delta);
    void applyObjectTransform();
    void calculateRotatedPosition(double angle_deg);
    void setBoxWindowRelative();

    std::vector<Motion> motions;
    std::vector<Motion>::iterator currentMotion;

    const Transform* objectTransform;
    Transform transform;

    // "Object-relative" : Relative to the parent object.
    // "Window-relative" : Relative to the window; "objective".
    
    // Pre-motion, object-relative box.
    // Original box values to apply motions on.
    SDL_FRect baseBox;
    // Post-motion, object-relative box.
    // Box values after motions are applied, but not for rendering.
    SDL_FRect modBox;
    // Post-motion, window-relative box.
    // Final box values to be used on rendering.
    SDL_FRect renderBox;

    // Object-relative rotation angle.
    double relativeAngle_deg;
    // Window-relative rotation angle.
    double angle_deg;
};