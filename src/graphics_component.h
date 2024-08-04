#pragma once

#include "clock.h"
#include "renderer.h"

#include "source_component.h"
#include "display_component.h"

class GraphicsComponent {
public:
    GraphicsComponent(Position& objPos) : target(objPos) {} // TODO: consider finding a different way to init position value
    void initFromFile(std::string path);

    void update(ms delta);
    void render(Renderer* renderer);

private:
    SourceComponent source;
    DisplayComponent display;
};

/*
Graphics data file:

- attributes (name, active, etc)
- source / display data file path
*/