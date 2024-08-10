#pragma once
#include <cmath>

#include "SDL.h"

#include "clock.h"
#include "math_operators.h"
#include "math_constants.h"
#include "transform.h"
#include "exception.h"

// Base class for all types of motion frames.
class MotionFrame {
public:
	MotionFrame(ms _duration) : duration(duration), elapsedTime(ms(0)) {}

	void reset() { elapsedTime = ms(0); }
	void updateTime(ms& delta);

	// Signals the frame its beginning, storing the initial position internally.
	// This is done for easier calculations in point-to-point movement, especially targeted ones.
	virtual void begin(const Transform& source) {}

	// Calculates and returns the updated Transform.
	virtual Transform apply(const Transform& source) = 0;

protected:
	ms elapsedTime;
	ms duration;
};

// Reference used for motion calculations:
/*
https://gizma.com/easing/
*/ 

namespace Motions {
	/*
	The object moves to a target position, with linear velocity.

	Parameters
	- target : The desired end position of the object.
	*/
	class Move2D_Linear : public MotionFrame {
	public:
		Move2D_Linear(ms duration, SDL_FPoint& target)
		  : MotionFrame(duration), end(target) {}
		
		void begin(const Transform& source) override {
			start = source.position;
		}

		Transform apply(const Transform& source) override;

	private:
		SDL_FPoint start;
		SDL_FPoint end;
	};

	/*
	The object moves in a sine function on a predetermined, rotated axis.

	Parameters
	- amplitude : The size of the sine wave, in pixels.
	- length : The time to cycle through one sine wave, in seconds.
	- angle : The angle of the sine wave, in degrees.
	*/
	class Move2D_SineWave : public MotionFrame {
	public:
		Move2D_SineWave(ms duration, float amplitude, float length, float angle)
		  : MotionFrame(duration), amp(amplitude), freq(2 * PI / length),
			angle_rad(remainder(angle_deg, 360.0) * 180.0 / PI) {}

		void begin(const Transform& source) override {
			basePos = source.position;
		}
		Transform apply(const Transform& source) override;

	private:
		SDL_FPoint basePos;
		float amp;
		float freq;
		float angle_rad;
	};

	/*
	The object moves to a target position, with easing sine functions.

	Parameters
	- target : The desired end position of the object.
	- easeIn / easeOut : Whether or not to add easing effects.
	*/
	class Move2D_EaseSine : public MotionFrame {
	public:
		Move2D_EaseSine(ms duration, SDL_FPoint& target, bool easeIn, bool easeOut)
		  : MotionFrame(duration), end(target), mode(easeIn + easeOut * 2) {}
		
		void begin(const Transform& source) override {
			start = source.position;
		}

		Transform apply(const Transform& source) override;

	private:
		SDL_FPoint start;
		SDL_FPoint end;
		// Values: None = 0, In, Out, Both
		short mode;
	};

	/*
	The object moves to a target position, overshooting a small amount and easing back.

	Parameters
	- target : The desired end position of the object.
	- strength : Easing strength. Value must be positive.
	- easeIn / easeOut : Whether or not to ease back.
	*/
	class Move2D_EaseBack : public MotionFrame {
	public:
		Move2D_EaseBack(ms duration, SDL_FPoint& target, float strength, bool easeIn, bool easeOut)
		  : MotionFrame(duration), end(target), c(strength), mode(easeIn + easeOut * 2) {}
		
		void begin(const Transform& source) override {
			start = source.position;
		}

		Transform apply(const Transform& source) override;

	private:
		SDL_FPoint start;
		SDL_FPoint end;
		float c;
		// Values: None = 0, In, Out, Both
		short mode;
	};

	/*
	The object rotates from the current angle, with linear angular velocity.

	Parameters
	- velocity : The angular velocity of the object, in degrees per second.
	*/
	class Rotate2D_Linear : public MotionFrame {
	public:
		Rotate2D_Linear(ms duration, double velocity)
		  : MotionFrame(duration), angularVelocity_deg(velocity) {}
		
		void begin(const Transform& source) override {
			startAngle_deg = source.angle_deg;
		}
		Transform apply(const Transform& source) override;

	private:
		double angularVelocity_deg_per_sec;
		double startAngle_deg;
	};

	/*
	The object rotates from the current angle, in a sine function.

	Parameters
	- amplitude : The size of the sine wave, in pixels.
	- length : The time to cycle through one sine wave, in seconds.
	*/
	class Rotate2D_SineWave : public MotionFrame {
	public:
		Rotate2D_SineWave(ms duration, double amplitude, double length)
		  : MotionFrame(duration), amp(amplitude), freq(2 * PI / length) {} 
	
		void begin(const Transform& source) override {
			startAngle_deg = source.angle_deg;
		}
		Transform apply(const Transform& source) override;

	private:
		double startAngle_deg;
		double amp;
		double freq;
	};
}