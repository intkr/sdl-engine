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
	
	// Temporary keybind code until player settings are implemented,
	// set keybinds like the commented code below
	//setKeybinds(_KEY_A1, SDL_SCANCODE_KP_7);
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

void Input::flushKeyStatus(InputState& status) {
	changeInputStatus(status, _INPUT_PRESS_DOWN, _INPUT_PRESSED);
	changeInputStatus(status, _INPUT_PRESS_UP, _INPUT_NONE);
}

void Input::flushMouse() {
	changeInputStatus(mouseStatus, _INPUT_PRESS_DOWN, _INPUT_PRESSED);
	changeInputStatus(mouseStatus, _INPUT_PRESS_UP, _INPUT_NONE);
}

void Input::changeInputStatus(InputState& status, InputState from, InputState to) {
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


void Input::setInputDevicePriority(Uint32 type) {
	switch (type) {
	// Key input
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		if (lastInputDevice != _MOUSE)
			lastInputDevice = _KEY;
		break;

	// Mouse input
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEMOTION:
		lastInputDevice = _MOUSE;
		break;
	
	default:
		// explore other options later
		break;
	}
}

void Input::keyDown(SDL_Scancode inputKey) {
	Key key = getBindedKey(inputKey);
	InputState& status = keyStatus[key];
	
	setInputStatus(status, _INPUT_PRESS_DOWN);
}

void Input::keyUp(SDL_Scancode inputKey) {
	Key key = getBindedKey(inputKey);
	InputState& status = keyStatus[key];
	
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
	InputState& status = mouseStatus[button];
	
	setInputStatus(status, _INPUT_PRESS_DOWN);
}

void Input::mouseUp(Uint8 SDLbutton) {
	MouseButton button = getButton(SDLbutton);
	InputState& status = mouseStatus[button];
	
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
		
		input = KeyInput(iter.first, iter.second);
		sc->handleKey(input);
	}
}

void Input::handleMouse() {
	MouseInput input;
	StateController* sc = StateController::getStateController();
	for (auto iter : mouseStatus) {
		input = MouseInput(iter.first, iter.second, cursorPos);
		sc->handleMouse(input);
	}
}