#include "input.h"

#include "core.h"

Input::Input(Core* _core) : core(_core) {
	leftClickStatus = _MOUSE_UP;
	curX = curY = 0;

	// Keypad layout for my current setup
	twelveKeys[0][0] = SDL_SCANCODE_KP_7;
	twelveKeys[0][1] = SDL_SCANCODE_KP_8;
	twelveKeys[0][2] = SDL_SCANCODE_KP_9;
	twelveKeys[1][0] = SDL_SCANCODE_KP_4;
	twelveKeys[1][1] = SDL_SCANCODE_KP_5;
	twelveKeys[1][2] = SDL_SCANCODE_KP_6;
	twelveKeys[2][0] = SDL_SCANCODE_KP_1;
	twelveKeys[2][1] = SDL_SCANCODE_KP_2;
	twelveKeys[2][2] = SDL_SCANCODE_KP_3;
	twelveKeys[3][0] = SDL_SCANCODE_KP_0;
	twelveKeys[3][1] = SDL_SCANCODE_KP_PERIOD;
	twelveKeys[3][2] = SDL_SCANCODE_KP_ENTER;
}

Input::~Input() {
	pressedKeys.clear();
	clickedSprites.clear();
}

void Input::update() {
	flushInput();
	pollInput();
	handleInput();
}

void Input::pollInput() {
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		// Window X button
		case SDL_QUIT:
			core->quit();
			break;

		// Key press / release
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			pollKey(e.key.keysym.scancode, e.type);
			break;

		// Mouse click / release
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			if (e.button.button == SDL_BUTTON_LEFT) {
				leftClickStatus = (e.type == SDL_MOUSEBUTTONUP) ? _MOUSE_UP : _MOUSE_ACTIVE;
			}
		// Mouse movement
		case SDL_MOUSEMOTION:
			curX = e.motion.x;
			curY = e.motion.y;
			break;
		default:
			break;
		}
	}

	// Note: pollMouse needs to be called every frame to check mouse hover
	pollMouse(curX, curY);
}

void Input::flushInput() {
	for (auto key = pressedKeys.begin(); key != pressedKeys.end();) {
		key++->second = false;
	}
	for (auto obj = clickedSprites.begin(); obj != clickedSprites.end();) {
		obj++->second = false;
	}

	hoveredSprites.clear();
	releasedSprites.clear();
	releasedKeys.clear();
}


void Input::pollKey(SDL_Scancode inputKey, Uint32 type) {
	switch (type) {
	case SDL_KEYDOWN:
		if (pressedKeys.find(inputKey) == pressedKeys.end()) {
			pressedKeys[inputKey] = true;
		}
		break;
	case SDL_KEYUP:
		pressedKeys.erase(inputKey);
		releasedKeys.push_back(inputKey);
		break;
	default:
		// Shouldn't happen
		std::cout << "Invalid input type while polling key events. (" << type << ")\n";
		break;
	}
}

void Input::pollMouse(int x, int y) {
	SDL_FPoint p = { (float)x, (float)y };
	SpriteList** map = core->getGraphics()->getSpriteMap();

	// Check mouse hover
	for (int i = 3; i; i--) {
		for (int j = 0; j < core->getGraphics()->maxLayers; j++) {
			for (auto iter = (*map[i - 1])[j].cbegin(); iter != (*map[i - 1])[j].cend();) {
				Sprite* s = iter->second;
				std::string t = iter->first;

				if (s->getDstRect() == nullptr || checkCollision(p, s)) {
					hoveredSprites.push_back(t);
				}
				iter++;
			}
		}
	}

	// Check other mouse events
	switch (leftClickStatus) {
	case _MOUSE_UP:
		for (auto o = clickedSprites.begin(); o != clickedSprites.end();) {
			std::string t = o->first;
			releasedSprites.push_back(o->first);
			o++;
		}
		clickedSprites.clear();
		break;

	case _MOUSE_ACTIVE:
		for (int i = 3; i; i--) {
			for (int j = 0; j < core->getGraphics()->maxLayers; j++) {
				for (auto iter = (*map[i - 1])[j].cbegin(); iter != (*map[i - 1])[j].cend();) {
					Sprite* s = iter->second;
					std::string t = iter->first;

					if (s->getStatus() != _END && (s->getDstRect() == nullptr || checkCollision(p, s))) {
						clickedSprites[t] = true;
					}
					iter++;
				}
			}
		}

		leftClickStatus = _MOUSE_PASSIVE;
		break;

	case _MOUSE_PASSIVE:
		for (int i = 3; i; i--) {
			for (int j = 0; j < core->getGraphics()->maxLayers; j++) {
				for (auto iter = (*map[i - 1])[j].cbegin(); iter != (*map[i - 1])[j].cend();) {
					Sprite* s = iter->second;
					std::string t = iter->first;

					if (s->getDstRect() == nullptr || checkCollision(p, s)) {
						clickedSprites[t] = false;
					}
					else if (clickedSprites.count(t) > 0) {
						clickedSprites.erase(t);
					}
					iter++;
				}
			}
		}
		break;
	}
}

int Input::checkKeybinds(SDL_Scancode key) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (key == twelveKeys[i][j]) {
				return i * 3 + j;
			}
		}
	}
	return -1;
}

void Input::handleInput() {
	SCore* sc = core->getSCore();

	for (auto& key : pressedKeys) {
		sc->handleKey(key.first, key.second);
	}

	for (auto& spr : hoveredSprites) {
		sc->handleHover(spr);
	}

	for (auto& spr : clickedSprites) {
		sc->handleClick(spr.first, spr.second);
	}

	for (auto& spr : releasedSprites) {
		sc->handleRelease(spr);
	}
}