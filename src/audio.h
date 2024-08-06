#pragma once
#include <map>
#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_output.h"
#include "fmod_errors.h"

#include "clock.h"
#include "channel.h"
#include "exceptions.h"

typedef FMOD::Sound Sound;

class Audio {
public:
	static Audio* getAudio();
	static void deleteAudio();
	
	// TODO: check if bgms can be replayed / have multiple channels
	
	// Adds a sound by loading the audio file and assigning it to a given name.
	// Each sound should be assigned a unique name to prevent confusion.
	Sound* addBGM(std::string path, std::string name);
	Sound* addSFX(std::string path, std::string name);
	
	// Creates a channel with a designated sound loaded in, in a paused state.
	// You can unpause the channel via Channel::play().
	Channel* createChannel(std::string soundName);

	void deleteSound(std::string name);
	
	bool stopAllSounds();
	void update();
	
private:
	static Audio* a;
	Audio();
	~Audio();
	
	bool isSoundAlreadyLoaded(std::string name) { return (sounds.find(name) != sounds.end()); }

	Sound* getSound(std::string name);
	FMOD::Channel* createFMODchannel(Sound* sound);
	bool isSoundBGM(Sound* sound);
	void Audio::addChannel(Channel* ch, std::string name);

	bool isChannelDeprecated(Channel* ch);
	
	FMOD::System* fs;
	FMOD_RESULT fr;
	
	FMOD::ChannelGroup* sfx;
	FMOD::ChannelGroup* bgm;
	std::multimap<std::string, Channel*> channels;
	std::map<std::string, Sound*> sounds;
};