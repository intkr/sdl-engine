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

Transform Motions::Move2D_SineWave::apply(const Transform& source) {
	Transform transform = source;

	float distance = amplitude * sin(frequency * PI * ((float)elapsedTime.count() / MS_PER_SECOND));
	transform.position.x = basePos.x + distance * cos(angle_rad);
	transform.position.y = basePos.y + distance * -sin(angle_rad);

	return transform;
}

Transform Motions::Move2D_Linear::apply(const Transform& source) {
	Transform transform = source;

	float x = (float)elapsedTime.count() / duration.count();
	transform.position = start + (end-start) * x;

	return transform;
}

Transform Motions::Move2D_EaseSine::apply(const Transform& source) {
	Transform transform = source;

	float x = (float)elapsedTime.count() / duration.count();
	float easeValue;
	switch (mode) {
	case 1: // In
		easeValue = 1 - cos(x * PI/2);
		break;

	case 2: // Out
		easeValue = sin(x * PI/2);
		break;

	case 3: // Both
		easeValue = -(cos(x * PI) - 1) / 2;
		break;

	case 0: // None
	default: // (Shouldn't be used)
		easeValue = x;
		break;
	}
	transform.position = start + (end-start) * easeValue;

	return transform;
}

Transform Motions::Move2D_EaseBack::apply(const Transform& source) {
	Transform transform = source;

	float x = (float)elapsedTime.count() / duration.count();
	float easeValue;
	switch (mode) {
	case 1: // In
		easeValue = (c+1) * pow(x, 3) - c * pow(x, 2);
		break;

	case 2: // Out
		easeValue = 1 + (c+1) * pow(x-1, 3) + c * pow(x-1, 2);
		break;

	case 3: // Both
		if (x < 0.5f) {
			easeValue = pow(x*2, 2) * ((c*1.525 + 1) * (x*2) - (c*1.525)) / 2;
		}
		else {
			easeValue = pow(x*2 - 2, 2) * ((c*1.525 + 1) * (x*2 - 2) + (c*1.525) + 2) / 2;
		}
		break;

	case 0: // None
	default: // (Shouldn't be used)
		easeValue = x;
		break;
	}
	transform.position = start + (end-start) * easeValue;

	return transform;
}

Transform Motions::Rotate2D_Linear::apply(const Transform& source) {
	Transform transform = source;
	
	transform.angle_deg = startAngle_deg + angularVelocity_deg_per_sec * (elapsedTime.count()/MS_PER_SECOND);

	return transform;
}

Transform Motions::Rotate2D_SineWave::apply(const Transform& source) {
	Transform transform = source;

	double x = (double)elapsedTime.count() / MS_PER_SECOND;
	transform.angle_deg = startAngle_deg + sin(x * freq) * amp;

	return transform;
}