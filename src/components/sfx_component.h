#pragma once
#include <map>
#include <string>

class SFXComponent {
public:
    // Adds the sound to a list labeled with the given parameter.
    void addSFX(std::string label, std::string soundName);
    // Plays the sound corresponding to the given label.
    void playSFX(std::string label);

private:
    // <label, sound name>
    std::map<std::string, std::string> sfxs;
}