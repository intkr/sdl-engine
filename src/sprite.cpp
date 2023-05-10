#include "sprite.h"

Sprite::Sprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, double a) {
	_texture = tex;
	srcRect = src;
	baseRect = dst;
	angle = a;
	visibility = true;
	if (dst != NULL) {
		dstRect = new SDL_FRect(*dst);
	}
	else {
		dstRect = NULL;
	}
	status = _INTRO;

	_animations[0] = &introAnimations;
	_animations[1] = &idleAnimations;
	_animations[2] = &outroAnimations;
}

Sprite::~Sprite() {
	// do not destroy texture

	if (srcRect != NULL) delete srcRect;
	if (baseRect != NULL) delete baseRect;
	if (dstRect != NULL) delete dstRect;

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
	Animation* a;
	AniVector* v = _animations[status];
	short flag = 0; // 0 : no sequential animations // 1 : unfinished sequential animations // 2 : all sequential animations finished

	for (auto i = v->begin(); i != v->end();) {
		a = i->second;

		if (i->first == "logoMoveLeft") {
			std::cout << "";
		}
		bool r = a->process(this);


		if (!r) {
			// animation was already finished, don't process and continue iteration
			i++;
			continue;
		}

		if (a->isFinished()) {
			if (!a->isLooping()) {
				// animation is finished and doesn't loop, delete from vector
				delete a;
				i = v->erase(i);
				continue;
			}

			// animation is not part of a sequence, reset
			if (!a->isSequential()) {
				a->reset();
				i++;
				continue;
			}
			
			if (!flag) flag = 2;
			if (a->isCompound()) {
				// this compound animation is part of a sequence, continue sequence
				i++;
				continue;
			}
			else {
				// this sequence doesn't continue further, break here
				break;
			}
		}
		else {
			if (a->isSequential()) flag = 1;

			if (a->isCompound()) {
				// this compound animation is part of a sequence, continue sequence
				i++;
				continue;
			}
			else {
				// this sequence doesn't continue further, break here
				break;
			}
		}
	}

	// reset all finished sequential looping animations
	if (flag == 2) {
		for (auto i = v->begin(); i != v->end();) {
			a = i->second;
			if (a->isFinished() && a->isSequential() && a->isLooping()) a->reset();
			i++;
		}
	}

	if (v->empty()) {
		// update status
		switch (status) {
		case _INTRO:
			status = _IDLE;
			break;
		case _IDLE:
			status = _OUTRO;
			break;
		case _OUTRO:
			status = _END;
			break;
		}

		if (status == _END) return false;
	}
	return true;
}

bool Sprite::addAnimation(std::string name, Animation* a, AnimationType type) {
	if (type == _END) return false;
	if (a == NULL) return false;

	(*_animations[type]).push_back(std::make_pair(name, a));
	return true;
}

bool checkCollision(SDL_FPoint& point, Sprite* sprite) {
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
