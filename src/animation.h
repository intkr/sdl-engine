#pragma once
#define PI 3.141592

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

// Note:
//		Compoundable animations are functions that directly change the properties of baseRect (and consequently, dstRect).
//		Because baseRect and dstRect has equal values, other animations can be added upon compoundable animations.
// 
//		Non-compoundable animations are functions that change the properties of dstRect based on baseRect.
//		Because there is a discrepancy between baseRect and dstRect, other animations can not be added upon non-compoundable animations.
//		However, they are compoundable with animations that control different variables.

// This function is compoundable.
void staticMotion(Sprite* _s, Animation* _a);

// This function is compoundable... not really.
void invisible(Sprite* _s, Animation* _a);

// The x / y position of the sprite moves in a sine / cosine function. (a sin b¥ðt / a cos b¥ðt)
// c decides which axis to move. true = x, false = y
// d decides which function to use. true = sine, false = cosine
// Length of cycle should be 2/b frames.
// This animation is NOT compoundable.
void sincosMotion(Sprite* _s, Animation* _a);

// The x / y position of the sprite moves in a linear function.
// a decides the axis of the motion. true = x, false = y
// The sprite will move at b pixels/frame.
// c decides whether baseRect will also move or not. (true / false)
// The compoundability of this animation is decided as the inverse value of c.
void linearMotion(Sprite* _s, Animation* _a);

// The size of the sprite increases from multiplier a to multiplier b.
// It resizes with its center as a fixed point.
// This animation is NOT compoundable.
void resizeCenteredMotion(Sprite* _s, Animation* _a);

// The sprite rotates clockwise indefinitely, a degrees per frame.
// This animation is compoundable.
void linearRotation(Sprite* _s, Animation* _a);

// The rotation of the sprite changes in a sine function. (a sin b¥ðt)
// Length of cycle should be 2/b frames.
// This animation is NOT compoundable.
void sinRotation(Sprite* _s, Animation* _a);

// Sets the opacity of the sprite across a set amount of frames. If it equals 1, opacity is static.
// If opacity is static, it's set to a. Otherwise, it changes from a to b. (a,b = 0~255)
// This animation is NOT compoundable.
// WARNING - This affects the texture, not the sprite. All sprites that uses the same texture will be affected.
void opacity(Sprite* _s, Animation* _a);