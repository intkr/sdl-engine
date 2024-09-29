#include "display_component.h"

void DisplayComponent::initFromFile(std::string path) {
    // get metadata stuff from the file on path
    // get file path with motion data from this file
    // loadMotionFromFile(motionFilePath);
}

void DisplayComponent::loadMotionFromFile(std::string path) {

}

void DisplayComponent::update(ms delta) {
    applyMotion(delta);
}

void DisplayComponent::applyMotion(ms delta) {
    spriteTransform = currentMotion->apply(spriteTransform, delta);
}