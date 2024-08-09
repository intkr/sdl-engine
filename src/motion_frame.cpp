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
	SDL_FPoint sourcePoint = getBoxCenter(sourceBox);
	SDL_FRect newBox = setBoxPosition(sourceBox, apply(sourcePoint));
	return newBox;
}

SDL_FPoint Motions::SineWave2D::apply(const SDL_FPoint& sourcePoint) {
	SDL_FPoint point = sourcePoint;

	float distance = amplitude * sin(frequency * PI * ((float)elapsedTime.count() / MS_PER_SECOND));

	point.x += distance * cos(angle_rad);
	point.y += distance * sin(angle_rad) * -1;

	return point;
}

SDL_FRect Motions::Move2D_Linear::apply(const SDL_FRect& sourceBox) {
	SDL_FPoint sourcePoint = getBoxCenter(sourceBox);
	SDL_FRect newBox = setBoxPosition(sourceBox, apply(sourcePoint));
	return newBox;
}

SDL_FPoint Motions::Move2D_Linear::apply(const SDL_FPoint& sourcePoint) {
	SDL_FPoint point;
	float percentage = (float)elapsedTime.count() / duration.count();
	point = start + (end - start) * percentage;
	return point;
}

SDL_FRect Motions::Move2D_EaseSine::apply(const SDL_FRect& sourceBox) {
	SDL_FPoint sourcePoint = getBoxCenter(sourceBox);
	SDL_FRect newBox = setBoxPosition(sourceBox, apply(sourcePoint));
	return newBox;
}

SDL_FPoint Motions::Move2D_EaseSine::apply(const SDL_FPoint& sourcePoint) {
	SDL_FPoint point;
	float percentage = (float)elapsedTime.count() / duration.count();
	float sineValue;
	switch (mode) {
	case 1: // In
		sineValue = 1 - cos(percentage * PI / 2);
		break;

	case 2: // Out
		sineValue = sin(percentage * PI / 2);
		break;

	case 3: // Both
		sineValue = -(cos(percentage * PI) - 1) / 2;
		break;

	case 0: // None
	default: // (Shouldn't be used)
		sineValue = percentage;
		break;
	}

	point = start + (end - start) * sineValue;
	return point;
}

SDL_FRect Motions::Move2D_EaseBack::apply(const SDL_FRect& sourceBox) {
	SDL_FPoint sourcePoint = getBoxCenter(sourceBox);
	SDL_FRect newBox = setBoxPosition(sourceBox, apply(sourcePoint));
	return newBox;
}

SDL_FPoint Motions::Move2D_EaseBack::apply(const SDL_FPoint& sourcePoint) {
	SDL_FPoint point;
	float percentage = (float)elapsedTime.count() / duration.count();
	float sineValue;
	switch (mode) {
	case 1: // In
		sineValue = 1 - cos(percentage * PI / 2);
		break;

	case 2: // Out
		sineValue = sin(percentage * PI / 2);
		break;

	case 3: // Both
		sineValue = -(cos(percentage * PI) - 1) / 2;
		break;

	case 0: // None
	default: // (Shouldn't be used)
		sineValue = percentage;
		break;
	}

	point = start + (end - start) * sineValue;
	return point;
}