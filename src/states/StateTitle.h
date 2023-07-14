#pragma once
#include "state.h"

class StateTitle : public State {
public:
	StateTitle(SCore* _score, Core* _core);
	~StateTitle();
	void init() override;
	void update() override;
	void exitState(StateType targetState) override;

	void handleClick(std::string name, bool active) override;
	void handleKey(SDL_Scancode key, bool active) override;

private:
	void addGearAnimations(Sprite* s, int rotatingFrames, int stopFrames, float rotation, int brightness = 255);
	void addGear(char size, int num, SDL_FRect* dst, double angle, float rotation, int rotatingFrames, int stopFrames, int brightness = 255, int layer = 0);

	void freeAll();
	void freeSpecifics(); // rename to something better

	bool test = true;
};