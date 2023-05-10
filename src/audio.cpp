#include "audio.h"

Audio::Audio() {
	fr = FMOD::System_Create(&fs);

	fr = fs->init(512, FMOD_INIT_NORMAL, 0);
}

Audio::~Audio() {
	FMOD::Sound* sound;

	// Release all allocated audio data
	for (auto a = _sounds.cbegin(); a != _sounds.cend();) {
		a->second->getCurrentSound(&sound);
		if (sound != NULL) {
			sound->release();
		}
		a->second->stop();
		_sounds.erase(a++);
	}

	fs->close();
	fs->release();
}

bool Audio::addSound(std::string& path, const char* name, bool isLoop, bool isStream, int volume) {
	std::string n = name;
	return addSound(path, n, isLoop, isStream, volume);
}

bool Audio::addSound(std::string& path, std::string& name, bool isLoop, bool isStream, int volume) {

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
	fr = fs->createSound(path.c_str(), (isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF) | FMOD_2D | (isStream ? FMOD_CREATESTREAM : 0), NULL, &sound);
	if (fr != FMOD_OK) {
		return false;
	}

	// Create channel object and pause sound immediately
	FMOD::Channel* channel;
	fs->playSound(sound, NULL, 1, &channel);
	if (fr != FMOD_OK) {
		sound->release();
		std::cout << "Sound \"" << name << "\" failed to play.\n";
		return false;
	}
	channel->setVolume((float)volume / 100);
	_sounds.push_back(std::make_pair(name, channel));
	return true;
}

void Audio::stopSound(std::string& name) {
	FMOD::Sound* sound;
	
	// Release all sounds if 'name' is empty
	if (name == "") {
		for (auto a = _sounds.cbegin(); a != _sounds.cend();) {
			a->second->getCurrentSound(&sound);
			sound->release();
			a++;
		}
		return;
	}

	// if not empty, release sound from corresponding channel
	FMOD::Channel* ch = getChannel(name);
	if (ch == nullptr) {
		std::cout << "Sound name \"" << name << "\" doesn't exist, failed to delete.\n";
		return;
	}
	
	ch->getCurrentSound(&sound);
	sound->release();
}

FMOD::Channel* Audio::getChannel(std::string& name) {
	for (int i = 0; i < _sounds.size(); i++) {
		if (_sounds[i].first == name) return _sounds[i].second;
	}

	std::cout << "Sound name \"" << name << "\" doesn't exist, failed to get channel.\n";
	return NULL;
}

void Audio::update() {
	FMOD::Sound* sound;
	bool b;
	for (auto a = _sounds.begin(); a != _sounds.end();) {
		fr = a->second->isPlaying(&b);

		if (!b || fr == FMOD_ERR_INVALID_HANDLE) {
			a->second->getCurrentSound(&sound);
			sound->release();
			//a->second->stop(); // this should be unnecessary
			a = _sounds.erase(a);
		}
		else {
			a++;
		}
	}
}

bool Audio::hasSounds() {
	return _sounds.size() > 0;
}