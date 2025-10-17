#pragma once
#include "ISingleton.h"
#include "BGM.h"
#include "SFX.h"

enum class AudioType
{
	MASTER,
	SFX,
	BGM,
	END
};

class AudioManager : public ISingleton<AudioManager>
{
	DECLARE_SINGLE(AudioManager);

public:
	virtual ~AudioManager() override;

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:
	FMOD::System* GetCoreSystem() { return _coreSystem; }
	void AddBGM(const shared_ptr<BGM>& bgm) { _bgm[bgm->GetName()] = bgm; }
	void AddSFX(const shared_ptr<SFX>& sfx) { _sfx[sfx->GetName()] = sfx; }

public:
	void PlayBGM(const string& name);
	void StopBGM(const string& name);
	void PauseBGM(const string& name);
	void ResumeBGM(const string& name);

public:
	void PlaySFX(const string& name);
	void StopSFX(const string& name);

public:
	void SetVolume(AudioType type, float volume);

public:
	void Clear();

private:
	FMOD::Studio::System* _system;
	FMOD::System* _coreSystem;

private:
	FMOD::ChannelGroup* _bgmGroup = nullptr;
	FMOD::ChannelGroup* _sfxGroup = nullptr;
	FMOD::ChannelGroup* _masterGroup = nullptr;

	unordered_map<string, shared_ptr<BGM>> _bgm; 
	unordered_map<string, shared_ptr<SFX>> _sfx;
};