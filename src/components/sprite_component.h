#pragma once

#include <string>

#include "engine/transform.h"
#include "engine/renderer.h"

#include "source_component.h"
#include "display_component.h"

class SpriteComponent {
public:
    SpriteComponent(std::string _name, short _layer);
    void init(std::string initFilePath, Transform* objectTransform);
    void render(Renderer* renderer);
    void update();

    void getTransform() { return transform; }

private:
    void initFromFile(std::string path);

    std::string name;
    short layer;

    Transform transform;
    Transform localTransform;

    SourceComponent* source;
    DisplayComponent* display;
};

/*
local transform is updated by processing motions via the display component.
it is then used by the sprite component to update the global transform.
global transform is used by external objects, such as collision checks and rendering.

<!> the global transform does not use its 'parent' variable - as it is not local to any parent.
*/