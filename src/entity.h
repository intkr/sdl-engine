#pragma once
#include <algorithm>
#include <cmath>

#include "attribute.h"
#include "geometry.h"
#include "sprite.h"
#include "animation.h"
#include "renderer.h"
#include "exception.h"

class Entity {
public:
	Entity(std::string name, SDL_FPoint pos) : attribute(name), geometry(pos) {}
	~Entity();
	
	bool operator==(const Entity& other) const;
	
	void addSprite(Sprite* s);
	void addAnimation(Animation* a);
	void addSubentity(Entity* e);
	
	// f(Entity*) should be defined in the state the entity is stored in.
	void setKeyEvent(KeyInput input, void(*f)(Entity*));
	void setMouseEvent(MouseInput input, void(*f)(Entity*));
	
	void update();
	void render(Renderer* renderer);
	
	void handleKey(KeyInput i);
	void handleMouse(MouseInput i);
	
	bool doesCollide(SDL_FPoint point);
	
	Entity* getSubentity(std::string name);
	std::string getName() { return attribute.name; }
	bool isFocused() { return focused; }
	
private:
	// Checks if the object actually exists and has not been added yet.
	// Note that these functions can't give enough information when an exception is thrown.
	template<typename T>
	void checkObjectValidity(T* t, std::vector<T*> v);
	template<typename T>
	bool doesObjectExist(T* t, std::vector<T*> v);
	
	MouseInput getCollisionInput(SDL_FPoint pos);
	void handleMouseInput(MouseInput i);
	
	void resetAllSprites();
	void playAnimations();
	void animateRecursively(Animation* animation);
	void applyAnimation(Animation* animation);
	void updateHitboxes(Orientation o);
	
	ObjectAttribute attribute;
	EntityGeometry geometry;
	bool focused;
	
	// if needed, add a parent entity pointer
	
	std::vector<Entity*> subentities;
	std::vector<Sprite*> sprites;
	std::vector<Animation*> animations;
	
	std::map<MouseInput, void(*)(Entity*)> mouseEvents;
	std::map<KeyInput, void(*)(Entity*)> keyEvents;
};

template<typename T>
void Entity::checkObjectValidity(T* t, std::vector<T*> v) {
	if (t == nullptr)
		throw InvalidItemException("nullptr", "object");
	if(doesObjectExist(t))
		throw DuplicateItemException("(?)", "object");
}

template<typename T>
bool Entity::doesObjectExist(T* t, std::vector<T*> v) {
	return (std::find(v.begin(), v.end(), t) != v.end());
}