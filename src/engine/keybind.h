#pragma once

#include <string>

#include <SDL.h>

struct Keybind {
    bool operator==(const std::string& name) {
        return (action == name);
    }

    std::string action;
    SDL_Scancode bindedKey;
    SDL_Scancode editorKey;
};