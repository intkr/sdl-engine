#include "system.h"

System::System() {
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

System::~System() {
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

void System::loop() {
	while (gaming) {
		updateTime();
		updateGame();
		render();
		limitFPS();
	}
}

void System::updateGame() {
	i->processInput();
	a->update();
	s->update();
	checkForQuitTrigger();
}

void System::checkForQuitTrigger() {
	if(i->isQuitTriggered())
		gaming = false;
}

void System::render() {
	Renderer* r = g->getRenderer();
	r->clearScreen();
	s->render(r);
	r->presentScreen();
}

void System::updateTime() {
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