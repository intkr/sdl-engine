#include "animation_functions.h"

#include "sprite.h"

void Animations::staticMotion(Sprite* _s, AnimationEvent* _e) {
	// nothing
}

void Animations::invisible(Sprite* _s, AnimationEvent* _e) {
	SDL_FRect* dstRect = _s->getDstRect();
	dstRect->w = dstRect->h = 0;
}

void Animations::sincosMotion(Sprite* _s, AnimationEvent* _e) {
	std::vector<double>* p = _e->getParameter();
	float a = (*p)[0], b = (*p)[1], c = (*p)[2], d = (*p)[3];
	unsigned int cf = _e->getCurrentFrame();
	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();

	float f;
	if (d == (float)true) { // true : sin, false : cos
		f = (float)sin(cf * M_PI * b) * a;
	}
	else {
		f = (float)cos(cf * M_PI * b) * a;
	}

	if (c == (float)true) { // true : x, false : y
		dstRect->x = baseRect->x - f;
	}
	else {
		dstRect->y = baseRect->y - f;
	}
}

void Animations::linearMotion(Sprite* _s, AnimationEvent* _e) {
	std::vector<double>* p = _e->getParameter();
	float a = (*p)[0], b = (*p)[1], c = (*p)[2];
	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();

	if (a == (float)true) {
		dstRect->x += b;
		if (c == (float)true) baseRect->x += b;
	}
	else {
		dstRect->y += b;
		if (c == (float)true) baseRect->y += b;
	}
}

void Animations::resizeCenteredMotion(Sprite* _s, AnimationEvent* _e) {
	std::vector<double>* p = _e->getParameter();
	float a = (*p)[0], b = (*p)[1];

	// validity check
	if (a < 0 || b < 0) {
		std::cout << "Multiplier is negative, failed to perform animation \"resizeCenteredPosition\".\n";
		return;
	}

	int mf = _e->getAnimationLength(), cf = _e->getCurrentFrame();
	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();


	dstRect->w = baseRect->w * (a * (mf - cf) + b * cf) / mf;
	dstRect->h = baseRect->h * (a * (mf - cf) + b * cf) / mf;
	dstRect->x = baseRect->x + (baseRect->w - dstRect->w) / 2;
	dstRect->y = baseRect->y + (baseRect->h - dstRect->h) / 2;
}

void Animations::linearRotation(Sprite* _s, AnimationEvent* _e) {
	std::vector<double>* p = _e->getParameter();
	_s->setAngle(_s->getAngle() + (double)(*p)[0]);
}

void Animations::sinRotation(Sprite* _s, AnimationEvent* _e) {
	std::vector<double>* p = _e->getParameter();
	float a = (*p)[0], b = (*p)[1];
	unsigned int cf = _e->getCurrentFrame();
	double d = sin(cf * M_PI * b) * a;
	_s->setAngle(d);
}

void Animations::opacity(Sprite* _s, AnimationEvent* _e) {
	std::vector<double>* p = _e->getParameter();
	int a = (int)(*p)[0], b = (int)(*p)[1];
	unsigned int cf = _e->getCurrentFrame();
	unsigned int mf = _e->getAnimationLength();
	if (mf == 1) {
		SDL_SetTextureAlphaMod(_s->getTexture(), a);
	}
	else {
		SDL_SetTextureAlphaMod(_s->getTexture(), (b * cf + a * (mf - cf)) / mf);
	}
}