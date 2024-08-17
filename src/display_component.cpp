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
    updateTransform();
}

void DisplayComponent::applyMotion(ms delta) {
    localTransform = currentMotion->apply(localTransform, delta);
}

void DisplayComponent::updateTransform() {
    transform = localTransform;

    // Update transform by inheriting values from all parents
    const Transform* currentParent = transform.parent;
    while (currentParent != nullptr) {
        transform.inherit(currentParent);
        currentParent = currentParent.parent;
    }
}