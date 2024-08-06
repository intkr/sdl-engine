#include "engine.h"

Engine::Engine() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	p = Player::getPlayer();
	graphics = Graphics::getGraphics();
	input = Input::getInput();
	audio = Audio::getAudio();
	stateController = StateController::getStateController();
	clock = Clock::getClock();
	
	gaming = true;
}

Engine::~Engine() {
	p->deletePlayer();
	stateController->deleteStateController();
	audio->deleteAudio();
	input->deleteInput();
	clock->deleteClock();
	graphics->deleteGraphics();
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::loop() {
	while (gaming) {
		updateTime();
		updateGame();
		render();
		limitFPS();
	}
}

void Engine::updateGame() {
	input->processInput();
	audio->update();
	stateController->update();
	checkForQuitTrigger();
}

void Engine::checkForQuitTrigger() {
	if(input->isQuitTriggered())
		gaming = false;
}

void Engine::render() {
	Renderer* renderer = graphics->getRenderer();
	renderer->clearScreen();
	stateController->render(renderer);
	renderer->presentScreen();
}

void Engine::updateTime() {
	clock->update();
}

void limitFPS() {
	ms delta = clock->getDeltaTime(SteadyClock::now());
	int deltaFrame_ms = (int)delta.count();
	
	const int msPerSecond = 1000;
	int msPerFrame = msPerSecond / fps;
	
	if (deltaFrame_ms < msPerFrame) {
		SDL_Delay(msPerFrame - deltaFrame_ms);
	}
}