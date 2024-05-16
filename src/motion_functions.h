#pragma once

#include <math.h>

#include "geometry.h"
#include "motion.h"
#include "exception.h"

namespace Motions {
	/*
	 The [x / y] position of the target moves in a sine function.
	 The function is equal to 'amplitude * sin(frequency*πt)',
	 where t = elapsed time (in seconds).
	 
	 Parameters:
	 "amplitude" (float) : The size of the sine wave.
	 "frequency" (float) : The frequency of each sine wave.
	 "axis" (char) : The axis to apply the function to. Value must either be 'x' or 'y'.
	*/
	void Position2D_SineWave(Geometry* geo, Motion* m);

	/*
	 The [x / y] position of the target moves in a cosine function.
	 The function is equal to 'amplitude * cos(frequency*πt)',
	 where t = elapsed time (in seconds).
	 
	 Parameters:
	 "amplitude" (float) : The size of the sine wave.
	 "frequency" (float) : The frequency of each sine wave.
	 "axis" (char) : The axis to apply the function to. Value must either be 'x' or 'y'.
	*/
	void Position2D_CosineWave(Geometry* geo, Motion* m);

	/*
	The target moves towards a destination point.
	
	Parameters:
	
	*/
	void Position2D_(Geometry* geo, Motion* m);
	
	
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

///
/// Rotation
///
	
	// The angle of the sprite changes in a linear function.
	// 'speed' (float) : Angular speed, degrees/frame.
	void linearRotation(Sprite* _s, AnimationEvent* _e);

	// The angle of the sprite changes in a [sine / cosine] function. (a sin b¥ðt / a cos b¥ðt)
	// 'a' (float) : Amplitude, 'a' in the equation.
	// 'b' (float) : Angular frequency, 'b' in the equation.
	//		Length of the cycle should be 2/b frames.
	// 'func' (char) : 's'(sine) or 'c'(cosine), the type of the function.
	void sincosRotation(Sprite* _s, AnimationEvent* _e);

///
/// Etc.
/// 

	// The width or height of the sprite changes from length a to b in a linear function.
	// 'axis' (char) : 'w' (width) or 'h' (height), defines the property to scale.
	// 'a' (float) : Initial length.
	// 'b' (float) : Final length.
	// 'centered' (bool) : If true, the sprite scales based on its center point.
	void linearScale(Sprite* _s, AnimationEvent* _e);

	// The opacity of the sprite changes in a linear function.
	// 'a' (float) : Initial opacity, [0.0-1.0].
	// 'b' (float) : Final opacity, [0.0-1.0].
	void opacity(Sprite* _s, AnimationEvent* _e);

	// Sprite has width and height of 0, thus becoming intangible.
	// As such, intangible sprites are not interactable.
	void intangible(Sprite* _s, AnimationEvent* _e);

	// Overlays a preset color on a texture.
	// 'r', 'g', 'b' (float) : The rgb value of the overlay color, [0-255]. Defaults to 0.
	void colorize(Sprite* _s, AnimationEvent* _e);
}
