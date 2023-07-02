#pragma once

#include <map>
#include <iostream>
#include <Windows.h>
#include <time.h>

#include "SDL.h"
#include "SDL_image.h"

class Graphics;
class Input;
class Audio;
class SCore;
class Player;
class Sprite;

#define SpriteMap std::map<std::string, Sprite*>

class Core {
public:

	Core();
	~Core();

	void gaming();

	/*
	I'm almost sure this implementation is horrible but idk any alternative solutions
	how the fuck do i communicate between objects better
	*/
	
	// Graphics
	SpriteMap** getSpriteMaps();

	// State
	void handleKey(SDL_Scancode id, bool active);
	void handleHover(std::string objName);
	void handleClick(std::string objName, bool active);
	void handleRelease(std::string objName);
	
	// Input
	int checkKeybinds(SDL_Scancode key);

	// (Hopefully temporary) functions used solely for creating Sounds/Sprites.
	Graphics* getGraphics() { return g; }
	Audio* getAudio() { return a; }


private:
	Graphics* g;
	Input* i;
	Audio* a;
	SCore* s;
	Player* p;
};