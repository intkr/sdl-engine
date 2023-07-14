#include "StateTitle.h"

#include "../core.h"
#include "score.h"


StateTitle::StateTitle(SCore* _score, Core* _core) : State(_score, _core) {
	init();
}

StateTitle::~StateTitle() {}

void StateTitle::init() {
	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	AnimationGroup* ag;
	AnimationEvent* ae;
	Sprite* s;
	SDL_FRect* r;
	int cycle, w, h;

	// Clockworks
	//if (tex = g->addTexture("assets/common/gear-L.png", "gear-1")) {
	//	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	//	r = new SDL_FRect{ 1920.0f * 0.12f, 1080.0f * 0.1f, (float)w * 1.5f, (float)h * 1.5f };
	//	s = g->addSprite("gear-1", _FOREGROUND, new Sprite(tex, nullptr, r));
	//
	//	if (s != nullptr) addGearAnimations(s, 18.0f);
	//}

	// Clockworks (blurred)
	addGear('L', 1, new SDL_FRect{ 1920.0f * 0.7f, 1080.0f * -0.1f, 3.0f, 3.0f }, 0.0, -18.0f, 10, 50, 160, 1);
	addGear('M', 2, new SDL_FRect{ 1920.0f * 0.46f, 1080.0f * 0.025f, 3.0f, 3.0f }, 0.0, 27.7f, 10, 50, 180, 1);
	addGear('S', 3, new SDL_FRect{ 1920.0f * 0.508f, 1080.0f * 0.485f, 2.333f, 2.333f }, -10.0, -60.0f, 10, 50, 200, 1);
	addGear('M', 4, new SDL_FRect{ 1920.0f * 0.548f, 1080.0f * 0.637f, 2.5f, 2.5f }, 10.0, 27.7f, 10, 50, 140, 1);
	addGear('S', 5, new SDL_FRect{ 1920.0f * 0.918f, 1080.0f * 0.67f, 2.75f, 2.75f }, 17.0, 60.0f, 10, 50, 235, 1);
	addGear('L', 6, new SDL_FRect{ 1920.0f * 0.157f, 1080.0f * 0.573f, 2.667f, 2.667f }, -6.0, -18.0f, 10, 50, 180, 1);
	addGear('M', 7, new SDL_FRect{ 1920.0f * 0.228f, 1080.0f * -0.188f, 3.0f, 3.0f }, 6.0, -27.7f, 10, 50, 200, 1);
	addGear('L', 8, new SDL_FRect{ 1920.0f * -0.171f, 1080.0f * -0.1f, 2.9f, 2.9f }, 13.0, 18.0f, 10, 50, 255, 1);

	addGear('L', 10, new SDL_FRect{ 1920.0f * 0.52f, 1080.0f * 0.14f, 5.0f, 5.0f }, 6.0, 1.0f, 1, 0, 80, 2);
	addGear('L', 11, new SDL_FRect{ 1920.0f * -0.161f, 1080.0f * -0.188f, 5.0f, 5.0f }, -3.0, -1.0f, 1, 0, 100, 2);

	// Black screen for fade in effect
	SDL_Renderer* _renderer = g->getRenderer();
	tex = SDL_CreateTexture(_renderer, 0, SDL_TEXTUREACCESS_TARGET, 1, 1);
	SDL_SetRenderTarget(_renderer, tex);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	SDL_RenderDrawPoint(_renderer, 0, 0);
	SDL_SetRenderTarget(_renderer, nullptr);
	if (tex = g->addTexture(tex, "black")) {
		s = g->addSprite("black", _FOREGROUND, new Sprite(tex, nullptr, nullptr), 0);

		if (s != nullptr) {
			// fade in
			ag = new AnimationGroup(false, false, true);
			if (s->addAnimationGroup("fadein", _IDLE, ag)) {
				ae = new AnimationEvent(40, Animations::opacity);
				ae->setFloat("a", 1.0f);
				ae->setFloat("b", 0.0f);
				s->addAnimationEvent("fadein", ae);
			}
		}
	}

	// background
	if (tex = g->addTexture("assets/bg.png", "test")) {
		s = g->addSprite("testbg", _BACKGROUND, new Sprite(tex, nullptr, nullptr), 9);

		if (s != nullptr) {
			// static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}

	// text
	tex = g->getTextTexture(L"Press any key", "white", 800);
	if (tex = g->addTexture(tex, "testText")) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		r = new SDL_FRect{ (1920 - w) * 0.5f, (1080 - h) * 0.9f, (float)w, (float)h };
		s = g->addSprite("txt", _FOREGROUND, new Sprite(tex, nullptr, r), 1);

		if (s != nullptr) {
			// static motion
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleStatic", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::staticMotion);
				s->addAnimationEvent("idleStatic", ae);
			}
		}
	}

	// Logo
	if (tex = g->addTexture("assets/common/logo.png", "logo"), 1) {
		SDL_QueryTexture(tex, 0, 0, &w, &h);
		r = new SDL_FRect{ (1920 - w) * 0.5f, (1080 - h) * 0.25f, (float)w, (float)h};
		s = g->addSprite("logo", _FOREGROUND, new Sprite(tex, nullptr, r), 1);

		if (s != nullptr) {
			// pop out from center of screen
			cycle = 30;
			ag = new AnimationGroup(false, true, true);
			if (s->addAnimationGroup("introPopOut", _INTRO, ag)) {
				ae = new AnimationEvent(cycle, Animations::resizeCenteredMotion);
				ae->setFloat("startSize", 0.0);
				ae->setFloat("endSize", 1.0);
				s->addAnimationEvent("introPopOut", ae);
			}
			else delete ag;

			// idle motion in y axis
			ag = new AnimationGroup(true, false, true);
			if (s->addAnimationGroup("idleSpin", _IDLE, ag)) {
				cycle = 120;
				ae = new AnimationEvent(cycle * 2, Animations::sincosMotion);
				ae->setFloat("a", 60.0f);
				ae->setFloat("b", 1.0f / cycle);
				ae->setChar("axis", 'y');
				ae->setChar("func", 's');
				s->addAnimationEvent("idleSpin", ae);
			}
			else delete ag;

			// low opacity (active when clicked)
			ag = new AnimationGroup(true, false, false);
			if (s->addAnimationGroup("idleOpacity", _IDLE, ag)) {
				ae = new AnimationEvent(1, Animations::opacity);
				ae->setFloat("a", 0.1f);
				s->addAnimationEvent("idleOpacity", ae);
			}
			else delete ag;
		}
		else {
			delete r;
		}
	}
	else {
		// if sprite already exists, disable 10% opacity
		s = g->addSprite("testfg", _FOREGROUND, nullptr);
		if (s != nullptr) {
			s->toggleAnimationGroup("idleOpacity", _IDLE, false);
		}
	}

	Audio* a = core->getAudio();
	if (a->addSound("assets/Vine Boom.ogg", "vine", false, false)) {
		
	}
	//if (a->addSound("assets/audio.mp3", "testbgm", true, true)) {
	//	a->playSound("testbgm", _BGM, 10);
	//}
	
}

