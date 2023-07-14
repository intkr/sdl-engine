#include "graphics.h"

#include "core.h"

Graphics::Graphics(Core* _core) : core(_core) {
	_sprites[0] = &backgroundSprites;
	_sprites[1] = &foregroundSprites;
	_sprites[2] = &popupSprites;
	// 10 layers for each sprite list
	for (int i = 0; i < 3; i++) {
		_sprites[i]->resize(maxLayers);
	}

	// TODO: Fetch screen size data from player
	int w = 1280, h = 720;

	SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE, &_window, &_renderer);
	SDL_RenderSetLogicalSize(_renderer, 1920, 1080);
	SDL_SetWindowTitle(_window, "Puzzle Time");
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);


	_font = TTF_OpenFont("assets/fonts/ns_eb.ttf", 70);
	_colors["white"] = SDL_Color{ 255, 255, 255, 255 };
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

SDL_Texture* Graphics::getTexture(std::string name) {
	if (_textures.count(name) > 0) {
		return _textures[name];
	}
	else return nullptr;
}

SDL_Surface* Graphics::getTextSurface(std::wstring text, std::string color, int wrapLength) {
	return getTextSurface(text, getColor(color), wrapLength);
}

SDL_Surface* Graphics::getTextSurface(std::wstring text, SDL_Color& color, int wrapLength) {
	size_t usize = text.size() + 1;
	Uint16* utext = new Uint16[usize];
	for (; usize; usize--) {
		utext[usize - 1] = text[usize - 1];
	}

	return TTF_RenderUNICODE_Blended_Wrapped(getFont(), utext, color, wrapLength);
}

SDL_Texture* Graphics::getTextTexture(std::wstring text, std::string color, int wrapLength) {
	return getTextTexture(text, getColor(color), wrapLength);
}

SDL_Texture* Graphics::getTextTexture(std::wstring text, SDL_Color& color, int wrapLength) {
	SDL_Surface* textSurface = getTextSurface(text, color, wrapLength);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_FreeSurface(textSurface);
	return textTexture;
}


bool Graphics::setSpriteTexture(std::string spriteName, std::string textureName) {
	Sprite* s = nullptr;
	for (int i = 3; i; i--) {
		for (int j = 0; j < maxLayers; j++) {
			if ((*_sprites[i - 1])[j].count(spriteName) > 0) s = (*_sprites[i - 1])[j][spriteName];
		}
	}
	if (s == nullptr) return false;

	SDL_Texture* t = nullptr;
	if (_textures.count(textureName) > 0) t = _textures[textureName];
	if (t == nullptr) return false;

	s->setTexture(t);
	return true;
}

SDL_Texture* Graphics::addTexture(std::string path, std::string name) {
	if (_textures.find(name) != _textures.end()) {
		std::cout << "adding texture \"" << name << "\" failed. (duplicate texture name)\n";
		return _textures[name];
	}

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) {
		std::cout << "adding texture \"" << name << "\" failed. (null image)\n";
		return nullptr;
	}
	
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_FreeSurface(surface);
	_textures[name] = texture;
	return texture;
}

SDL_Texture* Graphics::addTexture(SDL_Texture* texture, std::string name) {
	if (_textures.find(name) != _textures.end()) {
		std::cout << "adding texture \"" << name << "\" failed. (duplicate texture name)\n";
		return _textures[name];
	}

	if (texture == nullptr) {
		std::cout << "adding texture \"" << name << "\" failed. (null texture)\n";
		return nullptr;
	}

	_textures[name] = texture;
	return texture;
}

Sprite* Graphics::addSprite(std::string texName, std::string spriteName, SDL_Rect* src, SDL_FRect* dst, SpriteType type, int layer, double angle) {
	if (layer >= maxLayers) {
		std::cout << "adding sprite \"" << spriteName << "\" failed. (invalid layer)\n";
		return nullptr;
	}
	if ((*_sprites[type])[layer].count(spriteName) > 0) {
		std::cout << "adding sprite \"" << spriteName << "\" failed. (duplicate sprite name)\n";
		return(*_sprites[type])[layer][spriteName];
	}

	if (_textures.count(texName) == 0) {
		std::cout << "adding sprite \"" << spriteName << "\" failed. (null texture)\n";
		return nullptr;
	}

	Sprite* s = new Sprite(_textures[texName], src, dst, angle);
	(*_sprites[type])[layer][spriteName] = s;
	return s;
}

