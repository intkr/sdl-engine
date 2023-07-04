#pragma once
#include "state.h"

// Base class specifically for minigames
class Game : public State {
public:
	Game(SCore* _score, Core* _core) : State(_score, _core),
		difficulty(0.0f), gameStatus(_INTRO), gameTimer(60 * 60),
		baseScore(1000), score(0), scoreExponent(1.0f), currentCombo(0), maximumCombo(0),
		gameElapsedFrames(0), puzzleElapsedFrames(0) {}
	virtual ~Game() {}

protected:
	virtual void newPuzzle() = 0;
	virtual void winLevel();
	virtual void loseLevel();
	virtual void adjustDifficulty(bool won) = 0;

	void updateTime() { gameTimer--; gameElapsedFrames++; puzzleElapsedFrames++; }

	float difficulty;
	StatusType gameStatus;

	// Timer for gameplay, in frames.
	// Timer starts at 60 seconds (3600 frames) on default.
	int gameTimer;

	// Elapsed frames for current game.
	int gameElapsedFrames;

	// Elapsed frames for current puzzle.
	// Used to adjust difficulty.
	int puzzleElapsedFrames;

	// User's game score.
	int score;

	// Base game score rewarded per puzzle.
	int baseScore;

	// Exponent value for combo-score calculation.
	float scoreExponent;

	int currentCombo;
	int maximumCombo;
};