#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "key_category.h"

class KeyConfig {
public:
    void addCategory(std::string name);
    void addKeybind(std::string category, std::string action, SDL_Scancode key);
    void editKeybind(std::string category, std::string action, SDL_Scancode key);
    void confirmEdit();
    void cancelEdit();

    // if 'includeCommon' is true, the commonly used keybinds (such as Enter / Esc)
    // will also be deactivated until activated manually.
    void deactivateAllKeyCategories(bool includeCommon = false);
    void activateKeyCategory(std::string category);
    void activateKeyCategory(vector<std::string>& categories);

    std::string getAction(SDL_Scancode key);

private:
    void sortCategories();
    
    std::vector<KeyCategory> categories;
};