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
    applyObjectTransform();
}

void DisplayComponent::applyMotion(ms delta) {
    renderBox = currentMotion->apply(baseBox, delta);
}

void DisplayComponent::applyObjectTransform() {
    calculateRotatedPosition();
    setBoxWindowRelative();
}

void DisplayComponent::calculateRotatedPosition() {
    double objectAngle_deg = objectTransform->getAngle();
    // There's nothing to rotate if value equals 0
    if (objectAngle_deg == 0.0) return;

    finalAngle_deg = relativeAngle_deg + objectAngle_deg;
}

void DisplayComponent::setBoxWindowRelative() {
    Position objectPosition = objectTransform->getPosition();
    renderBox.x += objectPosition.x;
    renderBox.y += objectPosition.y;
}