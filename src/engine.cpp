#include "engine.h"

Engine::Engine() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	p = Player::getPlayer();
	g = Graphics::getGraphics();
	i = Input::getInput();
	a = Audio::getAudio();
	s = StateController::getStateController();
	c = Clock::getClock();
	
	gaming = true;
}

Engine::~Engine() {
	p->deletePlayer();
	s->deleteStateController();
	a->deleteAudio();
	i->deleteInput();
	c->deleteClock();
	g->deleteGraphics();
	
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
	i->processInput();
	a->update();
	s->update();
	checkForQuitTrigger();
}

void Engine::checkForQuitTrigger() {
	if(i->isQuitTriggered())
		gaming = false;
}

void Engine::render() {
	Renderer* r = g->getRenderer();
	r->clearScreen();
	s->render(r);
	r->presentScreen();
}

void Engine::updateTime() {
	c->update();
}

void limitFPS() {
	ms deltaTime = c->getDeltaTime(SteadyClock::now());
	int frameElapsedMS = (int)deltaTime.count();
	
	const int msPerSecond = 1000;
	int msPerFrame = msPerSecond / fps;
	
	if (frameElapsedMS < msPerFrame) {
		SDL_Delay(msPerFrame - frameElapsedMS);
	}
}