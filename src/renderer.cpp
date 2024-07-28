#include "renderer.h"

void Renderer::clearScreen() {
	SDL_RenderClear(renderer);
}

void Renderer::displayScreen() {
	SDL_RenderPresent(renderer);
}

void Renderer::renderTexture(SDL_Texture* texture, SDL_Rect* source, SDL_FRect target, double angle) {
	SDL_RenderCopyExF(renderer, texture, 
					  source, target, angle,
					  nullptr, SDL_FLIP_NONE);
}
