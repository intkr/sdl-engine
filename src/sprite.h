#pragma once
#include <map>
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "attribute.h"
#include "geometry.h"
#include "texture.h"
#include "animation.h"
#include "renderer.h"
#include "exception.h"

// Note: a Sprite's geometry is relative to the Entity's center position (equal to (0,0) for sprite positions)
class Sprite {
public:
	Sprite(std::string name, Texture* tex, Geometry& geo);
	~Sprite();
	
	bool operator==(const Sprite& other) const;
	
	void setTexture(Texture* texture, SDL_FRect* srcRect);
	
	void reset();
	void applyAnimation(Animation* a);
	void updateHitbox(EntityGeometry& geo);
	void render(Renderer* renderer);
	
	int getLayer() { return layer; }
	std::string getName() { return attribute.name; }
	
	bool isPointInSprite(SDL_FPoint point);
	
private:
	void deleteGeometry();
	
	void resetTextureMods();
	
	bool shouldSpriteBeRotated();
	void calculateRotation();
	void offsetPosition();
	
	ObjectAttribute attribute;
	int layer;
	SpriteGeometry geometry;
	Texture* texture;
};
