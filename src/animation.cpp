#include "animation.h"

#include "sprite.h"

Animation::Animation(float floats[4], int frames, bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*)) {
	for (int i = 0; i < _countof(param); i++) param[i] = floats[i];
	animationLength = frames;
	currentFrame = 1;
	looping = loop;
	compound = comp;
	sequential = seq;
	func = f;
}

Animation::Animation(bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*)) {
	for (int i = 0; i < _countof(param); i++) param[i] = 0;
	animationLength = 1;
	currentFrame = 1;
	looping = loop;
	compound = comp;
	sequential = seq;
	func = f;
}

Animation::~Animation() {}

bool Animation::process(Sprite* sprite) {
	if (!isFinished()) {
		func(sprite, this);
		currentFrame++;
		return true;
	}
	return false;
}