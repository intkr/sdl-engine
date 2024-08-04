#include "graphics_component.h"

void GraphicsComponent::initFromFile(std::string path) {
    // parse through file
        // set attributes
        // get source data file path, init source
        // get display data file path, init display
}

void GraphicsComponent::update(ms delta) {
    source.update(delta);
    display.update(delta);
}

void GraphicsComponent::render(Renderer* renderer) {
    renderer.renderTexture(source.texture, source.textureBox, display.renderBox, display.finalAngle_deg);
}