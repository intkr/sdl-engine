#include "key_config.h"

void KeyConfig::addCategory(std::string name) {
    categories.push_back(KeyCategory(name));
}

void KeyConfig::addKeybind(std::string category, std::string action, SDL_Scancode key) {
    auto category = std::find(categories.begin(), categories.end(), category);
    
    if (category != categories.end()) {
        category->addKeybind(action, key);
    }
}

void KeyConfig::editKeybind(std::string category, std::string action, SDL_Scancode key) {
    auto category = std::find(categories.begin(), categories.end(), category);
    
    if (category != categories.end()) {
        category->editKeybind(action, key);
    }
}
void KeyConfig::confirmEdit() {
    for (KeyCategory& category : categories) {
        category.confirmEdit();
    }
}

void KeyConfig::cancelEdit() {
    for (KeyCategory& category : categories) {
        category.cancelEdit();
    }
}

void KeyConfig::deactivateAllKeyCategories(bool includeCommon = false) {
    for (KeyCategory& category : categories) {
        if (includeCommon || (category == "keys_common")) {
            category.deactivate();
        }
    }
}

void KeyConfig::activateKeyCategory(std::string name) {
    auto category = std::find(categories.begin(), categories.end(), name);
    
    if (category != categories.end()) {
        category->activate();
    }
}

void KeyConfig::activateKeyCategory(vector<std::string>& names) {
    for (std::string name : names) {
        auto category = std::find(categories.begin(), categories.end(), name);
    
        if (category != categories.end()) {
            category->activate();
        }
    }
}

std::string KeyConfig::getAction(SDL_Scancode key) {
    std::string action;
    for (KeyCategory& category : categories) {
        if (category.isActive()) {
            action = category.getAction(key);
            if (action != "action_none") {
                return action;
            }
        }
    }

    return action;
}