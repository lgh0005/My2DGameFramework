#pragma once
#include "ISingleton.h"

class AudioManager : public ISingleton<AudioManager>
{
	DECLARE_SINGLE(AudioManager);

public:
	virtual ~AudioManager() override;

public:
	virtual void Init() override;
	virtual void Update() override;

public:
	// TODO : Control individual audio

public:
	// TODO : Control group audio

private:
	FMOD::Studio::System* _system;
	FMOD::System* _coreSystem;
};

