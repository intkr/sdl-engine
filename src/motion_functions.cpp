#include "animation_functions.h"

void Motions::Stationary(Geometry* geo, Motion* m) {
	// Nothing happens
}

void Motions::2DPosition_SineWave(Geometry* geo, Motion* m) {
	const int msPerSecond = 1000;
	float amplitude = m->getParameter<float>("amplitude"),
		freqency = m->getParameter<float>("frequency");
	ms elapsedTime = m->getElapsedTime();
		
	float delta = amplitude * (float)sin(frequency * M_PI * (elapsedTime.count() / msPerSecond));
	
	char axis = m->getParameter<char>("axis");
	SDL_FRect*& baseRect = geo->baseRect,
		modRect = geo->modRect;
	
	switch (axis) {
	case 'x':
		modRect->x = baseRect->x - delta;
	case 'y':
		modRect->y = baseRect->y - delta;
	default:
		std::cout << "Invalid parameter 'axis' (" << axis << ") in 2DPosition_SineWave\n";
	}
}

void Motions::2DPosition_CosineWave(Geometry* geo, Motion* m) {
	const int msPerSecond = 1000;
	float amplitude = m->getParameter<float>("amplitude"),
		freqency = m->getParameter<float>("frequency");
	ms elapsedTime = m->getElapsedTime();
		
	float delta = amplitude * (float)sin(frequency * M_PI * (elapsedTime.count() / msPerSecond));
	
	char axis = m->getParameter<char>("axis");
	SDL_FRect*& baseRect = geo->baseRect,
		modRect = geo->modRect;
	
	switch (axis) {
	case 'x':
		modRect->x = baseRect->x - delta;
	case 'y':
		modRect->y = baseRect->y - delta;
	default:
		std::cout << "Invalid parameter 'axis' (" << axis << ") in 2DPosition_SineWave\n";
	}
}

void Animations::linearMotion(Sprite* _s, AnimationEvent* _e) {
	float speed = _e->getParameter<float>("speed");
	char axis = _e->getParameter<char>("axis");
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
	float startSize = _e->getParameter<float>("startSize"), endSize = _e->getParameter<float>("endSize");

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
	double speed = (double)_e->getParameter<float>("speed");
	_s->setAngle(_s->getAngle() + speed);
}

void Animations::sincosRotation(Sprite* _s, AnimationEvent* _e) {
	float a = _e->getParameter<float>("a"), b = _e->getParameter<float>("b");
	char func = _e->getParameter<char>("func");
	unsigned int currentFrame = _e->getCurrentFrame();

	double angle = sin(currentFrame * M_PI * b) * a;
	_s->setAngle(angle);
}

void Animations::opacity(Sprite* _s, AnimationEvent* _e) {
	unsigned int currentFrame = _e->getCurrentFrame();
	unsigned int maxFrames = _e->getMaxFrames();

	float a = _e->getParameter<float>("a");
	if (a > 1.0f) a = 1.0f;
	else if (a < 0.0f) a = 0.0f;
	
	if (maxFrames == 1) {
		SDL_SetTextureAlphaMod(_s->getTexture(), (Uint8)(a * 255));
	}
	else {
		float b = _e->getParameter<float>("b");
		if (b > 1.0f) b = 1.0f;
		else if (b < 0.0f) b = 0.0f;

		SDL_SetTextureAlphaMod(_s->getTexture(), (Uint8)((b * currentFrame + a * (maxFrames - currentFrame)) / maxFrames * 255));
	}
}

void Animations::linearScale(Sprite* _s, AnimationEvent* _e) {
	unsigned int currentFrame = _e->getCurrentFrame();
	unsigned int maxFrames = _e->getMaxFrames();
	char axis = _e->getParameter<char>("axis");
	bool centered = _e->getBool("centered");
	float a = _e->getParameter<float>("a"), b = _e->getParameter<float>("b");

	SDL_FRect* baseRect = _s->getBaseRect(), * dstRect = _s->getDstRect();

	if (axis == 'w') {
		dstRect->w = (a * (maxFrames - currentFrame) + b * currentFrame) / maxFrames;
		if (centered) dstRect->x = baseRect->x + abs(dstRect->w - baseRect->w) / 2;
	}
	else if (axis == 'h') {
		dstRect->h = (a * (maxFrames - currentFrame) + b * currentFrame) / maxFrames;
		if (centered) dstRect->y = baseRect->y + abs(dstRect->h - baseRect->h) / 2;
	}
}

void Animations::colorize(Sprite* _s, AnimationEvent* _e) {
	int r = (int)_e->getParameter<float>("r"), g = (int)_e->getParameter<float>("g"), b = (int)_e->getParameter<float>("b");
	SDL_SetTextureColorMod(_s->getTexture(), r, g, b);
}