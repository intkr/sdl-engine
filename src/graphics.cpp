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

SDL_Texture* Graphics::getTexture(std::string name) {
	try {
		return textures.at(name);
	}
	catch (out_of_range& e) {
		throw InvalidItemException(name, "texture");
	}
}

SDL_Color& Graphics::getColor(std::string name) {
	try {
		return colors.at(name);
	}
	catch (out_of_range& e) {
		throw InvalidItemException(name, "color");
	}
}

SDL_Texture* Graphics::getTextTexture(std::wstring text, std::string color, int wrapLength) {
	SDL_Surface* textSurface = getTextSurface(text, getColor(color), wrapLength);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return textTexture;
}

SDL_Surface* Graphics::getTextSurface(std::wstring text, SDL_Color& color, int wrapLength) {
	// utext needs to be destroyed
	size_t usize = text.size() + 1;
	Uint16* utext = new Uint16[usize];
	for (; usize; usize--) {
		utext[usize - 1] = text[usize - 1];
	}

	SDL_Surface* surface = TTF_RenderUNICODE_Blended_Wrapped(getFont(), utext, color, wrapLength);
	
	delete utext;
	return surface;
}

Texture* Graphics::createTexture(std::string path, std::string name) {
	SDL_Texture* SDLtexture = createSDLtexture(path);
	if (SDLtexture == nullptr)
		throw InvalidItemException(path, "texture path");
	Texture* texture = Texture::createTexture(SDLtexture, name);

	return texture;
}

SDL_Texture* Graphics::createSDLtexture(std::string path) {
	SDL_Surface* surface = loadImageAsSurface(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Surface* Graphics::loadImageAsSurface(std::string path) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) throw InvalidItemException(path, "texture path");
	return surface;
}

Texture* Graphics::addTexture(Texture* texture) {
	try {
		std::string name = texture.getName();
		if (doesTextureExist(name)) {
			throw DuplicateItemException(name);
		}
		textures.emplace(name, texture);
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
}

bool Graphics::doesTextureExist(std::string name) {
	if (textures.find(name) != textures.end())
		return true;
	else return false;
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

/*
TODO: (functions to use on popup state or something idk)

void Graphics::addBlackOverlay(int opacity) {
	std::string overlayName = "popupOverlay";
	if (doesSpriteExist(overlayName)) {
		return;
	}
	
	SDL_Texture* tex = createBlackPixel(opacity);
	SpriteGeometry geo;
	
	Sprite* s = new Sprite(t, geo);
	sprites[popupLayer].insert(s);
}

SDL_Texture* Graphics::createBlackPixel(int opacity) {
	SDL_Texture* t = SDL_CreateTexture(renderer, 0, SDL_TEXTUREACCESS_TARGET, 1, 1);
	SDL_SetRenderTarget(renderer, t);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, opacity * 255 / 100);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	SDL_RenderDrawPoint(renderer, 0, 0);
	SDL_SetRenderTarget(renderer, nullptr);
	return t;
}
*/