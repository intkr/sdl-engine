#pragma once
#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "sprite.h"
#include "animation.h"


class Graphics {
public:
	friend class Input;

	Graphics(int w, int h);
	~Graphics();

	SDL_Window* getWindow() { return _window; }
	SDL_Renderer* getRenderer() { return _renderer; }
	
	// Returns a pointer to the texture corresponding to the identifier 'name'.
	// If no such texture exists, returns NULL.
	SDL_Texture* getTexture(std::string name);

	// Stores texture on memory. Returns true if successful, false otherwise.
	// 
	// path : File path of the image asset.
	// name : Texture object identifier.
	bool addTexture(std::string path, std::string name);
	
	// Adds sprite to memory. Returns true if successful, false otherwise.
	// 
	// tex : Texture to use for the sprite. Use getTexture().
	// src / dst : Rect area used on sprite data / screen. Pass NULL to use the entire area.
	// name : Sprite object identifier.
	// angle : Sprite rotation angle (clockwise).
	bool addSprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, SpriteType type, std::string name, double angle = 0.0);

	// Adds animation to sprite data. Returns true if successful, false otherwise.
	//
	// spriteName : Sprite object identifier.
	// aniName : Animation object identifier.
	// a : Animation object. Must be dynamically allocated.
	bool addAnimation(std::string spriteName, std::string aniName, Animation* a, AnimationType type);

	void renderScreen();

	// Resets internal data by deleting all texture and sprite data.
	void reset();

	// Forces the current screen to end by setting every sprite to the outro state.
	void triggerOutro();

	bool hasSprites();
	bool doesPopupExist();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Texture*> _textures;
	std::map<std::string, Sprite*> backgroundSprites;
	std::map<std::string, Sprite*> foregroundSprites;
	std::map<std::string, Sprite*> popupSprites;
	std::map<std::string, Sprite*>* _sprites[3];

	void emptySprites();
	void emptyTextures();

	void darkenScreen();
};