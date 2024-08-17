#pragma once
#include <string>
#include <vector>

#include "SDL.h"

#include "game_object.h"
#include "sprite_component.h"
#include "collision_component.h"

class Entity : public GameObject {
public:
	Entity(std::string _name, SDL_FPoint pos) : GameObject(_name, pos), parent(nullptr) {}
	void addSubentity(Entity* entity);
	void setParent(Entity* entity);
	void addSprite(SpriteComponent* sprite);

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