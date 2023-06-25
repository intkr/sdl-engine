#include "input.h"

Input::Input(Graphics* g) {
	_g = g;
	mouseStatus = 0;
	curX = curY = 0;
	quitTriggered = false;

	// default keybinds
	lefthandKeys[0][0] = SDL_SCANCODE_T;
	lefthandKeys[0][1] = SDL_SCANCODE_Y;
	lefthandKeys[0][2] = SDL_SCANCODE_U;
	lefthandKeys[1][0] = SDL_SCANCODE_T;
	lefthandKeys[1][1] = SDL_SCANCODE_Y;
	lefthandKeys[1][2] = SDL_SCANCODE_U;
	lefthandKeys[2][0] = SDL_SCANCODE_T;
	lefthandKeys[2][1] = SDL_SCANCODE_Y;
	lefthandKeys[2][2] = SDL_SCANCODE_U;
	lefthandKeys[3][0] = SDL_SCANCODE_T;
	lefthandKeys[3][1] = SDL_SCANCODE_Y;
	lefthandKeys[3][2] = SDL_SCANCODE_U;

	righthandKeys[0][0] = SDL_SCANCODE_KP_7;
	righthandKeys[0][1] = SDL_SCANCODE_KP_8;
	righthandKeys[0][2] = SDL_SCANCODE_KP_9;
	righthandKeys[1][0] = SDL_SCANCODE_KP_4;
	righthandKeys[1][1] = SDL_SCANCODE_KP_5;
	righthandKeys[1][2] = SDL_SCANCODE_KP_6;
	righthandKeys[2][0] = SDL_SCANCODE_KP_1;
	righthandKeys[2][1] = SDL_SCANCODE_KP_2;
	righthandKeys[2][2] = SDL_SCANCODE_KP_3;
	righthandKeys[3][0] = SDL_SCANCODE_KP_0;
	righthandKeys[3][1] = SDL_SCANCODE_KP_PERIOD;
	righthandKeys[3][2] = SDL_SCANCODE_KP_ENTER;
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

std::vector<std::string>* Input::getHoveredObject() {
	return &hoveredObject;
}

void Input::process(SDL_Event& e) {
	flushInput();

	// Handle key presses and mouse events
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			//gaming = false;
			quitTriggered = true;
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			pollInput(e.key.keysym.scancode, e.type);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseStatus = _MOUSE_ACTIVE;
				curX = e.button.x;
				curY = e.button.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) {
				mouseStatus = _MOUSE_UP;
				curX = e.button.x;
				curY = e.button.y;
			}
			break;
		case SDL_MOUSEMOTION:
			// SDL_MOUSEBUTTONDOWN event can get overridden if code below isn't commented
			// 
			//if (mouseStatus == _MOUSE_ACTIVE) mouseStatus = _MOUSE_PASSIVE;
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
		key++->second = false;
	}
	for (auto obj = clickedObject.begin(); obj != clickedObject.end();) {
		obj++->second = false;
	}

	hoveredObject.clear();
	releasedObject.clear();
}


void Input::pollInput(SDL_Scancode inputKey, Uint32 type) {
	switch (type) {
	case SDL_KEYDOWN:
		if (pressedKeys.find(inputKey) == pressedKeys.end()) {
			pressedKeys[inputKey] = true;
		}
		break;
	case SDL_KEYUP:
		pressedKeys.erase(inputKey);
		break;
	}
}

void Input::pollInput(int x, int y) {
	SDL_FPoint p = { (float)x, (float)y };

	// Handle hover
	for (int i = 3; i; i--) {
		for (auto iter = (*_g->_sprites[i - 1]).cbegin(); iter != (*_g->_sprites[i - 1]).cend();) {
			Sprite* s = iter->second;
			std::string t = iter->first;

			if (s->getDstRect() == nullptr || checkCollision(p, s)) {
				hoveredObject.push_back(t);
			}
			iter++;
		}
	}

	// Handle other mouse events
	switch (mouseStatus) {
	case _MOUSE_UP:
		for (auto o = clickedObject.begin(); o != clickedObject.end();) {
			std::string t = o->first;
			releasedObject.push_back(o->first);
			o++;
		}
		clickedObject.clear();
		break;

	case _MOUSE_ACTIVE:
		for (int i = 3; i; i--) {
			for (auto iter = (*_g->_sprites[i - 1]).cbegin(); iter != (*_g->_sprites[i - 1]).cend();) {
				Sprite* s = iter->second;
				std::string t = iter->first;
				
				if (s->getStatus() != _END && (s->getDstRect() == nullptr || checkCollision(p, s))) {
					clickedObject[t] = true;
				}
				iter++;
			}
		}

		mouseStatus = _MOUSE_PASSIVE;
		break;

	case _MOUSE_PASSIVE:
		for (int i = 2; i >= 0; i--) {
			for (auto iter = (*_g->_sprites[i]).cbegin(); iter != (*_g->_sprites[i]).cend();) {
				Sprite* s = iter->second;
				std::string t = iter->first;

				if (s->getDstRect() == nullptr || checkCollision(p, s)) {
					clickedObject[t] = false;
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

int Input::checkKeybinds(SDL_Scancode key) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (key == lefthandKeys[i][j] || key == righthandKeys[i][j]) {
				return i * 3 + j;
			}
		}
	}
	return -1;
}