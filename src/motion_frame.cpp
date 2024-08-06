#include "motion_frame.h"

void MotionFrame::updateTime(ms& delta) {
	ms remainingTime = duration - elapsedTime;

	if (delta <= remainingTime) {
		elapsedTime += delta;
	}
	else {
		elapsedTime = duration;
	}

	delta -= remainingTime;
}

SDL_FRect Motions::SineWave2D::apply(const SDL_FRect& sourceBox) {
	SDL_FRect box = sourceBox;

	double distance = amplitude * sin(frequency * PI * ((double)elapsedTime.count() / MS_PER_SECOND));

	box.x += (float)(distance * cos(angle_rad));
	box.y += (float)(distance * sin(angle_rad) * -1);

	return box;
}

