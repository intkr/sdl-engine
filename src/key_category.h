#pragma once

#include <vector>
#include <algorithm>

#include "keybind.h"

class KeyCategory {
public:
    bool operator==(const std::string& _name) {
        return (name == _name);
    }

    KeyCategory(std::string _name) : name(_name) {}
    void activate();
    void deactivate();
    bool isActive() { return active; }

    void addKeybind(std::string action, SDL_Scancode key);
    void editKeybind(std::string action, SDL_Scancode key);

    void confirmEdit();
    void cancelEdit();

    std::string getAction(SDL_Scancode key);

private:
    std::string name;
    bool active;

    std::vector<Keybind> keybinds;
};