#include "graphics.h"

Graphics* Graphics::getGraphics() {
	if (_graphics == nullptr) {
		_graphics = new Graphics();
	}
	return _graphics;
}

Graphics::Graphics() {
	initSDL();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Graphics::initSDL() {
	int w = 1280, h = 720;
	SDL_Renderer* SDLrenderer;
	SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE, &window, &SDLrenderer);
	SDL_RenderSetLogicalSize(renderer, 1920, 1080);
	SDL_SetWindowTitle(window, "Puzzle Time");
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	renderer = new Renderer(SDLrenderer);
}

void Graphics::initFonts() {
	addNewFont("test", "assets/fonts/ns_eb.ttf", 70);
	addNewColor("white", 255, 255, 255, 255);
}

void Graphics::addNewFont(std::string name, std::string path, int ptSize) {
	TTF_Font* font = TTF_OpenFont(path, ptSize);
	fonts.emplace(name, font);
}

void Graphics::addNewColor(std::string name, int r, int g, int b, int a) {
	SDL_Color color{r, g, b, a};
	colors.emplace(name, color);
}

Renderer* Graphics::getRenderer() {
	if (renderer == nullptr) {
		throw InvalidItemException("null", "renderer");
	}
	return renderer;
}

SDL_Texture* Graphics::addTextureFromString(std::string name, std::wstring text, std::string color, int wrapLength) {
	if (doesTextureExist(name)) {
			throw DuplicateItemException(name);
	}

	SDL_Surface* textSurface = createSurfaceFromText(text, getColor(color), wrapLength);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	
	textures.emplace(name, texture);
	return textTexture;
}

SDL_Surface* Graphics::createSurfaceFromText(std::wstring text, SDL_Color& color, int wrapLength) {
	// Converts wstring to Uint16 to match param requirements.
	size_t usize = text.size() + 1;
	Uint16* utext = new Uint16[usize];
	for (; usize; usize--) {
		utext[usize - 1] = text[usize - 1];
	}

	SDL_Surface* surface = TTF_RenderUNICODE_Blended_Wrapped(getFont(), utext, color, wrapLength);
	
	delete utext;
	return surface;
}

Texture* Graphics::addTextureFromImage(std::string name, std::string path, std::string name) {
	if (doesTextureExist(name)) {
			throw DuplicateItemException(name);
	}
	
	SDL_Texture* SDLtexture = createTextureFromImage(path);
	if (SDLtexture == nullptr) {
		throw InvalidItemException(path, "texture path");
	}

	Texture* texture = Texture::createTexture(SDLtexture, name);
	textures.emplace(name, texture);
	return texture;
}

SDL_Texture* Graphics::createTextureFromImage(std::string path) {
	SDL_Surface* surface = createSurfaceFromImage(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Surface* Graphics::createSurfaceFromImage(std::string path) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) {
		throw InvalidItemException(path, "texture path");
	}
	return surface;
}

SDL_Texture* Graphics::getTexture(std::string name) {
	try {
		return textures.at(name);
	}
	catch (out_of_range& e) {
		throw InvalidItemException(name, "texture");
	}
}

bool Graphics::doesTextureExist(std::string name) {
	if (textures.find(name) != textures.end())
		return true;
	else return false;
}

SDL_Color& Graphics::getColor(std::string name) {
	try {
		return colors.at(name);
	}
	catch (out_of_range& e) {
		throw InvalidItemException(name, "color");
	}
}

void Graphics::deleteAllAssets() {
	deleteAllTextures();
}

void Graphics::deleteAllTextures() {
	Texture* tex;
	for (auto iter = textures.begin(); iter != textures.end();) {
		tex = iter.second;
		SDL_DestroyTexture(tex);
		iter = textures.erase(iter);
	}
}

void Graphics::deleteTexture(std::string name) {
	try {
		Texture* tex = getTexture(name);
		delete tex;
	}
	catch (InvalidItemException& e) {
		std::cout << e.what();
	}
}