#pragma once

class Input;
class Audio;
class Graphics;

// base class, add more stuff in the future if necessary
class State {
public:
	State(Graphics* _g, Input* _i, Audio* _a);
	~State();

	virtual void init() = 0;
	
	// Returns 0 if the screen state shouldn't change;
	// otherwise returns screen state key value
	virtual int update() = 0;

	// Check for sprite and audio data.
	// If there are no sprites available and no sound is playing,
	// assume the game is going to transition into a new state and return false.
	// Otherwise, return true.
	virtual bool isStateRunning();
protected:
	Graphics* g;
	Input* i;
	Audio* a;
};