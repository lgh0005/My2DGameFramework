#pragma once
#include "IResource.h"

class IAudio : public IResource
{
	using Super = IResource;

public:
	IAudio(const string& name, const string& filePath, FMOD_MODE playMode);
	virtual ~IAudio() override = default;

public:
	virtual void Play(FMOD::ChannelGroup* group) abstract;
	virtual void Stop() abstract;
	virtual void Pause() abstract;
	virtual void Resume() abstract;
	virtual bool IsPlaying() const abstract;

protected:
	FMOD::Sound* _sound = nullptr;
	FMOD::Channel* _channel = nullptr;
};

