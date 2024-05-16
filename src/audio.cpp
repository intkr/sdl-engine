#include "audio.h"

#include "core.h"

Audio::Audio() {
	fr = FMOD::System_Create(&fs);
	fr = fs->init(512, FMOD_INIT_NORMAL, 0);
}

Audio::~Audio() {
	stopAllSounds();
	fs->close();
	fs->release();
}

Audio* Audio::getAudio() {
	if (a == nullptr) a = new Audio();
	return a;
}

void Audio::deleteAudio() {
	delete a;
}

Sound* Audio::createBGM(std::string path) {
	Sound* sound;
	fr = fs->createSound(path.c_str(), (FMOD_3D | FMOD_CREATESTREAM), nullptr, &sound);
	
	if (fr != FMOD_OK) {
		throw InvalidItemException(path, "sound path");
	}
	else return sound;
}

Sound* Audio::createSFX(std::string path) {
	Sound* sound;
	fr = fs->createSound(path.c_str(), (FMOD_3D | FMOD_CREATESAMPLE), nullptr, &sound);
	
	if (fr != FMOD_OK) {
		throw InvalidItemException(path, "sound path");
	}
	else return sound;
}

void Audio::addSound(Sound* s, std::string name) {
	if (isSoundAlreadyLoaded(name)) {
		throw DuplicateItemException(name, "sound");
	}
	sounds.emplace(name, s);
}

Channel* Audio::createChannel(std::string name) {
	try {
		Sound* sound = getSound(name);
		FMOD::Channel* fmod_ch = createFMODchannel(sound);
		Channel* channel = new Channel(fmod_ch);
		return channel;
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
}

Sound* Audio::getSound(std::string name) {
	try {
		Sound* sound = sounds.at(name);
		return sound;
	}
	catch (out_of_range& e) {
		throw InvalidItemException(name, "sound");
	}
}

FMOD::Channel* Audio::createFMODchannel(Sound* sound) {
	FMOD::ChannelGroup* group;
	if (isSoundBGM(sound)) group = bgm;
	else group = sfx;

	FMOD::Channel* fmod_ch;
	fr = fs->playSound(sound, group, true, &fmod_ch);
	return fmod_ch;
}

bool Audio::isSoundBGM(Sound* sound) {
	FMOD_MODE mode;
	sound->getMode(&mode);
	return (mode & FMOD_CREATESTREAM);
}

void Audio::addChannel(Channel* ch, std::string name) {
	channels.emplace(name, channel);
}

/* not sure if this is rly needed but uncomment if so
Channel* Audio::getChannel(std::string name) {
	auto range = channels.equal_range(name);
	return range->second->second;
}
*/

void Audio::update() {
	FMOD::Channel* channel;
	bool playing;

	// TODO: add effect related code when implemented
	for (auto it = channels.begin(); it != channels.end();) {
		channel = it->second;
		fr = channel->isPlaying(&playing);
		if (!playing || fr == FMOD_ERR_INVALID_HANDLE) {
			it = _channels.erase(it);
		}
		else it++;
	}
}

void Audio::deleteSound(std::string name) {
	try {
		Sound* sound = sounds.at(name);
		sound->release();
		sounds.erase(name);
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
}