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
}

void AudioManager::Update()
{

}
