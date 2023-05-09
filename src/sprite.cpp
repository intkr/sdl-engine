#include "sprite.h"

Animation::Animation(float floats[4], int frames, bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*)) {
	for (int i = 0; i < _countof(param); i++) param[i] = floats[i];
	maxFrames = frames;
	currentFrames = 1;
	looping = loop;
	compound = comp;
	sequential = seq;
	func = f;
}

Animation::Animation(bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*)) {
	for (int i = 0; i < _countof(param); i++) param[i] = 0;
	maxFrames = 1;
	currentFrames = 1;
	looping = loop;
	compound = comp;
	sequential = seq;
	func = f;
}

Animation::~Animation() {}

bool Animation::process(Sprite* s) {
	if (!isFinished()) {
		func(s, this);
		currentFrames++;
		return true;
	}
	return false;
}

bool Animation::isFinished() {
	return (currentFrames > maxFrames);
}

bool Animation::isCompound() {
	return compound;
}

bool Animation::isLooping() {
	return looping;
}

bool Animation::isSequential() {
	return sequential;
}

unsigned int Animation::getCF() {
	return currentFrames;
}

unsigned int Animation::getMF() {
	return maxFrames;
}

void Animation::reset() {
	currentFrames = 1;
}

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
	status = 0;

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

SDL_Texture* Sprite::getTexture() {
	return _texture;
}

SDL_Rect* Sprite::getSrcRect() {
	return srcRect;
}

SDL_FRect* Sprite::getBaseRect() {
	return baseRect;
}

SDL_FRect* Sprite::getDstRect() {
	return dstRect;
}

void Sprite::setAngle(double a) {
	while (a > 180 || a < -180) { // normalize angle to -180 ~ 180
		a += 360 * (a < 0 ? 1 : -1);
	}
	angle = a;
}

double Sprite::getAngle() {
	return angle;
}

bool Sprite::isVisible() {
	return visibility;
}

void Sprite::triggerOutro() {
	status = OUTRO;
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
		if (++status >= 3) return false;
	}
	return true;
}

bool Sprite::addAnimation(std::string name, Animation* a, short index) {
	if (index < 0 || index > 2) return false;
	if (a == NULL) return false;

	(*_animations[index]).push_back(std::make_pair(name, a));
	return true;
}

bool checkCollision(SDL_FPoint* p, Sprite* s) {
	SDL_FRect* r = s->getDstRect();
	float a = (float)(s->getAngle() * M_PI / 360); // sprite's rotation angle, converted to radians

	// This function checks the collision between a point and a rotated rectangle.
	// Because dstRect itself is not rotated, the point will be rotated instead for the collision check.

	SDL_FPoint cp = { r->x + r->w / 2, r->y + r->h / 2 }; // center of r
	
	// subtract p by cp, so p can be rotated centered on (0, 0)
	p->x -= cp.x;
	p->y -= cp.y;

	// Rotate point
	SDL_FPoint np; // new point
	float c = atan2f(p->y, p->x); // rotation of p, radians
	float d = sqrtf(p->x * p->x + p->y * p->y); // length of OP
	np.x = d * cosf(a - c) + cp.x;
	np.y = d * sinf(a - c) + cp.y;
	return SDL_PointInFRect(&np, r);
}

bool checkCollision(Sprite* s1, Sprite* s2) {
	SDL_FRect* r1 = s1->getDstRect(), * r2 = s2->getDstRect();
	double a1 = s1->getAngle(), a2 = s2->getAngle();

	// not implementing this until I need it :Okayge:
	return false;
}
