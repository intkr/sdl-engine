#pragma once

#include <string>

#include "transform.h"
#include "renderer.h"

#include "source_component.h"
#include "display_component.h"

class SpriteComponent {
public:
    SpriteComponent(std::string _name, short _layer);
    void init(std::string initFilePath, Transform* objectTransform);
    void render(Renderer* renderer);

private:
    void initFromFile(std::string path);
    void setTransform(Transform* t);

    std::string name;
    short layer;

    SourceComponent* source;
    DisplayComponent* display;
};