Sprite* Graphics::addSprite(std::string name, SpriteType type, Sprite* s, int layer) {
	if (layer >= maxLayers) {
		std::cout << "adding sprite \"" << name << "\" failed. (invalid layer)\n";
		return nullptr;
	}
	if ((*_sprites[type])[layer].count(name) > 0) {
		std::cout << "adding sprite \"" << name << "\" failed. (duplicate sprite name)\n";
		return (*_sprites[type])[layer][name];
	}

	(*_sprites[type])[layer][name] = s;
	return s;
}

Sprite* Graphics::getSprite(std::string name) {
	for (int i = 3; i; i--) {
		for (int j = 0; j < maxLayers; j++) {
			if ((*_sprites[i - 1])[j].count(name) > 0) {
				return (*_sprites[i - 1])[j][name];
			}
		}
	}
	return NULL;
}

bool Graphics::hasSprites() {
	for (int i = 0; i < 3; i++) {
		if (_sprites[i]->size() > 0)
			return false;
	}
	return true;
}

bool Graphics::doesPopupExist() {
	return popupSprites[0].size() > 0;
}

void Graphics::renderScreen() {
	SDL_RenderClear(_renderer);

	// render all sprites - background -> foreground -> popup
	for (int i = 0; i < 3; i++) {
		// If there's a pop-up window to render, cover the window with an translucent black sprite.
		if (i == 2 && doesPopupExist()) {
			darkenScreen();
		}
		for (int j = 0; j < maxLayers; j++) {
			for (auto iter = (*_sprites[i])[j].cbegin(); iter != (*_sprites[i])[j].cend();) {
				Sprite* s = iter->second;
				bool validSprite = s->update();
				if (validSprite) {
					if (s->isVisible()) SDL_RenderCopyExF(_renderer, s->getTexture(), s->getSrcRect(), s->getDstRect(),
						s->getAngle(), nullptr, SDL_FLIP_NONE);
				}
				iter++;
			}
		}
	}

	SDL_RenderPresent(_renderer);
}

void Graphics::darkenScreen() {
	int dim = 50; // Black layer opacity

	SDL_Texture* t = SDL_CreateTexture(_renderer, 0, SDL_TEXTUREACCESS_TARGET, 1, 1);
	SDL_SetRenderTarget(_renderer, t);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, dim * 255 / 100);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	SDL_RenderDrawPoint(_renderer, 0, 0);
	SDL_SetRenderTarget(_renderer, nullptr);
	SDL_RenderCopy(_renderer, t, nullptr, nullptr);
	SDL_DestroyTexture(t);
}
void Graphics::reset() {
	emptySprites();
	emptyTextures();
}

void Graphics::emptySprites() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < maxLayers; j++) {
			for (auto it = (*_sprites[i])[j].begin(); it != (*_sprites[i])[j].end();) {
				delete it->second;
				it = (*_sprites[i])[j].erase(it);
			}
			(*_sprites[i])[j].clear();
		}
	}
}

void Graphics::emptyTextures() {
	for (auto it = _textures.begin(); it != _textures.end();) {
		SDL_DestroyTexture(it->second);
		_textures.erase(it++);
	}
}

bool Graphics::deleteSprite(std::string name, SpriteType type) {
	int layer = -1;
	for (int i = 0; i < maxLayers; i++) {
		if ((*_sprites[type])[i].count(name) > 0) {
			layer = i;
			break;
		}
	}
	if (layer == -1) return false;

	auto it = (*_sprites[type])[layer].find(name);
	delete it->second;
	(*_sprites[type])[layer].erase(it);
	return true;
}

bool Graphics::deleteTexture(std::string name) {
	auto texture = _textures.find(name);
	if (texture != _textures.end()) {
		SDL_DestroyTexture(texture->second);
		_textures.erase(texture);
		return true;
	}
	else return false;
}

SDL_Color& Graphics::getColor(std::string name) {
	if (_colors.count(name) == 0) {
		return _colors["white"];
	}
	return _colors[name];
}