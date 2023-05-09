#pragma once
#include <vector>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

enum AnimationType {INTRO, IDLE, OUTRO};

#define AniVector std::vector<std::pair<std::string, Animation*>>

class Animation;

class Sprite {
public:
	Sprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, double a = 0);
	~Sprite();

	SDL_Texture* getTexture();
	SDL_Rect* getSrcRect();
	SDL_FRect* getDstRect();
	SDL_FRect* getBaseRect();
	void setAngle(double a);
	double getAngle();
	bool isVisible();

	void triggerOutro();

	// Updates sprite by processing through its animations.
	// Returns true if sprite is valid and needs to be rendered,
	// false if it finished its animations and needs to be deleted.
	bool updateSprite();

	// index : _INTRO | _IDLE | _OUTRO
	bool addAnimation(std::string name, Animation* a, short index);

	// make functions to edit animation data instead of passing everything as a parameter on initialization
private:
	SDL_Texture* _texture;
	SDL_Rect* srcRect;
	SDL_FRect* baseRect;
	SDL_FRect* dstRect;

	double angle;
	bool visibility;

	// when the user clicks this sprite, return this for callback
	// if this sprite doesn't need a response, set it to its default (CMD_NONE)
	//Command callback;

	// destroy animation when finished (unless idle looping)
	// change status when vector is empty
	AniVector introAnimations;
	AniVector idleAnimations;
	AniVector outroAnimations;
	AniVector* _animations[3];
	short status;
};


class Animation {
public:

	Animation(float floats[4], int frames, bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*));
	Animation(bool loop, bool comp, bool seq, void (*f)(Sprite*, Animation*));
	~Animation();

	// perform func, and add 1 to the current frame count.
	bool process(Sprite* s);

	// set current frame count to 1
	void reset();

	bool isFinished();
	bool isCompound();
	bool isSequential();
	bool isLooping();

	// max frames
	unsigned int getMF();

	// current frames
	unsigned int getCF();

	// deliberately placed in public to reduce duplicate code for accessing data
	float param[4];
private:
	void (*func)(Sprite*, Animation*);

	// true : Loops until outro is triggered. If sequential, the entire sequence loops as a whole.
	// false: Plays once.
	bool looping;

	// true : Subsequent animations will also be played.
	// false: Subsequent animations won't be played until it ends.
	bool compound;

	// true : Only one animation (more if compound) in a group of sequential animations is played at a time.
	// false: Multiple subsequent animations can be played.
	bool sequential;

	unsigned int maxFrames;
	unsigned int currentFrames;

};

bool checkCollision(SDL_FPoint* p, Sprite* s);
bool checkCollision(Sprite* s1, Sprite* s2);