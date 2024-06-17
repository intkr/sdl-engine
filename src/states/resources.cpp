#include "resources.h"

void Resources::render(Renderer* renderer) {
	for (Sprite* sprite : sprites) {
		sprite->render(renderer);
	}
}

void Resources::addSprite(Sprite* sprite) {
	auto iter = std::lower_bound(sprites.begin(), sprites.end(), sprite,
	[](Sprite& a, Sprite& b) -> bool { return a.getLayer() < b.getLayer(); } );
	sprites.insert(iter, sprite);
}

void Resources::addEntity(Entity* entity) {
	entities.push_back(entity);
}

Sprite* Resources::getSprite(std::string name) {
    for (Sprite* sprite : sprites) {
        if (sprite->getName() == name) {
            return sprite;
        }
    }
    throw InvalidItemException(name, "sprite");
}

Entity* Resources::getEntity(std::string name) {
    for (Entity* entity : entities) {
        if (entity->getName() == name) {
            return entity;
        }
    }
    throw InvalidItemException(name, "entity");
}

void Resources::deleteSprite(std::string name) {
    for (auto iter = sprites.begin(); iter != sprites.end(); iter++) {
        if ((*iter)->getName() == name) {
            sprites.erase(iter);
            return;
        }
    }
}

void Resources::deleteEntity(std::string name) {
    for (auto iter = entities.begin(); iter != entities.end(); iter++) {
        if ((*iter)->getName() == name) {
            entities.erase(iter);
            return;
        }
    }
}