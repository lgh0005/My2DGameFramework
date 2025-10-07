#pragma once
#include "IResource.h"

class Audio : public IResource
{
	using Super = IResource;

public:
	Audio(const string& name, const string& filePath, uint32 playMode,
		AudioType type, AudioGroups group);
	virtual ~Audio() override = default;

public:
	FMOD::Sound* GetSound() { return _sound; }
	AudioType GetType() { return _type; }
	AudioGroups GetGroup() { return _group; }
	FMOD::Channel* GetChannel() { return _channel; }

private:
	string _audioPath;
	FMOD::Sound* _sound;
	FMOD::Channel* _channel = nullptr;
	AudioType		_type;
	AudioGroups		_group;
};

