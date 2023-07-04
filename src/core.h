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
enum SpriteType;
enum AudioType;

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
	SDL_Texture* strToTexture(std::wstring text, std::string color, int wrapLength);
	SDL_Texture* addTexture(std::string path, std::string name);
	SDL_Texture* addTexture(SDL_Texture* tex, std::string name);
	bool deleteTexture(std::string name);

	Sprite* addSprite(std::string name, SpriteType type, Sprite* s);
	bool deleteSprite(std::string name, SpriteType type);

	// State
	void handleKey(SDL_Scancode id, bool active);
	void handleHover(std::string objName);
	void handleClick(std::string objName, bool active);
	void handleRelease(std::string objName);
	
	// Input
	int checkKeybinds(SDL_Scancode key);

	// Audio
	bool addSound(std::string path, std::string name, bool isLoop, bool isStream);
	bool playSound(std::string name, AudioType type, int volume);
	bool pauseSound(std::string name);

private:
	Graphics* g;
	Input* i;
	Audio* a;
	SCore* s;
	Player* p;
};