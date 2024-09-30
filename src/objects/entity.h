#pragma once
#include <string>
#include <vector>

#include "SDL.h"

#include "game_object.h"
#include "components/sprite_component.h"
#include "components/collision_component.h"

class Entity : public GameObject {
public:
	// dont focus on these stuff until all components are done
	Entity(std::string _name, SDL_FPoint pos) : GameObject(_name, pos), parent(nullptr) {}
	void addSubentity(Entity* entity);
	Entity* getSubentity(std::string name);
	void setParent(Entity* entity) { parent = entity; }
	void addSprite(SpriteComponent* sprite);
	void addCollision(std::string spriteName, std::string dataPath);

	void update(ms delta) override;

private:
	Entity* parent;
	std::vector<Entity*> subentities;
	std::vector<SpriteComponent*> sprites;
	std::vector<CollisionComponent*> collisions;

	/*
	stuff to add:
	collision / input components
	sub/parent entity related functions
	*/
};