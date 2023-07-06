#pragma once
#include <map>
#include <string>
#include <iostream>

#include "fmod.hpp"
#include "fmod_output.h"
#include "fmod_errors.h"

class Core;

enum AudioType { _AUDIO_BGM = 1, _AUDIO_SFX = 2
};

class Audio {
public:
	friend class Core;

	Audio(Core* core);
	~Audio();

	// TODO: check if below holds true if isStream is true

	/// <summary>
	/// Creates a Sound object, and adds it to memory.
	/// Sounds are not deleted from memory after it stops, and can be played again.
	/// </summary>
	/// <param name="path">Audio file path.</param>
	/// <param name="name">Sound name.</param>
	/// <param name="isLoop">If true, the audio loops indefinitely.</param>
	/// <param name="isStream">If true, audio is played as a stream. Should be false for SFXs and true for BGMs.</param>
	/// <returns>true if the Sound object is successfully created.</returns>
	bool addSound(std::string path, std::string name, bool isLoop, bool isStream);

	/// <summary>
	/// Plays a sound.
	/// </summary>
	/// <param name="name">Sound name.</param>
	/// <param name="type">Sound type - _AUDIO_BGM or _AUDIO_SFX.</param>
	/// <param name="volume">Sound volume, 0~100.</param>
	/// <returns>true if the sound is successfully played.</returns>
	bool playSound(std::string name, AudioType type, int volume);

	/// <summary>
	/// Pauses a sound.
	/// </summary>
	/// <param name="name">Sound name.</param>
	/// <returns>true if the sound is successfully paused.</returns>
	bool pauseSound(std::string name);

	/// <summary>
	/// Stops all playing sounds.
	/// </summary>
	/// <returns>true if all sounds are successfully stopped.</returns>
	bool stopSound();

	/// <summary>
	/// Stops a sound.
	/// </summary>
	/// <param name="name">Sound name.</param>
	/// <param name="type">Sound type - _AUDIO_BGM or _AUDIO_SFX.</param>
	/// <returns>true if the sound is successfully stopped.</returns>
	bool stopSound(std::string name, AudioType type);

	/// <summary>
	/// Iterates through all existing channels, deleting it from memory if its sound has finished playing.
	/// </summary>
	void update();

	/// <summary>
	/// Checks if there is a channel with sound playing.
	/// </summary>
	/// <returns>true if there is.</returns>
	bool hasSounds();

private:
	FMOD::System* fs;
	FMOD_RESULT fr;

	/// <summary>
	/// Contains a ChannelGroup object for each AudioType.<para/>
	/// Each ChannelGroup is used to control all SFXs or BGMs at once.
	/// </summary>
	std::map<AudioType, FMOD::ChannelGroup*> _chgroups;

	/// <summary>
	/// Contains all Channel objects currently playing a sound.<para/>
	/// Each Channel has its own name, and multiple Channels can have the same name.
	/// </summary>
	std::multimap<std::string, FMOD::Channel*> _channels;

	/// <summary>
	/// Contains all Sound objects for later use.
	/// Sound objects must be loaded and unloaded properly on each state change.
	/// </summary>
	std::map<std::string, FMOD::Sound*> _sounds;

	Core* core;
};