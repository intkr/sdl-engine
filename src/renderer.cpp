#include "renderer.h"

void Renderer::render() {
	clearScreen();
	
	displayScreen();
}

void Renderer::clearScreen() {
	SDL_RenderClear(renderer);
}

void Renderer::displayScreen() {
	SDL_RenderPresent(renderer);
}

void Renderer::renderTexture(Texture* texture, Geometry& geo) {
	SDL_RenderCopyExF(renderer, texture->texture, 
		geometry.srcRect, 
		geometry.hitbox, 
		geometry.angle,
		nullptr, SDL_FLIP_NONE);
}
