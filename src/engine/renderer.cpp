#include "renderer.h"

void Renderer::clearScreen() {
	SDL_RenderClear(renderer);
}

void Renderer::displayScreen() {
	SDL_RenderPresent(renderer);
}

void Renderer::renderTexture(SDL_Texture* texture, const SDL_Rect* source, const SDL_FRect* target, const double angle, const SDL_FPoint* center) {
	SDL_RenderCopyExF(renderer, texture, 
					  source, target, angle,
					  center, SDL_FLIP_NONE);
}
