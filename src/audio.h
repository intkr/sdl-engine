#pragma once
#include <map>
#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_output.h"
#include "fmod_errors.h"

#include "core.h"

// random note : Channels are (presumably) released automatically when its Sound is released

enum AudioType { _AUDIO_BGM = 1, _AUDIO_SFX = 2
};

class Audio {
public:
	friend class Core;

	Audio(Core* core);
	~Audio();

	// Creates a Sound object.
	//
	// path : Audio file path.
	// name : Audio object identifier.
	// isLoop : Decides if audio loops indefinitely.
	// isStream : Decides if audio should be played through a stream. Set this to true for large audio files.
	// type : ChannelGroup identifier for _soundgroups. ("bgm", "sfx")
	// volume : Volume of audio (0~100).
	bool addSound(std::string path, std::string name, bool isLoop, bool isStream, AudioType type, int volume);

	bool playSound(std::string name, AudioType type, int volume);
	bool pauseSound(std::string name);
	bool stopSound();
	bool stopSound(std::string name, AudioType type);

	// Checks through all allocated audio objects and releases all that finished playing.
	void update();

	// Returns true if there are any items in _soundgroups.
	// Returns false otherwise.
	bool hasSounds();

private:
	FMOD::System* fs;
	FMOD_RESULT fr;

	// "sfx" and "bgm" for now, divide this later for advanced adjustments
	std::map<AudioType, FMOD::ChannelGroup*> _soundgroups;

	// used for _soundgroups["bgm"]
	std::multimap<std::string, FMOD::Channel*> _channels;

	std::map<std::string, FMOD::Sound*> _sounds;
	Core* core;
};