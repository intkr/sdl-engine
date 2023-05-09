#pragma once
#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "sprite.h"
#include "animations.h"

enum SpriteType {BACKGROUND, FOREGROUND, POPUP};

class Graphics {
public:
	Graphics(int w, int h);
	~Graphics();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	std::map<std::string, SDL_Texture*>* getTexturePtr();
	std::map<std::string, Sprite*>** getSpritePtr();
	SDL_Texture* getTexture(std::string name);

	// path : File path of the image asset.
	// name : Name to be used as key on std::map.
	bool addTexture(std::string path, std::string name);

	// type : _BG | _FG | _POP
	bool addSprite(SDL_Texture* tex, SDL_Rect* src, SDL_FRect* dst, int type, std::string name, double a = 0);

	// type : _INTRO | _IDLE | _OUTRO
	bool addAnimation(std::string spriteName, std::string aniName, Animation* a, int type);

	void renderScreen();
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
};