void StateTitle::update() {
	return;
}

void StateTitle::exitState(StateType targetState) {
	switch (targetState) {
	case _GAME_PAIR:
		freeSpecifics();
		break;
	default:
		freeAll();
	}
	sCore->changeState(targetState);
}

void StateTitle::freeAll() {
	Graphics* g = core->getGraphics();
	g->deleteSprite("testfg", _FOREGROUND);
	g->deleteSprite("txt", _FOREGROUND);
}

void StateTitle::freeSpecifics() {
	Graphics* g = core->getGraphics();
	g->addSprite("testfg", _FOREGROUND, nullptr)->toggleAnimationGroup("idleOpacity", _IDLE, true);
	test = false;
}


void StateTitle::handleClick(std::string name, bool active) {
	Audio* a = core->getAudio();
	if (name == "testfg" && active) {
		// *vine boom*
		a->playSound("vine", _SFX, 100);
		exitState(_STATE_SELECT);
	}
	return;
}

void StateTitle::handleKey(SDL_Scancode key, bool active) {
	Audio* a = core->getAudio();
	if (key == SDL_SCANCODE_SPACE && active) {
		a->playSound("vine", _SFX, 100);
		exitState(_STATE_SELECT);
	}
	return;
}

void StateTitle::addGear(char size, int num, SDL_FRect* dst, double angle, float rotation, int rotatingFrames, int stopFrames, int brightness, int layer) {
	Graphics* g = core->getGraphics();
	SDL_Texture* tex;
	Sprite* s;
	int w, h;

	std::string path, name = "gear-blur-";
	name.append(std::to_string(num));
	switch (size) {
	case 's':
	case 'S':
		path = "assets/common/gear-S-blur.png";
		break;

	case 'm':
	case 'M':
		path = "assets/common/gear-M-blur.png";
		break;

	case 'l':
	case 'L':
		path = "assets/common/gear-L-blur.png";
		break;

	default:
		// invalid size
		return;
	}


	if (tex = g->addTexture(path, name)) {
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		dst->w *= w, dst->h *= h;
		s = g->addSprite(name, _BACKGROUND, new Sprite(tex, nullptr, dst, angle), layer);

		if (s != nullptr) addGearAnimations(s, rotatingFrames, stopFrames, rotation, brightness);
	}
}

void StateTitle::addGearAnimations(Sprite* s, int rotatingFrames, int stopFrames, float rotation, int brightness) {
	// rotation
	AnimationGroup* ag;
	AnimationEvent* ae;

	ag = new AnimationGroup(true, true, true);
	if (s->addAnimationGroup("gearSpin", _IDLE, ag)) {
		ae = new AnimationEvent(stopFrames, Animations::staticMotion);
		s->addAnimationEvent("gearSpin", ae);
		ae = new AnimationEvent(rotatingFrames, Animations::linearRotation);
		ae->setFloat("speed", rotation / rotatingFrames);
		s->addAnimationEvent("gearSpin", ae);
	}
	// colorize
	ag = new AnimationGroup(true, true, true);
	if (s->addAnimationGroup("gearDarken", _IDLE, ag)) {
		ae = new AnimationEvent(1, Animations::colorize);
		ae->setFloat("r", (float)brightness);
		ae->setFloat("g", (float)brightness);
		ae->setFloat("b", (float)brightness);
		s->addAnimationEvent("gearDarken", ae);
	}
}
