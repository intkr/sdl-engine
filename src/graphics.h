#pragma once
#include <map>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "sprite.h"
#include "animation.h"

#define SpriteMap std::map<std::string, Sprite*>

class Core;

class Graphics {
public:
	Graphics(Core* core);
	~Graphics();

	SDL_Window* getWindow() { return _window; }
	SDL_Renderer* getRenderer() { return _renderer; }
	
	/// <summary>
	/// Returns a texture.
	/// </summary>
	/// <param name="name">: Texture name.</param>
	/// <returns>Pointer to the texture object if found, nullptr otherwise.</returns>
	SDL_Texture* getTexture(std::string name);

	/// <summary>
	/// Returns a sprite.
	/// </summary>
	/// <param name="name">: Sprite name.</param>
	/// <returns>Pointer to the sprite object if found, nullptr otherwise.</returns>
	Sprite* getSprite(std::string name);

	/// <summary>
	/// Returns the only existing font. (for now)
	/// </summary>
	/// <returns>TTF_Font object for the NanumSquare_acEB font.</returns>
	TTF_Font* getFont() { return _font; }

	/// <summary>
	/// Returns a text color.
	/// TODO: Create a failsafe for nonexistent color names
	/// </summary>
	/// <param name="name">: Color name.</param>
	/// <returns>SDL_Color of the requested color.</returns>
	SDL_Color& getColor(std::string name);

	/// <summary>
	/// Creates and returns a SDL_Texture object of a Unicode text.
	/// </summary>
	/// <param name="text">: Wide string text.</param>
	/// <param name="color">: Text color.</param>
	/// <param name="wrapLength">: Maximum length of pixels of a single row of text.</param>
	/// <returns>SDL_Texture object if successful, nullptr otherwise.</returns>
	SDL_Texture* getTextTexture(std::wstring text, std::string color, int wrapLength);

	/// <summary>
	/// Creates and returns a SDL_Texture object of a Unicode text.
	/// </summary>
	/// <param name="text">: Wide string text.</param>
	/// <param name="color">: Text color.</param>
	/// <param name="wrapLength">: Maximum length of pixels of a single row of text.</param>
	/// <returns>SDL_Texture object if successful, nullptr otherwise.</returns>
	SDL_Texture* getTextTexture(std::wstring text, SDL_Color& color, int wrapLength);

	/// <summary>
	/// Creates a texture from an image and adds it to memory.
	/// </summary>
	/// <param name="path">: Image file path.</param>
	/// <param name="name">: Texture name.</param>
	/// <returns>SDL_Texture object corresponding to 'name', or nullptr if unsuccessful.</returns>
	SDL_Texture* addTexture(std::string path, std::string name);

	/// <summary>
	/// Adds an existing texture to memory.
	/// </summary>
	/// <param name="texture">: Texture to store.</param>
	/// <param name="name">: Texture name.</param>
	/// <returns>SDL_Texture object corresponding to 'name', or nullptr if unsuccessful.</returns>
	SDL_Texture* addTexture(SDL_Texture* texture, std::string name);
	
	// TODO: check if angle is in degrees or radians (i forgor)

	/// <summary>
	/// Creates a sprite and adds it to memory.
	/// </summary>
	/// <param name="texName">: Texture name.</param>
	/// <param name="spriteName">: Sprite name.</param>
	/// <param name="src">: TODO: how do i word this</param>
	/// <param name="dst">: ^</param>
	/// <param name="type">: Sprite type - _BACKGROUND, _FOREGROUND, or _POPUP.</param>
	/// <param name="angle">: Rotation angle of the sprite, in degrees.</param>
	/// <returns>Sprite object corresponding to 'name', or nullptr if unsuccessful.</returns>
	Sprite* addSprite(std::string texName, std::string spriteName, SDL_Rect* src, SDL_FRect* dst, SpriteType type, double angle = 0.0);
	
