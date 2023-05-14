#pragma once

class Sprite;
class AnimationEvent;

namespace Animations {
	// Sprite has no movement.
	void staticMotion(Sprite* _s, AnimationEvent* _e);

	// Sprite has width and height of 0, thus becoming invisible.
	// As such, invisible sprites are not interactable.
	void invisible(Sprite* _s, AnimationEvent* _e);

	// The x / y position of the sprite moves in a sine / cosine function. (a sin b��t / a cos b��t)
	// c decides which axis to move. true = x, false = y
	// d decides which function to use. true = sine, false = cosine
	// Length of cycle should be 2/b frames.
	// This animation is NOT compoundable.

	// The [x / y] position of the sprite moves in a [sine / cosine] function. (a sin b��t / a cos b��t)
	// 'a' (float) : Amplitude, 'a' in the equation.
	// 'b' (float) : Angular frequency, 'b' in the equation.
	//		Length of the cycle should be 2/b frames.
	// 'axis' (char) : 'x' or 'y', defines the axis the function operates on.
	// 'func' (char) : 's'(sine) or 'c'(cosine), the type of the function.
	void sincosMotion(Sprite* _s, AnimationEvent* _e);

	// The [x / y] position of the sprite moves in a linear function.
	// 'speed' (float) : Defines how much the sprite moves, pixels/frame.
	// 'axis' (char) : 'x' or 'y', defines the axis the function operates on.
	// 'baseMove' (bool) : If true, the actual sprite position and the animated position both changes.
	//		If false, only the animated position changes - subsequent animations may have undesired behavior.
	void linearMotion(Sprite* _s, AnimationEvent* _e);

	// The size of the sprite changes from multiplier a to multiplier b.
	// It resizes with its center as a fixed point.
	// 'startSize' (float) : Multiplier starting point.
	// 'endSize' (float) : Multiplier ending point.
	void resizeCenteredMotion(Sprite* _s, AnimationEvent* _e);

	// The angle of the sprite changes in a linear function.
	// 'speed' (float) : Angular speed, degrees/frame.
	void linearRotation(Sprite* _s, AnimationEvent* _e);

	// The angle of the sprite changes in a [sine / cosine] function. (a sin b��t / a cos b��t)
	// 'a' (float) : Amplitude, 'a' in the equation.
	// 'b' (float) : Angular frequency, 'b' in the equation.
	//		Length of the cycle should be 2/b frames.
	// 'func' (char) : 's'(sine) or 'c'(cosine), the type of the function.
	void sincosRotation(Sprite* _s, AnimationEvent* _e);

	// Sets the opacity of the sprite across a set amount of frames. If it equals 1, opacity is static.
	// If opacity is static, it's set to a. Otherwise, it changes from a to b. (a,b = 0~255)
	// This animation is NOT compoundable.
	// WARNING - This affects the texture, not the sprite. All sprites that uses the same texture will be affected.
	//void opacity(Sprite* _s, AnimationEvent* _e);
	// TODO: fix this ^
}

