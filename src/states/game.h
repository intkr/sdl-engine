#pragma once
#include "state.h"

// Base class specifically for minigames
class Game : public State {
public:
	Game(Graphics* _g, Input* _i, Audio* _a) : State(_g, _i, _a),
											   difficulty(0.0f) {}
	virtual ~Game() {}

protected:
	virtual void newPuzzle() = 0;
	virtual void winLevel() = 0;
	virtual void loseLevel() = 0;
	virtual void adjustDifficulty() = 0;

	float difficulty;

	TimelineType gameTimeline;

private:

};