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
	float a = _e->getFloat("a"), b = _e->getFloat("b");
	char axis = _e->getChar("axis"), func = _e->getChar("func");

	unsigned int currentFrame = _e->getCurrentFrame();
	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();

	float delta;
	switch (func) {
	case 's': // sine
		delta = (float)sin(currentFrame * M_PI * b) * a;
		break;
	case 'c': // cosine
		delta = (float)cos(currentFrame * M_PI * b) * a;
		break;
	default:
		delta = 0;
		printf("sincos - invalid func : %c\n", func);
		break;
	}

	switch (axis) {
	case 'x':
		dstRect->x = baseRect->x - delta;
		break;
	case 'y':
		dstRect->y = baseRect->y - delta;
		break;
	default:
		printf("sincos - invalid axis : %c\n", axis);
		break;
	}
}

void Animations::linearMotion(Sprite* _s, AnimationEvent* _e) {
	float speed = _e->getFloat("speed");
	char axis = _e->getChar("axis");
	bool baseMove = _e->getBool("baseMove");

	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();

	switch (axis) {
	case 'x':
		dstRect->x += speed;
		if (baseMove) baseRect->x += speed;
		break;

	case 'y':
		dstRect->x += speed;
		if (baseMove) baseRect->y += speed;
		break;
	default:
		printf("linear - invalid axis : %c\n", axis);
		break;
	}
}

void Animations::resizeCenteredMotion(Sprite* _s, AnimationEvent* _e) {
	float startSize = _e->getFloat("startSize"), endSize = _e->getFloat("endSize");

	// validity check
	if (startSize < 0 || endSize < 0) {
		std::cout << "Multiplier is negative, failed to perform animation \"resizeCenteredPosition\".\n";
		return;
	}

	int aniLength = _e->getMaxFrames(), currentFrame = _e->getCurrentFrame();
	int remainingFrames = aniLength - currentFrame;
	SDL_FRect* dstRect = _s->getDstRect();
	SDL_FRect* baseRect = _s->getBaseRect();

	// calculate diving point between (0, startSize) and (1, endSize)
	dstRect->w = baseRect->w * (startSize * remainingFrames + endSize * currentFrame) / aniLength;
	dstRect->h = baseRect->h * (startSize * remainingFrames + endSize * currentFrame) / aniLength;

	// move position based on calculated size
	dstRect->x = baseRect->x + (baseRect->w - dstRect->w) / 2;
	dstRect->y = baseRect->y + (baseRect->h - dstRect->h) / 2;
}

void Animations::linearRotation(Sprite* _s, AnimationEvent* _e) {
	double speed = (double)_e->getFloat("speed");
	_s->setAngle(_s->getAngle() + speed);
}

void Animations::sincosRotation(Sprite* _s, AnimationEvent* _e) {
	float a = _e->getFloat("a"), b = _e->getFloat("b");
	char func = _e->getChar("func");
	unsigned int currentFrame = _e->getCurrentFrame();

	double angle = sin(currentFrame * M_PI * b) * a;
	_s->setAngle(angle);
}

void Animations::opacity(Sprite* _s, AnimationEvent* _e) {
	unsigned int currentFrame = _e->getCurrentFrame();
	unsigned int maxFrames = _e->getMaxFrames();

	float a = _e->getFloat("a");
	if (a > 1.0f) a = 1.0f;
	else if (a < 0.0f) a = 0.0f;
	
	if (maxFrames == 1) {
		SDL_SetTextureAlphaMod(_s->getTexture(), (Uint8)(a * 255));
	}
	else {
		float b = _e->getFloat("b");
		if (b > 1.0f) b = 1.0f;
		else if (b < 0.0f) b = 0.0f;

		SDL_SetTextureAlphaMod(_s->getTexture(), (Uint8)((b * currentFrame + a * (maxFrames - currentFrame)) / maxFrames * 255));
	}
}
