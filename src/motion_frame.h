#pragma once
#include <cmath>

#include "SDL.h"

#include "clock.h"
#include "exception.h"

// Commonly used constants
#define PI 3.14159265358979323846f
#define MS_PER_SECOND 1000

// Base class for all types of motion frames.
class MotionFrame {
public:
	MotionFrame(ms _duration) : duration(duration), elapsedTime(ms(0)) {}

	void reset() { elapsedTime = ms(0); }
	void updateTime(ms& delta);

	// Signals the frame its beginning, storing the initial position internally.
	// This is done for easier calculations in point-to-point movement, especially targeted ones.
	virtual void begin(const SDL_FPoint& point);
	virtual void begin(const SDL_FRect& box);

	// Calculates and returns the new values based on the parameter.
	virtual SDL_FRect apply(const SDL_FRect& sourceBox) = 0;
	virtual SDL_FPoint apply(const SDL_FPoint& sourcePoint) = 0;

protected:
	ms elapsedTime;
	ms duration;
};

// Reference used for motion calculations:
/*
https://gizma.com/easing/
*/ 

namespace Motions {
	SDL_FRect setBoxPosition(const SDL_FRect& box, const SDL_FPoint& newPos) {
		SDL_FRect newBox = box;
		newBox.x = newPos.x, newBox.y = newPos.y;
		return newBox;
	}

	SDL_FPoint getBoxCenter(const SDL_FRect& box) {
		SDL_FPoint point = { box.x + box.w / 2, box.y  + box.h / 2 };
		return point;
	}

	/*
	The object moves in a sine function on a predetermined, rotated axis.

	Parameters
	- amplitude : The size of the sine wave, in pixels.
	- length : The time to cycle through one sine wave, in seconds.
	- angle_deg : The angle of the sine wave, in degrees.
	*/
	class SineWave2D : public MotionFrame {
	public:
		SineWave2D(ms duration, float amplitude, float length, float angle_deg) :
		  MotionFrame(duration), amp(amplitude), freq(2 * PI / length),
		  angle_rad(remainder(angle_deg, 360.0) * 180.0 / PI) {}

		SDL_FRect apply(const SDL_FRect& sourceBox) override;
		SDL_FPoint apply(const SDL_FPoint& sourcePoint) override;

	private:
		float amp;
		float freq;
		float angle_rad;
	}

	/*
	The object moves to a target position, linearly.

	Parameters
	- target : The desired end position of the object.
	*/
	class Move2D_Linear : public MotionFrame {
	public:
		Move2D_Linear(ms duration, SDL_FPoint& target) :
		  MotionFrame(duration), end(target) {}
		
		void begin(const SDL_FPoint& point) override {
			start = point;
		}
		void begin(const SDL_FRect& box) override {
			start = SDL_FPoint{ box.x, box.y };
		}

		SDL_FRect apply(const SDL_FRect& sourceBox) override;
		SDL_FPoint apply(const SDL_FPoint& sourcePoint) override;

	private:
		SDL_FPoint start;
		SDL_FPoint end;
	}

	/*
	The object moves to a target position, with easing sine functions.

	Parameters
	- target : The desired end position of the object.
	- easeIn / easeOut : Whether or not to add easing effects.
	*/
	class Move2D_EaseSine : public MotionFrame {
	public:
		Move2D_EaseSine(ms duration, SDL_FPoint& target, bool easeIn, bool easeOut) :
		  MotionFrame(duration), end(target), mode(easeIn + easeOut * 2) {}
		
		void begin(const SDL_FPoint& point) override {
			start = point;
		}
		void begin(const SDL_FRect& box) override {
			start = SDL_FPoint{ box.x, box.y };
		}

		SDL_FRect apply(const SDL_FRect& sourceBox) override;
		SDL_FPoint apply(const SDL_FPoint& sourcePoint) override;

	private:
		SDL_FPoint start;
		SDL_FPoint end;
		// Values: None = 0, In, Out, Both
		short mode;
	}

	/*
	The object moves to a target position, overshooting a small amount and easing back.

	Parameters
	- target : The desired end position of the object.
	- easeIn / easeOut : Whether or not to ease back.
	*/
	class Move2D_EaseBack : public MotionFrame {
	public:
	// unfinished
		Move2D_EaseBack(ms duration, SDL_FPoint& target, bool easeIn, bool easeOut) :
		  MotionFrame(duration), end(target), mode(easeIn + easeOut * 2) {}
		
		void begin(const SDL_FPoint& point) override {
			start = point;
		}
		void begin(const SDL_FRect& box) override {
			start = SDL_FPoint{ box.x, box.y };
		}

		SDL_FRect apply(const SDL_FRect& sourceBox) override;
		SDL_FPoint apply(const SDL_FPoint& sourcePoint) override;

	private:
		SDL_FPoint start;
		SDL_FPoint end;
		// Values: None = 0, In, Out, Both
		short mode;
	}
}