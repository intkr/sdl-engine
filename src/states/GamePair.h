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
	void adjustDifficulty(bool won) override;

	// pos : [0,size)
	void createCard(int pos, int type);
	void deleteCards();
	void hideCards();
	void openCard(int pos);
	bool validatePair(int a, int b);
	void interactCard(int cardPos);

	const int cardDisplayFrames = 120; // 2 seconds - maybe allow shrinking this for difficulty
	const int resultDisplayFrames = 30; // 0.5 seconds
	int displayTimer;
	bool playing;

	int cardTypes;
	std::vector<PairCard> cards;

	int remainingPairs;
	int lastCard;
};