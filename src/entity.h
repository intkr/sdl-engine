#pragma once
#include <string>
#include <vector>

#include "SDL.h"

#include "game_object.h"
#include "sprite_component.h"

class Entity : public GameObject {
public:
	Entity(std::string _name, SDL_FPoint pos) : GameObject(_name, pos) {}
	void addEntity(Entity* entity);
	void addSprite(SpriteComponent* sprite);

	void update(ms delta) override;

private:
	Entity* parent;
	std::vector<Entity*> subentities;
	std::vector<SpriteComponent*> sprites;

	/*
	stuff to add:
	collision / input components
	sub/parent entity related functions
	*/
};