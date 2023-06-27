#pragma once
#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

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
	// If no such texture exists, returns nullptr.
	SDL_Texture* getTexture(std::string name);

	Sprite* getSprite(std::string name);

	TTF_Font* getFont() { return _font; }
	SDL_Color& getColor(std::string name) { return _colors[name]; }

	SDL_Surface* getTextSurface(std::wstring text, std::string color, int wrapLength);

	// Stores texture on memory. Returns true if successful, false otherwise.
	// 
	// path : File path of the image asset.
	// name : Texture object identifier.
	bool addTexture(std::string path, std::string name);
	bool addTexture(SDL_Texture* texture, std::string name);
	
	// Adds sprite to memory. Returns true if successful, false otherwise.
	// 
	// tex : Texture to use for the sprite. Use getTexture().
	// src / dst : Rect area used on sprite sheet / sprite render. Pass nullptr to use the entire area.
	// name : Sprite object identifier.
	// angle : Sprite rotation angle (clockwise).
	bool addSprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, SpriteType type, std::string name, double angle = 0.0);

	bool deleteTexture(std::string name);

	bool deleteSprite(std::string name, SpriteType type);

	bool setSpriteTexture(std::string spriteName, std::string textureName);

	void renderScreen();

	// Resets internal data by deleting all texture and sprite objects.
	void reset();

	bool hasSprites();
	bool doesPopupExist();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	TTF_Font* _font;
	std::map<std::string, SDL_Color> _colors;

	std::map<std::string, SDL_Texture*> _textures;
	std::map<std::string, Sprite*> backgroundSprites;
	std::map<std::string, Sprite*> foregroundSprites;
	std::map<std::string, Sprite*> popupSprites;
	std::map<std::string, Sprite*>* _sprites[3];

	void emptySprites();
	void emptyTextures();

	void darkenScreen();
};