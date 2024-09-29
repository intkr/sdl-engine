#include "graphics_component.h"

SpriteComponent::SpriteComponent(std::string _name, short _layer) : name(_name), layer(_layer) {
    // create source / display component in the resource container
    // and set pointers to them
}

void SpriteComponent::init(std::string initFilePath, Transform* objectTransform) {
    initFromFile(initFilePath);
    setTransform(objectTransform);
}

void SpriteComponent::initFromFile(std::string path) {
    // parse through file
        // set attributes
        // get source data file path, init source
        // get display data file path, init display
            // also pass localtransform to display
}

void SpriteComponent::setTransform(Transform* t) {
    transform.parent = localTransform.parent = t;
}

void SpriteComponent::render(Renderer* renderer) {
    // add texture mods here

    SDL_FRect renderBox = source.getSourceBox();
    Transform transform = display.getTransform();
    SDL_FPoint center = source.getCenter() * transform.scale_percent;

    renderBox.w *= transform.scale_percent;
    renderBox.h *= transform.scale_percent;
    // Translate the display position by the source's center position,
    // so the top left of the render box is set correctly.
    renderBox.x = transform.position.x - center.x;
    renderBox.y = transform.position.y - center.y;

    renderer.renderTexture(source.getTexture(), source.getSourceBox(), renderBox, transform.angle_deg, center);
}

void SpriteComponent::update() {
    transform = localTransform;

    // Update transform by inheriting values from all parents
    const Transform* currentParent = transform.parent;
    while (currentParent != nullptr) {
        transform.inherit(currentParent);
        currentParent = currentParent.parent;
    }
}