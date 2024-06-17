#pragma once

#include <vector>

#include "../exceptions.h"
#include "../entity.h"
#include "../renderer.h"

// Stores all sprites and entities used by currently active states.
class Resources {
public:
    void render(Renderer* renderer);

	void addSprite(Sprite* sprite);
	void addEntity(Entity* entity);
    
    Sprite* getSprite(std::string name);
    Entity* getEntity(std::string name);

    void deleteSprite(std::string name);
    void deleteEntity(std::string name);

private:
	std::vector<Sprite*> sprites;
	std::vector<Entity*> entities;
};