#include "audio.h"

Audio::Audio() {
	fr = FMOD::System_Create(&fs);
	fr = fs->init(512, FMOD_INIT_NORMAL, 0);
	
	FMOD::ChannelGroup* cg;
	fs->createChannelGroup("bgm", &cg);
	_sounds[_AUDIO_BGM] = cg;

	fs->createChannelGroup("sfx", &cg);
	_sounds[_AUDIO_SFX] = cg;
}

Audio::~Audio() {

	// Release all allocated audio objects
	stopBGM();

	FMOD::Channel* channel;
	FMOD::Sound* sound;
	FMOD::ChannelGroup* cg = _sounds[_AUDIO_SFX];
	int n;
	cg->getNumChannels(&n);
	for (; n; n--) {
		cg->getChannel(n - 1, &channel);
		channel->getCurrentSound(&sound);
		sound->release();
	}

	fs->close();
	fs->release();
}

FMOD::Channel* Audio::addSound(std::string& path, const char* name, bool isLoop, bool isStream, AudioType type, int volume) {
	std::string n = name;
	return addSound(path, n, isLoop, isStream, type, volume);
}

FMOD::Channel* Audio::addSound(std::string& path, std::string& name, bool isLoop, bool isStream, AudioType type, int volume) {
	// Setting audio boundaries
	if (volume > 100) {
		std::cout << "Warning: Sound \"" << name << "\" was set to volume " << volume << ", setting to 100 instead.\n";
		volume = 100;
	}
	else if (volume < 0) {
		std::cout << "Warning: Sound \"" << name << "\" was set to volume " << volume << ", setting to 0 instead.\n";
		volume = 0;
	}

	// Create sound object
	FMOD::Sound* sound;
	fr = fs->createSound(path.c_str(), (isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF) | FMOD_2D | (isStream ? FMOD_CREATESTREAM : 0), nullptr, &sound);
	if (fr != FMOD_OK) {
		return nullptr;
	}

	// SFX should be played instantly, while BGM should be played by unpausing.
	// This is because there might be a delay when loading BGMs onto a stream.
	FMOD::Channel* channel;
	fr = fs->playSound(sound, _sounds[type], true, &channel);
	
	if (fr != FMOD_OK) {
		sound->release();
		std::cout << "Sound \"" << name << "\" failed to play.\n";
		return nullptr;
	}
	channel->setVolume((float)volume / 100);
	//channel->setChannelGroup(_sounds[type]->getGroup());
	return channel;
}

void Audio::stopBGM() {
	FMOD::Channel* channel;
	FMOD::Sound* sound;
	int n;

	// Release all sounds if 'name' is empty
	FMOD::ChannelGroup* cg = _sounds[_AUDIO_BGM];
	cg->getNumChannels(&n);
	for (; n; n--) {
		cg->getChannel(n - 1, &channel);
		channel->getCurrentSound(&sound);
		sound->release();
	}
	return;
}

void Audio::stopBGM(std::string& name, AudioType type) {
	FMOD::Channel* channel;
	FMOD::Sound* sound;

	// if not empty, release sound from corresponding channel
	//channel = getChannelByName(name, type);
	if (bgmChannels.count(name) == 0) {
		std::cout << "Sound name \"" << name << "\" doesn't exist, failed to delete.\n";
		return;
	}

	channel = bgmChannels[name];
	channel->getCurrentSound(&sound);
	sound->release();
}

FMOD::Channel* Audio::getBGMChannel(std::string& name) {
	FMOD::Channel* ch;
	//ch = _sounds[type]->getChannel(name);

	if (bgmChannels.count(name) == 0) {
		std::cout << "Sound name \"" << name << "\" doesn't exist, failed to get channel.\n";
	}
	ch = bgmChannels[name];
	return ch;
}

void Audio::update() {
	FMOD::Sound* sound;
	FMOD::ChannelGroup* cg;
	FMOD::Channel* ch;
	bool b;
	int i;

	for (auto it = _sounds.begin(); it != _sounds.end();) {
		cg = it->second;

		for (cg->getNumChannels(&i); i; i--) {
			cg->getChannel(i, &ch);
			fr = ch->isPlaying(&b);

			if (!b || fr == FMOD_ERR_INVALID_HANDLE) {
				ch->getCurrentSound(&sound);
				sound->release();
			}
		}

		it++;
	}
}

bool Audio::hasSounds() {
	return _sounds.size() > 0;
}