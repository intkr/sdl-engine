#pragma once
#include "state.h"

// Base class specifically for minigames
class Game : public State {
public:
	Game(SCore* _score, Core* _core, float exp) : State(_score, _core),
		difficulty(0.0f), gameStatus(_INTRO), gameTimer(60 * 60),
		baseScore(1000), score(0), scoreExponent(exp), currentCombo(0), maximumCombo(0),
		gameElapsedFrames(0), puzzleElapsedFrames(0) {}
	virtual ~Game() {}

	virtual void init() override;
	virtual void update() override;
	virtual void exitState(StateType targetState) override;

protected:
	void setStatus(StatusType status) { gameStatus = status; }
	StatusType getStatus() { return gameStatus; }

	/// <summary>
	/// Creates a new puzzle.
	/// </summary>
	virtual void newPuzzle() = 0;

	/// <summary>
	/// Adjusts the difficulty using several factors.
	/// </summary>
	/// <param name="win">: true if the last puzzle was solved correctly.</param>
	virtual void adjustDifficulty(bool win) = 0;

	virtual void winLevel();
	virtual void loseLevel();


	/// <summary>
	/// Current difficulty of the puzzle.<para/>
	/// Difficulty range differs for every game.
	/// </summary>
	float difficulty;

	/// <summary>
	/// Frames elapsed for the current game.
	/// Excludes intro / outro cutscenes.
	/// </summary>
	int gameElapsedFrames;

	/// <summary>
	/// Frames elapsed for the current puzzle.
	/// </summary>
	int puzzleElapsedFrames;


private:
	/// <summary>
	/// Updates the state timers.
	/// </summary>
	void updateTime();

	/// <summary>
	/// Updates the timer's graphics.
	/// </summary>
	void updateTimer();

	/// <summary>
	/// Current status of the game.<para/>
	/// Used for cutscene purposes.
	/// </summary>
	StatusType gameStatus;

	/// <summary>
	/// Gameplay timer, measured in frames.
	/// Timer starts at 60 seconds (or 3600 frames) by default.
	/// </summary>
	int gameTimer;

	/// <summary>
	/// Current game score.
	/// </summary>
	int score;

	/// <summary>
	/// Base score rewarded per solved puzzle.
	/// </summary>
	int baseScore;

	/// <summary>
	/// Exponent value for combo-score calculation.
	/// </summary>
	float scoreExponent;

	/// <summary>
	/// Current combo.
	/// </summary>
	int currentCombo;

	/// <summary>
	/// Maximum combo achieved during the current game.
	/// </summary>
	int maximumCombo;

	int barWidth;
	int barHeight;
};