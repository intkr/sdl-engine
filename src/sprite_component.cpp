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
    renderer.renderTexture(source.texture, source.textureBox, display.renderBox, display.finalAngle_deg);
}