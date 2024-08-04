#pragma once
#include <string>
#include <vector>

#include "geometry.h"
#include "motion.h"

class DisplayComponent {
    friend class GraphicsComponent;
public:
    DisplayComponent(TransformComponent& objTransform) : objectTransform(objTransform) {}
	void initFromFile(std::string path);

	void update(ms delta);
    
private:
    void loadMotionFromFile(std::string path);

    void applyMotion(ms delta);
    void applyObjectTransform();
    void calculateRotatedPosition(double angle_deg);
    void setBoxWindowRelative();

    std::vector<Motion> motions;
    std::vector<Motion>::iterator currentMotion;

    // Transform of the object this component is part of.
    TransformComponent* const objectTransform;

    // "Object-relative" : Relative to the parent object.
    // "Window-relative" : Relative to the window; "objective".
    
    // Pre-transform, object-relative box.
    // Contains the original values to perform calculations on.
    SDL_FRect baseBox;
    // Post-transform, window-relative box.
    // Contains the final values to be used on rendering.
    SDL_FRect renderBox;

    // Object-relative rotation angle.
    double relativeAngle_deg;
    // Window-relative rotation angle.
    double finalAngle_deg;
};