	/// <summary>
	/// Adds an existing sprite to memory.
	/// </summary>
	/// <param name="name">: Sprite name.</param>
	/// <param name="type">: Sprite type - _BACKGROUND, _FOREGROUND, or _POPUP.</param>
	/// <param name="s">: Sprite object.</param>
	/// <returns>Sprite object corresponding to 'name', or nullptr if unsuccessful.</returns>
	Sprite* addSprite(std::string name, SpriteType type, Sprite* s);

	/// <summary>
	/// Deletes a texture.
	/// </summary>
	/// <param name="name">: Texture name.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool deleteTexture(std::string name);

	/// <summary>
	/// Deletes a sprite.
	/// </summary>
	/// <param name="name">: Sprite name.</param>
	/// <param name="type">: Sprite type - _BACKGROUND, _FOREGROUND, or _POPUP.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool deleteSprite(std::string name, SpriteType type);

	/// <summary>
	/// Assigns a texture to a sprite.
	/// </summary>
	/// <param name="spriteName">: Sprite name.</param>
	/// <param name="textureName">: Texture name.</param>
	/// <returns>true if successful, false otherwise.</returns>
	bool setSpriteTexture(std::string spriteName, std::string textureName);

	/// <summary>
	/// Renders all visible sprites on the screen.
	/// </summary>
	void renderScreen();

	/// <summary>
	/// Resets internal data by deleting all texture and sprite objects.
	/// </summary>
	void reset();

	/// <summary>
	/// Checks if there are any existing sprites.
	/// </summary>
	/// <returns>true if there are any, false otherwise.</returns>
	bool hasSprites();

	/// <summary>
	/// Checks if there is a popup visible on screen.
	/// </summary>
	/// <returns>true if there is, false otherwise.</returns>
	bool doesPopupExist();
	
	/// <summary>
	/// Returns the sprite map for cursor-hitbox detection.
	/// </summary>
	/// <returns>Pointer to SpriteMap*[3].</returns>
	SpriteMap** getSpriteMap() { return _spritemap; }

private:
	/// <summary>
	/// Creates and returns a SDL_Surface object of a Unicode text.
	/// </summary>
	/// <param name="text">: Wide string text.</param>
	/// <param name="color">: Text color.</param>
	/// <param name="wrapLength">: Maximum length of pixels of a single row of text.</param>
	/// <returns>SDL_Surface object if successful, nullptr otherwise.</returns>
	SDL_Surface* getTextSurface(std::wstring text, std::string color, int wrapLength);

	/// <summary>
	/// Creates and returns a SDL_Surface object of a Unicode text.
	/// </summary>
	/// <param name="text">: Wide string text.</param>
	/// <param name="color">: Text color.</param>
	/// <param name="wrapLength">: Maximum length of pixels of a single row of text.</param>
	/// <returns>SDL_Surface object if successful, nullptr otherwise.</returns>
	SDL_Surface* getTextSurface(std::wstring text, SDL_Color& color, int wrapLength);

	void emptySprites();
	void emptyTextures();

	/// <summary>
	/// Masks the screen with a transluscent black color.
	/// </summary>
	void darkenScreen();

	/// <summary>
	/// Game window object.
	/// </summary>
	SDL_Window* _window;

	/// <summary>
	/// Graphics renderer object.
	/// </summary>
	SDL_Renderer* _renderer;

	/// <summary>
	/// NanumSquare font, ExtraBold.
	/// </summary>
	TTF_Font* _font;

	/// <summary>
	/// List of text colors.<para/>
	/// Existing colors:<para/>
	/// "white"
	/// </summary>
	std::map<std::string, SDL_Color> _colors;

	/// <summary>
	/// List of textures.
	/// </summary>
	std::map<std::string, SDL_Texture*> _textures;

	/// <summary>
	/// List of sprites.
	/// </summary>
	SpriteMap backgroundSprites;
	SpriteMap foregroundSprites;
	SpriteMap popupSprites;

	/// <summary>
	/// Array of three sprite lists.
	/// </summary>
	SpriteMap* _spritemap[3];

	Core* core;
};