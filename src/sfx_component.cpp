#include "sfx_component.h"

void SFXComponent::addSFX(std::string label, std::string soundName) {
    if (sfxs.count(label) > 0) {
        // SFX for the given label has already been added.
        // This new SFX does not replace the old one.
    }
    sfxs.emplace(label, soundName);
}

void SFXComponent::playSFX(std::string label) {
    // call resources
}