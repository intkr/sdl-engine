#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "state.h"

#define _PAIR_HEIGHT 4
#define _PAIR_WIDTH 3

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

	const int displayFrames = 120; // 2 seconds
	int displayTimer;
	bool playing;

	int cardTypes;
	int difficulty;
	std::vector<int> cards;
};