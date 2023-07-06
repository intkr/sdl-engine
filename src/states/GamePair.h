#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <math.h>

#include "game.h"

#define _PAIR_HEIGHT 4
#define _PAIR_WIDTH 3

struct PairCard {
	int type;
	bool opened;
	PairCard(int n) : type(n), opened(false) {}
};

class GamePair : public Game {
public:
	GamePair(SCore* _score, Core* _core);
	~GamePair();

	void init() override;
	void update() override;
	void exitState(StateType targetState) override;

	void handleClick(std::string name, bool active) override;
	void handleKey(SDL_Scancode key, bool active) override;

private:
	void newPuzzle() override;
	void winLevel() override;
	void loseLevel() override;
	void adjustDifficulty(bool win) override;

	// pos : [0,size)

	/// <summary>
	/// Creates a card sprite.
	/// </summary>
	/// <param name="pos">: Card position, 0 ~ 11.</param>
	/// <param name="type">: Card type, 0 ~ (cardTypes - 1).</param>
	void createCard(int pos, int type);

	/// <summary>
	/// Deletes a card sprite.
	/// </summary>
	void deleteCards();

	/// <summary>
	/// Triggers a card hiding animation.
	/// </summary>
	void hideCards();

	/// <summary>
	/// Triggers a card opening animation and opens the card.
	/// </summary>
	/// <param name="pos">: Card position, 0 ~ 11.</param>
	void openCard(int pos);

	/// <summary>
	/// Checks if the two last chosen cards are a valid pair.
	/// </summary>
	/// <param name="a">: First card position.</param>
	/// <param name="b">: Second card position.</param>
	/// <returns>true if valid, false otherwise.</returns>
	bool validatePair(int a, int b);

	/// <summary>
	/// Interacts with a card.
	/// </summary>
	/// <param name="pos"></param>
	void interactCard(int pos);

	/// <summary>
	/// Length of time displaying the cards, in frames.
	/// </summary>
	const int cardDisplayFrames = 120;

	/// <summary>
	/// Length of time displaying the result, in frames.
	/// </summary>
	const int resultDisplayFrames = 30;

	/// <summary>
	/// Timer for displaying sprites.
	/// </summary>
	int displayTimer;

	/// <summary>
	/// Number of types of cards available.
	/// </summary>
	int cardTypes;

	/// <summary>
	/// List of cards.
	/// </summary>
	std::vector<PairCard> cards;

	/// <summary>
	/// Number of pairs remaining in this puzzle.
	/// </summary>
	int remainingPairs;

	/// <summary>
	/// Last card picked before two cards were validated.
	/// </summary>
	int lastCard;
};