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
	// do not destroy texture

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

void Sprite::setAngle(double a) {
	while (a > 180 || a < -180) { // normalize angle to -180 ~ 180
		a += 360 * (a < 0 ? 1 : -1);
	}
	angle = a;
}

bool Sprite::updateSprite() {
	if (status == _END) return false;

	AniContainer* list = _animations[status];
	bool finished = true;

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
	if (type == _END) return false;
	if (g == nullptr) return false;
	if ((*_animations[type]).count(name) > 0) return false;

	(*_animations[type])[name] = g;
	return true;
}

bool Sprite::addAnimationEvent(std::string groupName, AnimationEvent* e) {
	if (e == nullptr) return false;
	int index = -1;
	for (int i = 0; i < 3; i++) {
		if ((*_animations[i]).count(groupName) > 0) {
			index = i;
			break;
		}
	}
	if (index == -1) return false;

	(*_animations[index])[groupName]->addEvent(e);
	return true;
}

bool Sprite::toggleAnimationGroup(std::string groupName, StatusType type, bool enable) {
	if (_animations[type]->count(groupName) > 0) {
		if (enable) (*_animations[type])[groupName]->enableGroup();
		else (*_animations[type])[groupName]->disableGroup();
		return true;
	}
	else return false;
}

bool checkCollision(SDL_FPoint point, Sprite* sprite) {
	// Because rectangle objects can't be rotated, the function "un-rotates the point" instead.

	// Hitbox rect of sprite and its center point
	SDL_FRect* rect = sprite->getDstRect();
	SDL_FPoint rectCenter = { rect->x + rect->w / 2, rect->y + rect->h / 2 };

	// sprite'sprite rotation angle, converted to radians
	float a = (float)(sprite->getAngle() * M_PI / 360);
	
	// Move point so it's related to (0, 0) instead of center of rect
	point.x -= rectCenter.x;
	point.y -= rectCenter.y;

	// Rotate point
	SDL_FPoint np; // new point
	float c = atan2f(point.y, point.x); // rotation of point, radians
	float d = sqrtf(point.x * point.x + point.y * point.y); // length of OP
	np.x = d * cosf(a - c) + rectCenter.x;
	np.y = d * sinf(a - c) + rectCenter.y;

	// Check if the un-rotated point is within rect
	return SDL_PointInFRect(&np, rect);
}

bool checkCollision(Sprite* s1, Sprite* s2) {
	SDL_FRect* r1 = s1->getDstRect(), * r2 = s2->getDstRect();
	double a1 = s1->getAngle(), a2 = s2->getAngle();

	// not implementing this until I need it :Okayge:
	return false;
}