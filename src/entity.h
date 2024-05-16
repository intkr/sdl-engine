#pragma once
#include <algorithm>
#include <cmath>

#include "attribute.h"
#include "sprite.h"
#include "animation.h"
#include "renderer.h"
#include "exception.h"

class Entity {
public:
	Entity(std::string name, SDL_FPoint pos) : attribute(name), orientation(pos) {}
	~Entity();
	
	bool operator==(const Entity& other) const;
	
	void addSprite(Sprite* s);
	void addAnimation(Animation* a);
	void addSubentity(Entity* e);
	Entity* getSubentity(std::string name);
	void setKeyEvent(KeyInput input, void(*f)(Entity*));
	void setMouseEvent(MouseInput input, void(*f)(Entity*));
	
	void update();
	void render(Renderer* renderer);
	
	void handleKey(KeyInput i);
	void handleMouse(MouseInput i);
	
	// Checks the collision between an entity's hitbox and a single point.
	bool isPointInEntity(SDL_FPoint point);
	
	std::string getName() { return attribute.name; }
	bool isFocused() { return focused; }
	
private:
	void checkSpriteValidity(Sprite* s);
	void checkAnimationValidity(Animation* a);
	bool isSpriteAlreadyMapped(Sprite* s);
	bool isAnimationAlreadyMapped(Animation* a);
	
	MouseInput getCollisionInput(SDL_FPoint pos);
	void handleMouseInput(MouseInput i);
	
	void resetAllSpriteEffects();
	void playAnimations();
	void animateRecursively(Animation* animation);
	void applyAnimation(Animation* animation);
	void updateHitboxes(Orientation o);
	
	Attribute attribute;
	Orientation orientation;
	bool focused;
	
	// if needed, add a parent entity pointer
	
	std::vector<Entity*> subentities;
	std::vector<Sprite*> sprites;
	std::vector<Animation*> animations;
	
	std::map<MouseInput, void(*)(Entity*)> mouseEvents;
	std::map<KeyInput, void(*)(Entity*)> keyEvents;
};