#pragma once
#include <algorithm>
#include <cmath>

#include "game_object.h"
#include "sprite_component.h"

class Entity : public GameObject {
public:
	Entity(std::string name, SDL_FPoint pos) : attribute(name), geometry(pos) {}
	~Entity();
	
	bool operator==(const Entity& other) const;
	
	void addSubentity(Entity* e);
	
	// f(Entity*) should be defined in the state the entity is stored in.
	void setKeyEvent(KeyInput input, void(*f)(Entity*));
	void setMouseEvent(MouseInput input, void(*f)(Entity*));
	
	void update();
	void render() override;
	
	void handleKey(KeyInput i);
	void handleMouse(MouseInput i);
	
	bool doesCollide(SDL_FPoint point);
	
	bool isRootEntity() { return (parent == null); }
	Entity* getParentEntity() { return parent; }
	Entity* getSubentity(std::string name);
	std::string getName() { return attribute.name; }
	bool isFocused() { return focused; }
	
private:

	
	MouseInput getCollisionInput(SDL_FPoint pos);
	void handleMouseInput(MouseInput i);
	
	void updateHitboxes(Orientation o);
	
	Entity* parent;
	std::vector<Entity*> subentities;

	Attribute attribute;
	Position position;
	
	// TODO: implement in a way such that each Text/Sprite component can be tied to a Display component
	// 		 so the Renderer can draw each texture as intended
	vector<SpriteComponent> sprites;

	std::map<MouseInput, void(*)(Entity*)> mouseEvents;
	std::map<KeyInput, void(*)(Entity*)> keyEvents;
};

