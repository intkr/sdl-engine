#pragma once
#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "core.h"
#include "sprite.h"
#include "animation.h"

#define SpriteMap std::map<std::string, Sprite*>

class Graphics {
public:
	friend class Core;

	Graphics(Core* core);
	~Graphics();

	SDL_Window* getWindow() { return _window; }
	SDL_Renderer* getRenderer() { return _renderer; }
	
	// Returns a pointer to the texture corresponding to the identifier 'name'.
	// If no such texture exists, returns nullptr.
	SDL_Texture* getTexture(std::string name);

	Sprite* getSprite(std::string name);

	TTF_Font* getFont() { return _font; }
	SDL_Color& getColor(std::string name) { return _colors[name]; }

	SDL_Surface* getTextSurface(std::wstring text, std::string color, int wrapLength);

	// TODO: Fix the currently-used workaround of using addTexture/addSprite to get existing texture/sprite objects

	// Stores texture on memory. Returns true if successful, false otherwise.
	// 
	// path : File path of the image asset.
	// name : Texture object identifier.
	SDL_Texture* addTexture(std::string path, std::string name);
	SDL_Texture* addTexture(SDL_Texture* texture, std::string name);
	
	// Adds sprite to memory. Returns true if successful, false otherwise.
	// 
	// texName : Texture object identifier to use for the sprite.
	// spriteName : Sprite object identifier.
	// src / dst : Rect area used on sprite sheet / sprite render. Pass nullptr to use the entire area.
	// angle : Sprite rotation angle (clockwise).
	Sprite* addSprite(std::string texName, std::string spriteName, SDL_Rect* src, SDL_FRect* dst, SpriteType type, double angle = 0.0);
	Sprite* addSprite(std::string name, SpriteType type, Sprite* s);

	bool deleteTexture(std::string name);

	bool deleteSprite(std::string name, SpriteType type);

	bool setSpriteTexture(std::string spriteName, std::string textureName);

	void renderScreen();

	// Resets internal data by deleting all texture and sprite objects.
	void reset();

	bool hasSprites();
	bool doesPopupExist();

private:
	void emptySprites();
	void emptyTextures();

	void darkenScreen();

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	TTF_Font* _font;
	std::map<std::string, SDL_Color> _colors;

	std::map<std::string, SDL_Texture*> _textures;
	SpriteMap backgroundSprites;
	SpriteMap foregroundSprites;
	SpriteMap popupSprites;
	SpriteMap* _sprites[3];

	Core* core;
};