#include "animation_functions.h"

#include "sprite.h"

void staticMotion(Sprite* _s, Animation* _a) {
	// nothing
}

void invisible(Sprite* _s, Animation* _a) {
	SDL_FRect* dstRect = _s->getDstRect();
	dstRect->w = dstRect->h = 0;
}

void sincosMotion(Sprite* _s, Animation* _a) {
	float a = _a->param[0], b = _a->param[1], c = _a->param[2], d = _a->param[3];
	unsigned int cf = _a->getCurrentFrame();
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

void linearMotion(Sprite* _s, Animation* _a) {
	float a = _a->param[0], b = _a->param[1], c = _a->param[2];
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

void resizeCenteredMotion(Sprite* _s, Animation* _a) {
	float a = _a->param[0], b = _a->param[1];

	// validity check
	if (a < 0 || b < 0) {
		std::cout << "Multiplier is negative, failed to perform animation \"resizeCenteredPosition\".\n";
		return;
	}

	int mf = _a->getAniLength(), cf = _a->getCurrentFrame();
	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();


	dstRect->w = baseRect->w * (a * (mf - cf) + b * cf) / mf;
	dstRect->h = baseRect->h * (a * (mf - cf) + b * cf) / mf;
	dstRect->x = baseRect->x + (baseRect->w - dstRect->w) / 2;
	dstRect->y = baseRect->y + (baseRect->h - dstRect->h) / 2;
}

void linearRotation(Sprite* _s, Animation* _a) {
	_s->setAngle(_s->getAngle() + (double)_a->param[0]);
}

void sinRotation(Sprite* _s, Animation* _a) {
	float a = _a->param[0], b = _a->param[1];
	unsigned int cf = _a->getCurrentFrame();
	double d = sin(cf * M_PI * b) * a;
	_s->setAngle(d);
}

void opacity(Sprite* _s, Animation* _a) {
	int a = (int)_a->param[0], b = (int)_a->param[1];
	unsigned int cf = _a->getCurrentFrame();
	unsigned int mf = _a->getAniLength();
	if (mf == 1) {
		SDL_SetTextureAlphaMod(_s->getTexture(), a);
	}
	else {
		SDL_SetTextureAlphaMod(_s->getTexture(), (b * cf + a * (mf - cf)) / mf);
	}
}