#include "input.h"

Input* Input::getInput() {
	if (_input == nullptr) {
		_input = new Input();
	}
	return _input;
}

void Input::deleteInput() {
	delete _input;
}

Input::Input() {
	quitTriggered = false;
	lastInputDevice = _NONE;
	
	// Keybind setup for my keyboard
	setKeybinds(_KEY_A1, SDL_SCANCODE_KP_7);
	setKeybinds(_KEY_A2, SDL_SCANCODE_KP_8);
	setKeybinds(_KEY_A3, SDL_SCANCODE_KP_9);
	
	setKeybinds(_KEY_B1, SDL_SCANCODE_KP_4);
	setKeybinds(_KEY_B2, SDL_SCANCODE_KP_5);
	setKeybinds(_KEY_B3, SDL_SCANCODE_KP_6);
	
	setKeybinds(_KEY_C1, SDL_SCANCODE_KP_1);
	setKeybinds(_KEY_C2, SDL_SCANCODE_KP_2);
	setKeybinds(_KEY_C3, SDL_SCANCODE_KP_3);
	
	setKeybinds(_KEY_D1, SDL_SCANCODE_KP_0);
	setKeybinds(_KEY_D2, SDL_SCANCODE_KP_PERIOD);
	setKeybinds(_KEY_D3, SDL_SCANCODE_KP_ENTER);

	setKeybinds(_KEY_SHIFT, SDL_SCANCODE_LSHIFT);
	setKeybinds(_KEY_RETURN, SDL_SCANCODE_RETURN);
	setKeybinds(_KEY_ESCAPE, SDL_SCANCODE_ESCAPE);
}

Input::~Input() {}

void Input::setKeybinds(Key key, SDL_Scancode scancode) {
	deleteBindedKeyIfDuplicate(key, scancode);
	keybinds.emplace(scancode, key);
}

void Input::deleteBindedKeyIfDuplicate(Key key, SDL_Scancode scancode) {
	auto iter = keybinds.find(scancode);
	if (iter == keybinds.end()) return;
	
	if (iter.second != key) {
		keybinds.erase(iter);
	}
}

void Input::processInput() {
	flushInput();
	pollInput();
	handleInput();
}

void Input::flushInput() {
	flushKeys();
	flushMouse();
}

void Input::flushKeys() {
	for (auto iter : keyStatus) {
		flushKeyStatus(iter->second);
	}
}

void Input::flushKeyStatus(InputType& status) {
	transformInputStatus(status, _INPUT_PRESS_DOWN, _INPUT_PRESSED);
	transformInputStatus(status, _INPUT_PRESS_UP, _INPUT_NONE);
}

void Input::flushMouse() {
	transformInputStatus(mouseStatus, _INPUT_PRESS_DOWN, _INPUT_PRESSED);
	transformInputStatus(mouseStatus, _INPUT_PRESS_UP, _INPUT_NONE);
}

void Input::transformInputStatus(InputType& status, InputType from, InputType to) {
	if (status == from)
		status = to;
}

void Input::pollInput() {
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		setInputDevicePriority(e.type);
		switch (e.type) {
		// Window X button
		case SDL_QUIT:
			quitTriggered = true;
			break;

		// Key press / release
		case SDL_KEYDOWN:
			keyDown(e.key.keysym.scancode);
			break;
		case SDL_KEYUP:
			keyUp(e.key.keysym.scancode);
			break;

		// Mouse click / release
		case SDL_MOUSEBUTTONDOWN:
			mouseDown(e.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			mouseUp(e.button.button);
			break;
		// Mouse movement
		case SDL_MOUSEMOTION:
			updateCursorPos(e);
			break;
			
		// idk
		default:
			break;
		}
	}
}

// TODO: this function exists because idk how the polling system works,
// check if all polled events follow some sort of fixed ordering -
// which would make this function pointless if so.
void Input::setInputDevicePriority(Uint32 type) {
	switch (type) {
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		if (lastInputDevice != _MOUSE)
			lastInputDevice = _KEY;
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEMOTION:
		lastInputDevice = _MOUSE;
	}
}

void Input::keyDown(SDL_Scancode inputKey) {
	Key key = getBindedKey(inputKey);
	InputType& status = keyStatus[key];
	
	setInputStatus(status, _INPUT_PRESS_DOWN);
}

void Input::keyUp(SDL_Scancode inputKey) {
	Key key = getBindedKey(inputKey);
	InputType& status = keyStatus[key];
	
	setInputStatus(status, _INPUT_PRESS_UP);
}

Key Input::getBindedKey(SDL_Scancode scancode) {
	auto iter = keybinds.find(scancode);

	if (iter.second != keybinds.end())
		return iter.second;
	else return _KEY_ETC;
}

void Input::mouseDown(Uint8 SDLbutton) {
	MouseButton button = getButton(SDLbutton);
	InputType& status = mouseStatus[button];
	
	setInputStatus(status, _INPUT_PRESS_DOWN);
}

void Input::mouseUp(Uint8 SDLbutton) {
	MouseButton button = getButton(SDLbutton);
	InputType& status = mouseStatus[button];
	
	setInputStatus(status, _INPUT_PRESS_UP);
}

MouseButton Input::getButton(Uint8 button) {
	switch (button) {
	case SDL_BUTTON_LEFT:
		return _BUTTON_LEFT;
	case SDL_BUTTON_MIDDLE:
		return _BUTTON_MIDDLE;
	case SDL_BUTTON_RIGHT:
		return _BUTTON_RIGHT;
	default:
		return _BUTTON_ETC;
	}
}
void Input::updateCursorPos(SDL_Event& e) {
	cursorPos.x = (float)e.motion.x;
	cursorPos.y = (float)e.motion.y;
}

void Input::handleInput() {
	handleKeys();
	if (lastInputDevice == _MOUSE)
		handleMouse();
}

void Input::handleKeys() {
	KeyInput input;
	StateController* sc = StateController::getStateController();
	for (auto iter : keyStatus) {
		if (iter.first == _KEY_ETC || iter.second == _INPUT_NONE)
			continue;
		
		input = KeyInput(iter.second, iter.first);
		sc->handleKey(input);
	}
}

void Input::handleMouse() {
	MouseInput input;
	StateController* sc = StateController::getStateController();
	for (auto iter : mouseStatus) {
		input = MouseInput(iter.second, iter.first, cursorPos);
		sc->handleMouse(input);
	}
}