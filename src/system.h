#pragma once

#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "player.h"
#include "clock.h"
#include "states/controller.h"

class System {
public:
	System();
	~System();
	
	void loop();
	
private:
	void updateGame();
	void render();
	void updateTime();
	void limitFPS();
	void checkForQuitTrigger();
	
	Player* p;
	Graphics* g;
	Audio* a;
	Input* i;
	Clock* c;
	StateController* s;
	
	bool gaming;
	
	// temporary until player settings are implemented
	int fps = 60;
};
