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
	
	Sound* createBGM(std::string path);
	Sound* createSFX(std::string path);
	void addSound(Sound* s, std::string name);
	// The name of the channel is equal to the sound it plays.
	// Multiple channels may result in having the same name.
	Channel* createChannel(std::string soundName);
	void addChannel(Channel* ch, std::string name);

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
	
	FMOD::System* fs;
	FMOD_RESULT fr;
	
	FMOD::ChannelGroup* sfx;
	FMOD::ChannelGroup* bgm;
	std::multimap<std::string, Channel*> channels;
	std::map<std::string, Sound*> sounds;
};