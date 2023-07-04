#include "audio.h"

Audio::Audio(Core* _core) : core(_core) {
	fr = FMOD::System_Create(&fs);
	fr = fs->init(512, FMOD_INIT_NORMAL, 0);

	FMOD::ChannelGroup* cg;
	fs->createChannelGroup("bgm", &cg);
	_soundgroups[_AUDIO_BGM] = cg;

	fs->createChannelGroup("sfx", &cg);
	_soundgroups[_AUDIO_SFX] = cg;
}

Audio::~Audio() {

	// Release all allocated audio objects
	stopSound();

	FMOD::Channel* channel;
	FMOD::Sound* sound;
	FMOD::ChannelGroup* cg = _soundgroups[_AUDIO_SFX];
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

bool Audio::addSound(std::string path, std::string name, bool isLoop, bool isStream, AudioType type, int volume) {
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
	fr = fs->createSound(path.c_str(), (isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF) | FMOD_2D | (isStream ? FMOD_CREATESTREAM : FMOD_CREATESAMPLE), nullptr, &sound);
	if (fr != FMOD_OK) {
		return false;
	}

	_sounds[name] = sound;
	return true;
}

bool Audio::playSound(std::string name, AudioType type, int volume) {
	if (_sounds.count(name) == 0) {
		return false;
	}
	FMOD::Channel* channel;
	fr = fs->playSound(_sounds[name], _soundgroups[type], false, &channel);

	_channels.insert(std::make_pair(name, channel));
	return true;
}

bool Audio::pauseSound(std::string name) {
	if (_channels.count(name) == 0) {
		return false;
	}
	_channels.find(name)->second->setPaused(true);
	return true;
}

bool Audio::stopSound() {
	for (auto ch = _channels.begin(); ch != _channels.end();) {
		ch->second->stop();
		ch = _channels.erase(ch);
	}
	return true;
}

bool Audio::stopSound(std::string name, AudioType type) {
	FMOD::Channel* channel;

	if (_channels.count(name) == 0) {
		std::cout << "Sound name \"" << name << "\" doesn't exist, failed to delete.\n";
		return false;
	}

	channel = _channels.find(name)->second;
	channel->stop();
	return true;
}

void Audio::update() {
	FMOD::Channel* ch;
	bool b;

	for (auto it = _channels.begin(); it != _channels.end();) {
		ch = it->second;
		fr = ch->isPlaying(&b);
		if (!b || fr == FMOD_ERR_INVALID_HANDLE) {
			it = _channels.erase(it);
		}
		else it++;
	}
}

bool Audio::hasSounds() {
	return _soundgroups.size() > 0;
}