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
		delta = sin(currentFrame * M_PI * b) * a;
		break;
	case 'c': // cosine
		delta = cos(currentFrame * M_PI * b) * a;
		break;
	default:
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

	int aniLength = _e->getAnimationLength(), currentFrame = _e->getCurrentFrame();
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

//void Animations::opacity(Sprite* _s, AnimationEvent* _e) {
//	std::vector<double>* p = _e->getParameter();
//	int a = (int)(*p)[0], b = (int)(*p)[1];
//	unsigned int cf = _e->getCurrentFrame();
//	unsigned int mf = _e->getAnimationLength();
//	if (mf == 1) {
//		SDL_SetTextureAlphaMod(_s->getTexture(), a);
//	}
//	else {
//		SDL_SetTextureAlphaMod(_s->getTexture(), (b * cf + a * (mf - cf)) / mf);
//	}
//}
