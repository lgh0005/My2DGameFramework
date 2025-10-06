#pragma once
#include "ISingleton.h"

class Audio;

enum class AudioType
{
	BGM,
	SFX,
	END
};

enum class AudioGroups
{
	BGM,
	SFX,
	END
};

enum
{
	AUDIOTYPE_COUNT = static_cast<uint8>(AudioType::END),
	AUDIOGROUP_COUNT = static_cast<uint8>(AudioGroups::END)
};

class AudioManager : public ISingleton<AudioManager>
{
	DECLARE_SINGLE(AudioManager);

public:
	virtual ~AudioManager() override;

public:
	virtual void Init() override;
	virtual void Update() override {};

public:
	FMOD::System* GetCoreSystem() { return _coreSystem; }
	void AddAudioSource(const shared_ptr<Audio>& audio);

public:
	void Play(const string& name, AudioType audioType);
	void Stop(const string& name);
	void Pause(const string& name);
	void Resume(const string& name);

public:
	void StopGroup(AudioGroups group);
	void PauseGroup(AudioGroups group);
	void ResumeGroup(AudioGroups group);

private:
	FMOD::Studio::System* _system;
	FMOD::System* _coreSystem;

private:
	array<unordered_map<string, shared_ptr<Audio>>, AUDIOTYPE_COUNT> _audioMap;
	array<FMOD::ChannelGroup*, AUDIOGROUP_COUNT> _audioGroup;
	unordered_map<string, FMOD::Channel*> _playingChannels;
};

