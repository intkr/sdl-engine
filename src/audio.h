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

	// Adds a new Sound* to a std::map with name as its key.
	// When using a large audio file (eg. BGM), set isStream to true to reduce memory usage.
	// volume should be set between 0~100. Any higher or lower values will be set to its closest bounds.
	// Returns true if successfully added, false otherwise.
	bool addSound(std::string& path, const char* name, bool isLoop, bool isStream, int volume);
	bool addSound(std::string& path, std::string& name, bool isLoop, bool isStream, int volume);

	// Iterates through _sounds to check if any sounds have finished playing.
	// Deletes all items that fits criterion above.
	void update();

	// Releases the sound playing on a channel if key equals name.
	// If name is NULL, stop all sounds.
	void stopSound(std::string& name);

	bool hasSounds();
private:
	// Searches for any item with its name as 'name' in the sound data vector.
	// If found, returns the vector index; otherwise, returns -1.
	int searchSound(std::string& name);

	FMOD::System* fs;
	FMOD_RESULT fr;

	std::vector<std::pair<std::string, FMOD::Channel*>> _sounds;
};

/*
a->addSound(PATH, NAME, LOOP, STREAM, VOLUME);
a->getChannel(NAME)->setPaused(false);
*/