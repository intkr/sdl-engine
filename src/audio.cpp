#include "audio.h"

#include "core.h"

Audio::Audio(Core* _core) : core(_core) {
	fr = FMOD::System_Create(&fs);
	fr = fs->init(512, FMOD_INIT_NORMAL, 0);

	FMOD::ChannelGroup* bgm;
	fs->createChannelGroup("bgm", &bgm);
	_chgroups[_BGM] = bgm;

	FMOD::ChannelGroup* sfx;
	fs->createChannelGroup("sfx", &sfx);
	_chgroups[_SFX] = sfx;
}

Audio::~Audio() {
	stopSound();
	// TODO: check how to delete FMOD::ChannelGroups
	fs->close();
	fs->release();
}

bool Audio::addSound(std::string path, std::string name, bool isLoop, bool isStream) {
	if (_sounds.count(name) > 0) {
		std::cout << "Failed to add sound \"" << name << "\". (Duplicate sound name)\n";
		return false;
	}

	FMOD::Sound* sound;
	fr = fs->createSound(path.c_str(), (isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF) | FMOD_2D | (isStream ? FMOD_CREATESTREAM : FMOD_CREATESAMPLE), nullptr, &sound);
	if (fr != FMOD_OK) {
		// TODO: add more descriptive error prompts
		std::cout << "Failed to add sound \"" << name << "\". (Unknown error)\n";
		std::cout << "\tFMOD Error : " << FMOD_ErrorString(fr) << "\n";
		return false;
	}

	_sounds[name] = sound;
	return true;
}

bool Audio::playSound(std::string name, AudioType type, int volume) {
	if (_sounds.count(name) == 0) {
		std::cout << "Failed to play sound \"" << name << "\". (Nonexistent name)\n";
		return false;
	}

	FMOD::Channel* channel;
	fr = fs->playSound(_sounds[name], _chgroups[type], false, &channel);

	if (volume > 100) volume = 100;
	else if (volume < 0) volume = 0;
	channel->setVolume(volume / 100.0f);
	_channels.insert(std::make_pair(name, channel));
	return true;
}

bool Audio::pauseSound(std::string name) {
	if (_channels.count(name) == 0) {
		std::cout << "Failed to pause sound \"" << name << "\". (Nonexistent name)\n";
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
		std::cout << "Failed to stop sound \"" << name << "\". (Nonexistent name)\n";
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
	return _channels.size() > 0;
}