#include "pch.h"
#include "AudioManager.h"

AudioManager::~AudioManager()
{
	if (_system)
	{
		_system->release();
		_system = nullptr;
		_coreSystem = nullptr;
	}
}

void AudioManager::Init()
{
	// Initialize FMOD Studio and Core systems, set software format, and prepare for audio playback
	FMOD_RESULT result;
	auto errFunc = [&]() { return FMOD_ErrorString(result); };

	// Create FMOD system.
	result = FMOD::Studio::System::create(&_system);
	LOGGER.DebugAssert(result != FMOD_OK, "FMOD Error : Failed to create FMOD 'system'.", errFunc);

	// Create FMOD core system.
	result = _system->getCoreSystem(&_coreSystem);
	LOGGER.DebugAssert(result != FMOD_OK, "FMOD Error : Failed to create FMOD 'core system'.", errFunc);
	
	// Set FMOD software format.
	result = _coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);
	LOGGER.DebugAssert(result != FMOD_OK, "FMOD Error : Failed to set 'software format.'", errFunc);

	// Initialize FMOD system.
	result = _system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
	LOGGER.DebugAssert(result != FMOD_OK, "FMOD Error : Failed to initialize system.", errFunc);

	// Create channel group
	_coreSystem->createChannelGroup("Master", &_masterGroup);
	_coreSystem->createChannelGroup("BGM", &_bgmGroup);
	_coreSystem->createChannelGroup("SFX", &_sfxGroup);
	_masterGroup->addGroup(_bgmGroup);
	_masterGroup->addGroup(_sfxGroup);
}

void AudioManager::Update()
{
	_system->update();
}

void AudioManager::LateUpdate() {}

void AudioManager::PlayBGM(const string& name)
{
	auto it = _bgm.find(name);
	if (it == _bgm.end()) return;

	auto& bgm = it->second;
	if (!bgm->IsPlaying()) bgm->Play(_bgmGroup);
}

void AudioManager::StopBGM(const string& name)
{
	auto it = _bgm.find(name);
	if (it == _bgm.end()) return;
	it->second->Stop();
}

void AudioManager::PauseBGM(const string& name)
{
	auto it = _bgm.find(name);
	if (it == _bgm.end()) return;
	it->second->Pause();
}

void AudioManager::ResumeBGM(const string& name)
{
	auto it = _bgm.find(name);
	if (it == _bgm.end()) return;
	it->second->Resume();
}

void AudioManager::PlaySFX(const string& name)
{
	auto it = _sfx.find(name);
	if (it == _sfx.end()) return;
	shared_ptr<SFX> sfx = it->second;
	sfx->Play(_sfxGroup);
}

void AudioManager::StopSFX(const string& name)
{
	auto it = _sfx.find(name);
	if (it == _sfx.end()) return;
	it->second->Stop();
}

void AudioManager::SetVolume(AudioType type, float volume)
{
	FMOD::ChannelGroup* group = nullptr;

	switch (type)
	{
	case AudioType::MASTER: group = _masterGroup; break;
	case AudioType::BGM: group = _bgmGroup; break;
	case AudioType::SFX: group = _sfxGroup; break;
	default: group = _masterGroup; break;
	}

	if (group) group->setVolume(volume);
}

void AudioManager::Clear()
{
	_bgmGroup->stop();
	_sfxGroup->stop();

	_bgm.clear();
	_sfx.clear();
}