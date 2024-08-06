#pragma once
#include <cmath>

#include "SDL.h"

#include "clock.h"
#include "exception.h"

// Commonly used constants
#define PI 3.14159265358979323846
#define MS_PER_SECOND 1000

// Base class for all types of motion frames.
class MotionFrame {
public:
	MotionFrame(ms _duration) : duration(duration), elapsedTime(ms(0)) {}

	void reset() { elapsedTime = ms(0); }
	void updateTime(ms& delta);
	virtual SDL_FRect apply(const SDL_FRect& sourceBox) = 0;

protected:
	ms elapsedTime;
	ms duration;
};

namespace Motions {
	/*
	Simulates a sine function in a rotated axis.
	Equal to the mathematical function "amplitude * sin(frequency*πt)",
	where t = elapsed time (in seconds).

	Parameters
	- amplitude : The size of the sine wave.
	- frequency : The frequency of each sine wave.
	- angle_deg : The angle of the sine wave, in degrees.
	*/
	class SineWave2D : public MotionFrame {
	public:
		SineWave2D(ms duration, double amplitude, double frequency, double angle_deg) :
		  MotionFrame(duration), amp(amplitude), freq(frequency) {
			angle_rad = remainder(angle_deg, 360.0) * 180.0 / PI;
		}

		SDL_FRect apply(const SDL_FRect& sourceBox) override;

	private:
		double amp;
		double freq;
		double angle_rad;
	}
}