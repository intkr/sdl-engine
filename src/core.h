#pragma once

#include <map>
#include <iostream>
#include <Windows.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "player.h"
#include "states/score.h"

// Core of the game.
class Core {
public:
	Core();
	~Core();

	/// <summary>
	/// Main game loop.
	/// </summary>
	void loop();

	/// <summary>
	/// Quits game.
	/// </summary>
	void quit() { gaming = false; }

	Graphics* getGraphics() { return g; }
	Input* getInput() { return i; }
	Audio* getAudio() { return a; }
	Player* getPlayer() { return p; }
	SCore* getSCore() { return s; }

private:
	bool gaming;
	Graphics* g;
	Input* i;
	Audio* a;
	SCore* s;
	Player* p;
};