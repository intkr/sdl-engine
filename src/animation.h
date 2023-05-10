#pragma once

class Sprite;

class Animation {
public:
	
	Animation(float floats[4], int frames, bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*));
	Animation(bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*));
	~Animation();

	// Returns false if the animation has already finished.
	// Otherwise, performs the assigned animation function, and adds 1 to the current frame count. Returns true.
	bool process(Sprite* s);

	// Sets currentFrame to 1, resetting the animation to its initial state.
	void reset() { currentFrame = 1; }

	bool isFinished() { return (currentFrame > animationLength); }
	bool isCompound() { return compound; }
	bool isSequential() { return sequential; }
	bool isLooping() { return looping; }

	// Returns the length (frames) of the animatino.
	unsigned int getAniLength() { return animationLength; }

	// Returns the current frame number of the animation.
	unsigned int getCurrentFrame() { return currentFrame; }

	// deliberately placed in public to reduce duplicate code for accessing data
	float param[4];
private:
	// Animation function from animation.h
	void (*func)(Sprite*, Animation*);

	// true : Loops until outro is triggered. If sequential, the entire sequence loops as a whole.
	// false: Plays once.
	bool looping;

	// true : Subsequent animations will also be played.
	// false: Subsequent animations won't be played until it ends.
	bool compound;

	// true : Only one animation (more if compound) in a group of sequential animations is played at a time.
	// false: Multiple subsequent animations can be played.
	bool sequential;

	unsigned int animationLength;
	unsigned int currentFrame;

};
