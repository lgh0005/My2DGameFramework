#pragma once
#include "ISingleton.h"

class SettingManager : public ISingleton<SettingManager>
{
	DECLARE_SINGLE(SettingManager);

public:
	virtual ~SettingManager() override = default;

public:
	virtual void Init() override {}
	virtual void Update() override {}

public:
	void SetBGM(bool bgm) { _bgmOn = bgm; }
	void SetSFX(bool sfx) { _sfxOn = sfx; }

private:
	bool _bgmOn = true;
	bool _sfxOn = true;
};

