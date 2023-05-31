#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

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
	GamePair(Graphics* _g, Input* _i, Audio* _a);
	~GamePair();
	void init() override;
	Command update() override;
	void exitState(Command& cmd) override;
	bool isStateRunning() override;

	Command handleClick(std::string name, bool active) override;

private:
	void newPuzzle() override;
	void winLevel() override;
	void loseLevel() override;
	void adjustDifficulty() override;

	// pos : [0,size)
	void createCard(int pos, int type);
	void deleteCards();
	void hideCards();
	void openCard(int pos);
	bool validatePair(int a, int b);


	int cardDisplayFrames = 90;		// default : 1.5 seconds
	int resultDisplayFrames = 30;	// default : 0.5 seconds

	int displayTimer;

	int cardTypes;
	std::vector<PairCard> cards;

	int remainingPairs;
	int lastCard;
};