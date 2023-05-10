#include "input.h"

Input::Input(Graphics* g) {
	_g = g;
	mouseStatus = 0;
	curX = curY = 0;
	
	// default keybinds
	leftKeybinds[0][0] = SDL_SCANCODE_2;
	leftKeybinds[0][1] = SDL_SCANCODE_3;
	leftKeybinds[0][2] = SDL_SCANCODE_4;
	leftKeybinds[1][0] = SDL_SCANCODE_W;
	leftKeybinds[1][1] = SDL_SCANCODE_E;
	leftKeybinds[1][2] = SDL_SCANCODE_R;
	leftKeybinds[2][0] = SDL_SCANCODE_S;
	leftKeybinds[2][1] = SDL_SCANCODE_D;
	leftKeybinds[2][2] = SDL_SCANCODE_F;
	leftKeybinds[3][0] = SDL_SCANCODE_X;
	leftKeybinds[3][1] = SDL_SCANCODE_C;
	leftKeybinds[3][2] = SDL_SCANCODE_V;

	rightKeybinds[0][0] = SDL_SCANCODE_7;
	rightKeybinds[0][1] = SDL_SCANCODE_8;
	rightKeybinds[0][2] = SDL_SCANCODE_9;
	rightKeybinds[1][0] = SDL_SCANCODE_U;
	rightKeybinds[1][1] = SDL_SCANCODE_I;
	rightKeybinds[1][2] = SDL_SCANCODE_O;
	rightKeybinds[2][0] = SDL_SCANCODE_J;
	rightKeybinds[2][1] = SDL_SCANCODE_K;
	rightKeybinds[2][2] = SDL_SCANCODE_L;
	rightKeybinds[3][0] = SDL_SCANCODE_M;
	rightKeybinds[3][1] = SDL_SCANCODE_COMMA;
	rightKeybinds[3][2] = SDL_SCANCODE_PERIOD;
}

Input::~Input() {
	pressedKeys.clear();
	clickedObject.clear();
}

std::map<SDL_Scancode, bool>* Input::getPressedKeys() {
	return &pressedKeys;
}

std::map<std::string, bool>* Input::getClickedObject() {
	return &clickedObject;
}

std::vector<std::string>* Input::getReleasedObject() {
	return &releasedObject;
}

void Input::process(SDL_Event& e) {
	flushInput();

	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			//gaming = false;
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			pollInput(e.key.keysym.scancode, e.type);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseStatus = 1;
				curX = e.button.x;
				curY = e.button.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseStatus = 0;
				curX = e.button.x;
				curY = e.button.y;
			}
			break;
		case SDL_MOUSEMOTION:
			if (mouseStatus > 0) mouseStatus = 2;
			curX = e.motion.x;
			curY = e.motion.y;
			break;
		default:
			break;
		}
	}
	pollInput(curX, curY);
}

void Input::flushInput() {
	for (auto key = pressedKeys.begin(); key != pressedKeys.end();) {
		key++->second = true;
	}
	releasedObject.clear();
}


void Input::pollInput(SDL_Scancode inputKey, Uint32 type) {
	switch (type) {
	case SDL_KEYDOWN:
		if (pressedKeys.find(inputKey) == pressedKeys.end()) {
			pressedKeys[inputKey] = false;
		}
		break;
	case SDL_KEYUP:
		pressedKeys.erase(inputKey);
		break;
	}
}

void Input::pollInput(int x, int y) {
	SDL_FPoint p = { (float)x, (float)y };
	switch (mouseStatus) {
	case 0:
		for (auto o = clickedObject.cbegin(); o != clickedObject.cend();) {
			std::string t = o->first;
			releasedObject.push_back(o->first);
			o++;
		}
		clickedObject.clear();
		break;
	case 1:
		mouseStatus = 2;
		for (int i = 2; i >= 0; i--) {
			for (auto iter = (*_g->_sprites[i]).cbegin(); iter != (*_g->_sprites[i]).cend();) {
				Sprite* s = iter->second;
				std::string t = iter->first;
				
				if (s->getDstRect() == NULL || checkCollision(p, s)) {
					clickedObject[t] = false;
				}
				iter++;
			}
		}
		break;
	case 2:
		for (int i = 2; i >= 0; i--) {
			for (auto iter = (*_g->_sprites[i]).cbegin(); iter != (*_g->_sprites[i]).cend();) {
				Sprite* s = iter->second;
				std::string t = iter->first;

				if (s->getDstRect() == NULL || checkCollision(p, s)) {
					clickedObject[t] = true;
				}
				else if (clickedObject.count(t) > 0) {
					clickedObject.erase(t);
				}
				iter++;
			}
		}
		break;
	default:
		// shouldn't happen
		break;
	}
}