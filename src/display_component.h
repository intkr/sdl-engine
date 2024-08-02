#pragma once
#include <string>
#include <vector>

#include "geometry.h"
#include "motion.h"

class DisplayComponent {
    friend class GraphicsComponent;
public:
    DisplayComponent(Position& objPos) : centerPos(position) {}
	void initFromFile(std::string path);

	void update(ms delta);
    
private:
    // some class object to make changes on the render box idk

    // Position of the object this component is part of.
    Position* const centerPos;

    // "Object-relative" : (0,0) refers to centerPos.
    // "Window-relative" : (0,0) refers to the top left corner of the window.
    
    // Pre-transform, object-relative box.
    // Contains the original values to perform calculations on.
    SDL_FRect baseBox;
    // Post-transform, window-relative box.
    // Contains the final values to be used on rendering.
    SDL_FRect renderBox;

    double angle_deg;
};