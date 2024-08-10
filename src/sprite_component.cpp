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
}

void SpriteComponent::setTransform(Transform* t) {
    display->setObjectTransform(t);
}

void SpriteComponent::render(Renderer* renderer) {
    // add texture mods here

    SDL_FRect renderBox = source.getSourceBox();
    Transform transform = display.getTransform();

    renderBox.x = transform.position.x;
    renderBox.y = transform.position.y;
    renderBox.w *= transform.scale_percent;
    renderBox.h *= transform.scale_percent;

    renderer.renderTexture(source.getTexture(), source.getSourceBox(), renderBox, transform.angle_deg, source.getCenter());
}