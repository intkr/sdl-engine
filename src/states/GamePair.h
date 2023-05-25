#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "state.h"

#define _PAIR_HEIGHT 4
#define _PAIR_WIDTH 3

struct PairCard {
	int type;
	bool opened;
	PairCard(int n) : type(n), opened(false) {}
};

class GamePair : public State {
public:
	GamePair(Graphics* _g, Input* _i, Audio* _a);
	~GamePair();
	void init() override;
	Command update() override;
	void exitState(Command& cmd) override;
	bool isStateRunning() override;

	Command handleClick(std::string name, bool active) override;
private:
	void newPuzzle();

	// pos : [0,size)
	void createCard(int pos, int type);
	void deleteCards();
	void hideCards();
	void openCard(int pos);
	bool validatePair(int a, int b);

	void winLevel();
	void loseLevel();

	const int cardDisplayFrames = 120; // 2 seconds
	const int resultDisplayFrames = 30; // 0.5 seconds
	int displayTimer;
	int displayStatus; // 0 : card, 1 : result (temporary)
	bool playing;

	int cardTypes;
	int difficulty;
	std::vector<PairCard> cards;

	int remainingPairs;
	int lastCard;
};