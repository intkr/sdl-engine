#include "key_category.h"

void KeyCategory::addKeybind(std::string action, SDL_Scancode key) {
    auto iter = std::find(keybinds.begin(), keybinds.end(), action);

    if (iter == keybinds.end()) {
        Keybind keybind { action, key, key };
        keybinds.push_back(keybind);
    }
}

void KeyCategory::editKeybind(std::string action, SDL_Scancode key) {
    auto iter = std::find(keybinds.begin(), keybinds.end(), action);

    if (iter != keybinds.end()) {
        iter->editorKey = key;
    }
}

void KeyCategory::confirmEdit() {
    for (Keybind& keybind : keybinds) {
        keybind.bindedKey = keybind.editorKey;
    }
}

void KeyCategory::cancelEdit() {
    for (Keybind& keybind : keybinds) {
        keybind.editorKey = keybind.bindedKey;
    }
}

std::string KeyCategory::getAction(SDL_Scancode key) {
    auto iter = std::find(keybinds.begin(), keybinds.end(), action);

    if (iter != keybinds.end()) {
        return iter->action;
    }
    return "action_none";
}