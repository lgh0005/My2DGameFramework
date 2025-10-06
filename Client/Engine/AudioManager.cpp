#include "pch.h"
#include "AudioManager.h"
#include "Audio.h"

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

void AudioManager::AddAudioSource(const shared_ptr<Audio>& audio)
{
	AudioType audioType = audio->GetType();
	AudioGroups audioGroup = audio->GetGroup();
	string audioName = audio->GetName();

	auto& audioDict = _audioMap[static_cast<uint8>(audioType)];
	if (audioDict.find(audioName) != audioDict.end()) return;

	_audioMap[static_cast<uint8>(audioType)][audioName] = audio;
}

void AudioManager::Play(const string& name, AudioType audioType)
{
	// 이미 재생 중이면 무시
	if (_playingChannels.find(name) != _playingChannels.end()) return;

	auto& audioDict = _audioMap[static_cast<uint8>(audioType)];

	// find audio in audioDict.
	auto audio = audioDict[name];
	if (audio == nullptr) return;

	FMOD::Sound* sound = audio->GetSound();
	if (!sound) return;

	// play sound and setting new channel
	FMOD::Channel* channel = nullptr;
	_coreSystem->playSound(sound, nullptr, false, &channel);

	AudioGroups group = audio->GetGroup();
	FMOD::ChannelGroup* channelGroup = _audioGroup[static_cast<uint8>(group)];
	if (channelGroup) channel->setChannelGroup(channelGroup);

	// register channel to now playing audio's channelMap; _playingChannels;
	_playingChannels[name] = channel;
}

void AudioManager::Stop(const string& name)
{
	auto it = _playingChannels.find(name);
	if (it != _playingChannels.end())
	{
		it->second->stop();
		_playingChannels.erase(it);
	}
}

void AudioManager::Pause(const string& name)
{
	auto it = _playingChannels.find(name);
	if (it != _playingChannels.end()) it->second->setPaused(true);
}

void AudioManager::Resume(const string& name)
{
	auto it = _playingChannels.find(name);
	if (it != _playingChannels.end()) it->second->setPaused(false);
}

void AudioManager::StopGroup(AudioGroups group)
{
	// Get the channel group to stop
	FMOD::ChannelGroup* channelGroup = _audioGroup[static_cast<uint8>(group)];

	// stop and remove all channels belonging to this group
	for (auto it = _playingChannels.begin(); it != _playingChannels.end(); )
	{
		FMOD::ChannelGroup* chGroup = nullptr;
		it->second->getChannelGroup(&chGroup);
		if (chGroup == channelGroup)
		{
			it->second->stop();
			it = _playingChannels.erase(it);
		}
		else it++;
	}

	// Finally, stop the channel group itself
	if (channelGroup) channelGroup->stop();
}

void AudioManager::PauseGroup(AudioGroups group)
{
	FMOD::ChannelGroup* channelGroup = _audioGroup[static_cast<uint8>(group)];
	if (channelGroup) channelGroup->setPaused(true);
}

void AudioManager::ResumeGroup(AudioGroups group)
{
	FMOD::ChannelGroup* channelGroup = _audioGroup[static_cast<uint8>(group)];
	if (channelGroup) channelGroup->setPaused(false);
}

