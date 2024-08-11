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
    transform = currentMotion->apply(transform, delta);
}

Transform DisplayComponent::getTransform() {
    Transform globalTransform = transform;

    // Update transform by inheriting values from all parents
    const Transform* currentParent = transform.parent;
    while (currentParent != nullptr) {
        globalTransform.inherit(currentParent);
        currentParent = currentParent.parent;
    }

    return globalTransform;
}