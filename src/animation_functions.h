#pragma once

class Sprite;
class Animation;

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