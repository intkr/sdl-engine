#include "sprite.h"

Sprite::Sprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, double a) {
	_texture = tex;
	srcRect = src;
	baseRect = dst;
	angle = a;
	visibility = true;
	if (dst != nullptr) {
		dstRect = new SDL_FRect(*dst);
	}
	else {
		dstRect = nullptr;
	}
	status = _INTRO;

	_animations[0] = &introAnimations;
	_animations[1] = &idleAnimations;
	_animations[2] = &outroAnimations;
}

Sprite::~Sprite() {
	if (srcRect != nullptr) delete srcRect;
	if (baseRect != nullptr) delete baseRect;
	if (dstRect != nullptr) delete dstRect;

	for (int i = 0; i < 3; i++) {
		for (auto it = _animations[i]->begin(); it != _animations[i]->end();) {
			delete it->second;
			it = _animations[i]->erase(it);
		}
	}
}

void Sprite::resetDstRect() {
	dstRect->x = baseRect->x;
	dstRect->y = baseRect->y;
	dstRect->w = baseRect->w;
	dstRect->h = baseRect->h;
}

void Sprite::setAngle(double a) {
	while (a > 180 || a < -180) {
		a += 360 * (a < 0 ? 1 : -1);
	}
	angle = a;
}

bool Sprite::update() {
	if (status == _END) return false;

	AniContainer* list = _animations[status];
	bool finished = true;
	if (list->size() == 0) {
		++status;
		return false;
	}

	// set default texture opacity to 100%
	SDL_SetTextureAlphaMod(getTexture(), 255);

	for (auto aniGroup = list->begin(); aniGroup != list->end();) {
		if (aniGroup->second->animate(this)) {
			//finished = true;
		}
		else finished = false;
		aniGroup++;
	}

	if (finished) {
		++status;
	}
	return status != _END;
}

bool Sprite::addAnimationGroup(std::string name, StatusType type, AnimationGroup* g) {
	if (type == _END) {
		std::cout << "Failed to add animation group \"" << name << "\". (StatusType == _END)\n";
		return false;
	}
	
	if (g == nullptr) {
		std::cout << "Failed to add animation group \"" << name << "\". (Null group object)\n";
		return false;
	}

	if ((*_animations[type]).count(name) > 0) {
		std::cout << "Failed to add animation group \"" << name << "\". (Duplicate group name)\n";
		return false;
	}

	(*_animations[type])[name] = g;
	return true;
}

bool Sprite::addAnimationEvent(std::string groupName, AnimationEvent* e) {
	if (e == nullptr) {
		std::cout << "Failed to add animation event to group \"" << groupName << "\". (Null event object)\n";
		return false;
	}

	int index = -1;
	for (int i = 0; i < 3; i++) {
		if ((*_animations[i]).count(groupName) > 0) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "Failed to add animation event to group \"" << groupName << "\". (Invalid group name)\n";
		return false;
	}

	(*_animations[index])[groupName]->addEvent(e);
	return true;
}

bool Sprite::toggleAnimationGroup(std::string groupName, StatusType type, bool enable) {
	if (_animations[type]->count(groupName) > 0) {
		if (enable) (*_animations[type])[groupName]->enableGroup();
		else (*_animations[type])[groupName]->disableGroup();
		return true;
	}
	else {
		std::cout << "Failed to toggle animation group \"" << groupName << "\". (Invalid group name or wrong StatusType)\n";
		return false;
	}
}

bool checkCollision(SDL_FPoint point, Sprite* sprite) {
	// Because SDL_FRect can't be rotated,
	// the function "un-rotates the point" and checks the collision instead.

	SDL_FRect* hitbox = sprite->getDstRect();
	SDL_FPoint centroid = { hitbox->x + hitbox->w / 2, hitbox->y + hitbox->h / 2 };

	// Sprite's rotation angle in radians.
	float a = (float)(sprite->getAngle() * M_PI / 360);
	
	// Move the point so it's related to (0, 0) instead of the hitbox's center.
	// This is done to simply point rotation calculations.
	point.x -= centroid.x;
	point.y -= centroid.y;

	// Rotate point
	float c = atan2f(point.y, point.x); // Rotation of point in radians
	float d = sqrtf(point.x * point.x + point.y * point.y); // Length from (0, 0) to point
	point.x = d * cosf(a - c) + centroid.x;
	point.y = d * sinf(a - c) + centroid.y;

	// Check if the un-rotated point is within hitbox
	return SDL_PointInFRect(&point, hitbox);
}

bool checkCollision(Sprite* s1, Sprite* s2) {
	SDL_FRect* r1 = s1->getDstRect(), * r2 = s2->getDstRect();
	double a1 = s1->getAngle(), a2 = s2->getAngle();

	// not implementing this until I need it :Okayge:
	return false;
}