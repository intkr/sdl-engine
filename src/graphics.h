#pragma once
#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "texture.h"
#include "renderer.h"
#include "exceptions.h"

// TODO: split font-related stuff and sprite-related stuff into separate classes

class Graphics {
public:
	static Graphics* getGraphics();
	static void deleteGraphics();
	static Renderer* getRenderer();

	void createTextureFromText(std::string name, std::wstring text, TextAttribute attribute, int wrapLength);
	void createTextureFromImage(std::string name, std::string path, std::string name);
	SDL_Texture* getTexture(std::string name);
	bool doesTextureExist(std::string name);

	void deleteAllAssets();
	void deleteTexture(std::string name);

private:
	static Graphics* _graphics;

	Graphics();
	~Graphics();
	
	void initSDL();
	void loadFonts();
	void addNewFont(std::string name, std::string path, int ptSize);
	void addNewColor(std::string name, int r, int b, int g, int a);

	SDL_Color& getColor(std::string name);
	SDL_Surface* getTextSurface(std::wstring text, SDL_Color& color, int wrapLength);

	SDL_Texture* createTextureFromImage(std::string path);
	SDL_Surface* createSurfaceFromImage(std::string path);
	
	void deleteAllTextures();

	SDL_Window* window;
	Renderer* renderer;
	
	// TODO: check how much memory each TTF_Font object uses.
	// If it is somewhat huge, then consider having one TTF_Font* and load a new font every time it needs to be changed.
	// In such case, fonts should be map<font name, font path> instead.
	
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, SDL_Color> colors;
	std::map<std::string, SDL_Texture*> textures;
	std::vector<Sprite*> sprites;
};
