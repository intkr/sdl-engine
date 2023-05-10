#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_output.h"
#include "fmod_errors.h"

class Audio {
public:
	Audio();
	~Audio();

	FMOD::Channel* getChannel(std::string& name);

	// Creates a Sound object.
	//
	// path : Audio file path.
	// name : Audio object identifier.
	// isLoop : Decides if audio loops indefinitely.
	// isStream : Decides if audio should be played through a stream. Set this to true for large audio files.
	// volume : Volume of audio (0~100).
	bool addSound(std::string& path, const char* name, bool isLoop, bool isStream, int volume);
	bool addSound(std::string& path, std::string& name, bool isLoop, bool isStream, int volume);

	// Checks through all allocated audio data and releases all that finished playing.
	void update();

	// Releases the sound with identifier 'name'.
	// If name is empty (""), stop all sounds.
	void stopSound(std::string& name);

	// Returns true if there are any items in _sounds.
	// Returns false otherwise.
	bool hasSounds();

private:
	FMOD::System* fs;
	FMOD_RESULT fr;

	std::vector<std::pair<std::string, FMOD::Channel*>> _sounds;
};

/*
a->addSound(PATH, NAME, LOOP, STREAM, VOLUME);
a->getChannel(NAME)->setPaused(false);
*/