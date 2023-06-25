#include "game.h"

void Game::winLevel() {
	currentCombo++;
	if (currentCombo > maximumCombo) maximumCombo = currentCombo;

	score += (int)(pow(currentCombo, scoreExponent) * baseScore);
}

void Game::loseLevel() {
	currentCombo = 0;
}