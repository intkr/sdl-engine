#pragma once
#include <map>
#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_output.h"
#include "fmod_errors.h"

// random note : Channels are (presumably) released automatically when its Sound is released

enum AudioType { _AUDIO_BGM = 1, _AUDIO_SFX = 2
};

class Audio {
public:
	Audio();
	~Audio();

	FMOD::Channel* getBGMChannel(std::string& name);

	// Creates a Sound object.
	//
	// path : Audio file path.
	// name : Audio object identifier.
	// isLoop : Decides if audio loops indefinitely.
	// isStream : Decides if audio should be played through a stream. Set this to true for large audio files.
	// type : ChannelGroup identifier for _sounds. ("bgm", "sfx")
	// volume : Volume of audio (0~100).
	FMOD::Channel* addSound(std::string& path, const char* name, bool isLoop, bool isStream, AudioType type, int volume);
	FMOD::Channel* addSound(std::string& path, std::string& name, bool isLoop, bool isStream, AudioType type, int volume);

	// Checks through all allocated audio objects and releases all that finished playing.
	void update();

	// Releases the sound with identifier 'name'.
	// If there's no parameter, stop all sounds.
	void stopBGM();
	void stopBGM(std::string& name, AudioType type);

	// Returns true if there are any items in _sounds.
	// Returns false otherwise.
	bool hasSounds();

private:
	FMOD::System* fs;
	FMOD_RESULT fr;

	// "sfx" and "bgm" for now, divide this later for advanced adjustments
	std::map<AudioType, FMOD::ChannelGroup*> _sounds;

	// used for _sounds["bgm"]
	std::map<std::string, FMOD::Channel*> bgmChannels;
};

/*
a->addSound(PATH, NAME, LOOP, STREAM, VOLUME);
a->getChannel(NAME)->setPaused(false);
*/