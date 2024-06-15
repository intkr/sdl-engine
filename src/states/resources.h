#pragma once

#include <vector>

#include "../entity.h"

// All resources used by the state are stored in this class object.
class Resources {
public:
    /*
    TODO:
        add functions that add, return, and delete entities/sprites.
    */

private:
	std::vector<Sprite*> sprites;
	std::vector<Entity*> entities;
};