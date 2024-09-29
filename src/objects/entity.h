#pragma once
#include <string>
#include <vector>

#include "SDL.h"

#include "game_object.h"
#include "components/sprite_component.h"
#include "components/collision_component.h"

class Entity : public GameObject {
public:
	Entity(std::string _name, SDL_FPoint pos) : GameObject(_name, pos), parent(nullptr) {}
	void addSubentity(Entity* entity);
	void getSubentity(std::string name);
	void setParent(Entity* entity) { parent = entity; }
	void addSprite(SpriteComponent* sprite);
	// Adds collision to a sprite owned by the entity.
	void addCollision(CollisionComponent* collision, std::string spriteName);

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