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
		key++->second = true;
	}
	for (auto obj = clickedObject.begin(); obj != clickedObject.end();) {
		obj++->second = true;
	}

	hoveredObject.clear();
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
				
				if (s->getDstRect() == nullptr || checkCollision(p, s)) {
					clickedObject[t] = false;

					// click test
					if (t != "testfg" && t != "testbg") {
						std::cout << "clicked : \t" << t << "\n";
					}
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