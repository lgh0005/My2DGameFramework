#pragma once
#include "IAudio.h"

class BGM : public IAudio
{
	using Super = IAudio;

public:
	BGM(const string& name, const string& filePath, FMOD_MODE playMode);
	virtual ~BGM() override;

public:
	virtual void Play(FMOD::ChannelGroup* group) override;
	virtual void Stop() override;
	virtual void Pause() override;
	virtual void Resume() override;
	virtual bool IsPlaying() const override;
};

